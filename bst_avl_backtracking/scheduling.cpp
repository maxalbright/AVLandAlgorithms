//
//  scheduling.cpp
//
//
//  Created by Max Albright on 11/26/21.
//

#include "avlbst.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

void printsolution(AVLTree<int, int>& map) {
    for (AVLTree<int, int>::iterator treeitr = map.begin(); treeitr != map.end(); ++treeitr) {
        cout << (*treeitr).first << " " << (*treeitr).second + 1 << endl;
    }
}

bool search(
        int row,
        AVLTree<int, int>& map,
        bool** threat,
        pair<int, vector<int>>* classroster,
        int numexams,
        int numtimeslots) {

    if (row == numexams) {
        printsolution(map);
        return true;
    } else {
        // tries every timeslot for that specific class, given the classes placement before it
        for (int i = 0; i < numtimeslots; i++) {
            bool oktoplacehere = true;
            for (int personinclass = 0; personinclass < (int)classroster[row].second.size(); personinclass++) {
                if (threat[classroster[row].second[personinclass]][i]
                    == true) {  // it is not ok for this student to be placedhere
                    oktoplacehere = false;
                    break;
                }
            }
            if (oktoplacehere) {
                // adjusts threat array
                for (int personinclass = 0; personinclass < (int)classroster[row].second.size(); personinclass++) {
                    threat[classroster[row].second[personinclass]][i] = true;
                }
                // tries to continue on from here
                map.insert(pair<int, int>(classroster[row].first, i));
                if (search(row + 1, map, threat, classroster, numexams, numtimeslots)) {
                    return true;
                }

                // if that insertion didn't work, try it at the next available slot
                else {
                    map.remove(classroster[row].first);
                    for (int personinclass = 0; personinclass < (int)classroster[row].second.size(); personinclass++) {
                        threat[classroster[row].second[personinclass]][i] = false;
                    }
                }
            }
        }
    }
    // if you have reached this, a solution is not possible
    return false;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        return 0;
    }
    ifstream ifile(argv[1]);
    if (ifile.fail()) {
        return 0;
    }
    int numexams, numstudents, numtimeslots;
    ifile >> numexams >> numstudents >> numtimeslots;

    // keeps track of what time slots each student can and can't be in
    bool** threat = new bool*[numstudents];
    for (int i = 0; i < numstudents; i++) {
        threat[i] = new bool[numtimeslots];
        for (int j = 0; j < numtimeslots; j++) {
            threat[i][j] = false;
        }
    }

    AVLTree<int, int> map;
    // this is an array of the classes and the students in each
    pair<int, vector<int>>* classroster = new pair<int, vector<int>>[numexams];
    string currline;
    getline(ifile, currline);
    int currstudent = 0;

    while (getline(ifile, currline)) {
        stringstream ss(currline);
        string getridof;
        int currentexaminline;
        ss >> getridof;
        while (ss >> currentexaminline) {
            for (int i = 0; i < numexams; i++) {
                if (classroster[i].first == currentexaminline) {
                    classroster[i].second.push_back(currstudent);
                    break;
                } else if (classroster[i].first == 0) {
                    classroster[i].first = currentexaminline;
                    classroster[i].second.push_back(currstudent);
                    break;
                }
            }
        }
        currstudent++;
    }

    if (!search(0, map, threat, classroster, numexams, numtimeslots)) {
        cout << "No valid solution." << endl;
    }

    for (int i = 0; i < numstudents; i++) {
        delete[] threat[i];
    }
    delete[] threat;
    delete[] classroster;

    return 0;
}
