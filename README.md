# Project 5 : AVL Loader
### Made for data structures

### Instructions I was given for this homework project (full PDF in files)
You should then write a program that allows a user to interact with an instance of the AVL you have
implemented. This program should implement a text-based interface that allows the user to:

1. Create an empty AVL. This should warn the user they are deleting the existing AVL and ask them
if they wish to proceed. Remind the user they can save the contents of their AVL to a file.
2. Insert a string into the current AVL.
3. Search for a string in the current AVL.
4. Remove a string from the current AVL.
5. Output the in-order traversal of the current AVL.
6. Output the pre-order traversal of the current AVL.
7. Output the post-order traversal of the current AVL.
8. Save the post-order traversal of the current AVL to a user specified filename.
9. Read the post-order traversal from a user specified filename and reconstruct a functional AVL
duplicate of the saved AVL
10. Exit.


Pseudocode for loading a post order traversal back into a tree:

    1. Destroy the existing tree
    2. Read the strings from the save file into an array (use a vector for ease of use)
    3. Create the root node and assign it the value of the last element of the array
    4. Push the root onto an empty stack
    5. Iterate I backwards from length(array)-2 to 0
      a. Declare pointer to a node current and assign it the value of the array[I]
      b. Declare pointers to a node temp and top
      c. Loop while the stack isn’t empty
        i. Assign top the value of stack.peek()
        ii. If (current’s value >= top’s value) exit the while loop
        iii. Assign temp the value of top
        iv. Pop an element from the stack
      d. If temp has a value assigned to it
        i. Set temp’s left to current
      e. Otherwise
        i. Assign top the value of stack.peek()
        ii. Set top’s right to current
      f. Push current onto the stack
    6. Finally traverse the newly create tree and fix the heights
