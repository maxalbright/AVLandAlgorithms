//
//  tests.cpp
//  
//
//  Created by Max Albright on 11/21/21.
//

#include "avlbst.h"
#include <string>
#include <iostream>
#include <cstdlib>

using namespace std;



int main(int argc, char* argv[]) {
   
    
    BinarySearchTree<int,string> bst;
    cout << bst.empty() << endl;
    
    
    // delete leaf node
    /*
    bst.insert(pair<int, string> (1, "hello"));
    bst.insert(pair<int, string> (2, "hello2"));
    bst.insert(pair<int, string> (3, "hello3"));
    bst.insert(pair<int, string> (4, "hello"));
    bst.insert(pair<int, string> (5, "hello2"));
    bst.insert(pair<int, string> (6, "hello3"));
    bst.insert(pair<int, string> (7, "hello"));
    bst.remove(7);
    bst.print();
    bst.clear();

    
    // delete root node
    bst.insert(pair<int, string> (1, "hello"));
    bst.insert(pair<int, string> (2, "hello2"));
    bst.insert(pair<int, string> (3, "hello3"));
    bst.remove(1);
    bst.print();
    bst.clear();
    
    */
    // delete something with one child
    bst.insert(pair<int, string> (44, "hello"));
    bst.insert(pair<int, string> (17, "hello2"));
    bst.insert(pair<int, string> (32, "hello3"));
    bst.insert(pair<int, string> (30, "hello"));
    bst.insert(pair<int, string> (62, "hello2"));
    bst.insert(pair<int, string> (50, "hello3"));
    bst.insert(pair<int, string> (54, "hello"));
    bst.insert(pair<int, string> (78, "hello3"));
    bst.insert(pair<int, string> (70, "hello"));
    bst.insert(pair<int, string> (88, "hello"));
    bst.remove(32);
    bst.print();
    bst.insert(pair<int, string> (32, "hello3"));
    /*
    //delete something that has two children and predecessor has none
    bst.remove(62);
    bst.print();
    bst.insert(pair<int, string> (62, "hello3"));
    
    
    //delete something that has two children and predecessor has one
    bst.remove(44);
    bst.print();
    bst.insert(pair<int, string> (44, "hello3"));
    bst.clear();
    
    
   
    
    
    AVLTree<int, string> avl;
    
    
     // EXAMPLE FROM LECTURE 22 
    avl.insert(pair<int, string> (1, "1"));
    avl.print();
    cout << avl.isBalanced() << endl;
    avl.insert(pair<int, string> (2, "1"));
    avl.print();
    cout << avl.isBalanced() << endl;
    avl.insert(pair<int, string> (3, "1"));
    avl.print();
    cout << avl.isBalanced() << endl;
    avl.insert(pair<int, string> (12, "1"));
    avl.print();
    cout << avl.isBalanced() << endl;
    avl.insert(pair<int, string> (9, "1"));
    avl.print();
    cout << avl.isBalanced() << endl;
    avl.insert(pair<int, string> (13, "1"));
    avl.print();
    cout << avl.isBalanced() << endl;
    avl.insert(pair<int, string> (7, "1"));
    avl.print();
    cout << avl.isBalanced() << endl;
    avl.insert(pair<int, string> (4, "1"));
    avl.print();
    cout << avl.isBalanced() << endl;
    avl.insert(pair<int, string> (6, "1"));
    avl.print();
    cout << avl.isBalanced() << endl;
    avl.insert(pair<int, string> (5, "1"));
    avl.print();
    cout << avl.isBalanced() << endl;
    avl.insert(pair<int, string> (8, "1"));
    avl.print();
    cout << avl.isBalanced() << endl;

    avl.remove(4);
    avl.print();
    cout << avl.isBalanced() << endl;
    avl.remove(1);
    avl.print();
    cout << avl.isBalanced() << endl;
    
    avl.insert(pair<int, string> (1, "1"));
    avl.print();
    cout << avl.isBalanced() << endl;
    avl.insert(pair<int, string> (14, "1"));
    avl.print();
    cout << avl.isBalanced() << endl;
    avl.insert(pair<int, string> (11, "1"));
    avl.print();
    cout << avl.isBalanced() << endl;
    
    avl.remove(3);
    avl.print();
    cout << avl.isBalanced() << endl;
    avl.remove(13);
    avl.print();
    cout << avl.isBalanced() << endl;
    avl.remove(12);
    avl.print();
    cout << avl.isBalanced() << endl;
    avl.remove(11);
    avl.print();
    cout << avl.isBalanced() << endl;
    avl.remove(14);
    avl.print();
    cout << avl.isBalanced() << endl;
    avl.remove(2);
    avl.print();
    cout << avl.isBalanced() << endl;
    avl.remove(3);
    avl.print();
    cout << avl.isBalanced() << endl;
    avl.remove(7);
    avl.print();
    cout << avl.isBalanced() << endl;
    avl.remove(8);
    avl.print();
    cout << avl.isBalanced() << endl;
    avl.remove(9);
    avl.print();
    cout << avl.isBalanced() << endl;
    avl.clear();
    
    
    
    cout << "New Test " << endl;
    
    avl.insert(pair<int, string> (8, "1"));
    avl.print();
    avl.insert(pair<int, string> (5, "1"));
    avl.print();
    avl.insert(pair<int, string> (9, "1"));
    avl.print();
    avl.insert(pair<int, string> (3, "1"));
    avl.print();
    avl.insert(pair<int, string> (6, "1"));
    avl.print();
    avl.insert(pair<int, string> (11, "1"));
    avl.print();
    avl.insert(pair<int, string> (2, "1"));
    avl.print();
    avl.insert(pair<int, string> (4, "1"));
    avl.print();
    avl.insert(pair<int, string> (7, "1"));
    avl.print();
    avl.insert(pair<int, string> (10, "1"));
    avl.print();
    avl.insert(pair<int, string> (12, "1"));
    avl.print();
    avl.insert(pair<int, string> (1, "1"));
    avl.print();
    
    avl.remove(10);
    avl.print();
    
    
    // Test isBalanced
    bst.insert(pair<int, string>(2, "1"));
    bst.print();
    cout << bst.isBalanced() << endl;
    bst.insert(pair<int, string>(1, "1"));
    bst.print();
    cout << bst.isBalanced() << endl;
    bst.insert(pair<int, string>(3, "1"));
    bst.print();
    cout << bst.isBalanced() << endl;
    bst.insert(pair<int, string>(4, "1"));
    bst.print();
    cout << bst.isBalanced() << endl;
    bst.insert(pair<int, string>(5, "1"));
    bst.print();
    cout << bst.isBalanced() << endl;
    
    
    //test "isBalanced"
    
    for (int i = 0; i < 1000; i++) {
        int insertion = rand() % 250;
        avl.insert(pair<int, string>(insertion, "1"));
        // the next three lines only work if you make root_ public temporarily
        
        if (i % 5 == 0) {
            avl.remove(avl.root_->getKey());
        }
       
        cout << i << " " << insertion << " " << avl.isBalanced() << endl;
        
        
    }
    
    cout << avl.empty();
    
    avl.clear();
    cout << avl.empty();
    
    
    */
    return 0;
}

