compile using makefile
'./program3 filex.txt filey.txt' to run

This program uses a 2d vector of ints called memoTable which is initialized to -1. -1 corresponds to a value that has not been solved for yet. Any other value means that we have already recursively solved for this value of i and j.

This program uses the recursive approach to solve the LCS problem with memoization. Starting from the bottom right of the "table" (index at file1.size, file2.size) we recursively call the diagonal entry if there is a match. Otherwise we call the max of the recursive call above or below the current index. The base case is the first row/column where each entry is 0. (mimicing the example from lecture slides) 

The difference between this a program 2 is that before ANY recursive calls, we first refer to the memoTable data structure to check if we have already made this same recursive call in the past. If we have a hit into this memoTable, we simply access the value there and do NOT recursively call. The values in this table are updated after every recursive call.

the max function takes 2 ints as arguments and returns the larger of the two

the function recursiveLCS is the recursive function for solving the LCS problem.

this program outputs the solution length and run time to the output3.txt file

This algorithm is significantly faster than program 2 because it makes way less recursive calls than program 2 does. The memoTable is the reason for this because it allows us to solve each unique subproblem only once. This reduces the number of nodes in the recursion tree dramatically.
