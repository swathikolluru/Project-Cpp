BST Directory/File Manager

A terminal-based file management system built in C++ using Binary Search Trees (BST).
The project demonstrates BST operations through file and directory management functionalities.

->     Features

Create files and directories
Delete files and directories
Search for a file or directory
Display entries in sorted order
View tree using inorder, preorder, and postorder traversals
Distinguish between files and directories during display


->   Project Structure

BST-File-Manager/

├── file_manager_bst.cpp

└── README.md

->          Data Structure Used


Data Structure              	Purpose

Binary Search Tree (BST)	    Stores files and directories alphabetically

Node Class	                  Stores entry name, type, and child pointers

->Operations and Complexity

Operation	                Description	                     Complexity

Insert	              Add file/directory	              O(log n) average

Search	              Find file/directory         	    O(log n) average

Delete	              Remove file/directory	            O(log n) average

Inorder               Traversal	Alphabetical listing	        O(n)

Preorder Traversal	  Root-first display	                    O(n)

Postorder Traversal	  Child-first display	                    O(n)


->      Functionalities

Create new files and directories
Delete entries from BST
Search for existing entries
Display sorted directory listing
Traverse tree using different traversal methods
Concepts Demonstrated
Binary Search Tree operations
Tree traversals
Recursion
Dynamic memory allocation
Pointers and node-based structures
Inorder successor in BST deletion


->     Author

Developed by Kolluru Swathi
