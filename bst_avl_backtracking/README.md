

Binary Search Trees, AVL Trees, and Backtracking

bst.h is a templated binary search tree class which implements standard insertion, deletion, find, isBalanced, clear, and print methods. It promotes the predecessor node in deletion. 

avl.h is a templated avl tree class that derives from bst.h. It balances the tree after insertion and deletion. 

scheduling.cpp implements a backtracking algorithm which takes an input file that includes on the first line: how many exams there are, how many students there are, and how many timeslots there are.
On each following line there is the name of a student, and the name of the classes that student is in. 
For example:
5 4 3
aaron    104 170
leia 104   170 350
jarjar  101
finn  270  350

The output is then the classes assigned to their respective timeslots: one class per line:
101 1
104 1
170 2
270 1
350 3

If there is no solution, it outputs "No valid solution."
The backtracking algorithm utilizes the AVL class to keep track of the timeslot each class is in. 

To compile scheduling.cpp, simply type "make" or "make scheduling" and then run it using ./scheduling <inputfilename>


