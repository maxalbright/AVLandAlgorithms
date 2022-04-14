# Binary Search Trees, AVL Trees, and Backtracking

## Binary Search Tree (BST) Implementation
bst.h is a templated binary search tree class which implements standard insertion, deletion, find, isBalanced, clear, and print methods. It also implements an iterator that performs in-order traversal through the tree, just as the iterator of a map in the standard template library does. Note: This implementation promotes the predecessor node in deletion. <br><br>

## AVL Tree Implementation
avl.h is a templated avl tree class that derives from bst.h. It balances the tree after insertion and deletion. <br><br>

Example: <br>

<img width="650" alt="Screen Shot 2022-04-13 at 7 58 41 PM" src="https://user-images.githubusercontent.com/70349082/163304955-c16700eb-87a5-4ca6-96cb-9a3cf068286a.png">
<img width="500" alt="Screen Shot 2022-04-13 at 7 59 57 PM" src="https://user-images.githubusercontent.com/70349082/163305082-c98237e1-5b12-4684-93aa-4f6ec2dd2f45.png">
<img width="169" alt="Screen Shot 2022-04-13 at 8 00 11 PM" src="https://user-images.githubusercontent.com/70349082/163305109-6abe4604-5228-4aed-8370-3c65919acdd6.png">
<img width="461" alt="Screen Shot 2022-04-13 at 8 00 43 PM" src="https://user-images.githubusercontent.com/70349082/163305173-63213c64-d212-47e1-800a-d65b95c0b791.png"> <br>

<hr>

## Backtracking Algorithm
scheduling.cpp implements a backtracking algorithm which takes an input file that includes on the first line: "e s t" where <br>
- e = how many exams there are
- s = how many students there are
- t = how many timeslots there are.  <br>

On each following line there is the name of a student, and the name of the classes that student is in. 
<br><br>
Example Input File: <br>
5 4 3  
aaron    104 170  
leia 104   170 350  
jarjar  101  
finn  270  350.  <br><br>

The output is then the classes assigned to their respective timeslots: one class per line:
101 1  
104 1  
170 2  
270 1  
350 3  

If there is no solution, it outputs "No valid solution."  
The backtracking algorithm utilizes the AVL class to keep track of the timeslot each class is in.   

## To Compile:

To compile scheduling.cpp, simply type "make" or "make scheduling" and then run it using ./scheduling <inputfilename>
