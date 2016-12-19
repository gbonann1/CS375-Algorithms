compile using makefile
'./program2 filex.txt filey.txt' to run

This program uses no complex data structures

This program uses the recursive approach to solve the LCS problem. Starting from the bottom right of the "table" (index at file1.size, file2.size) we recursively call the diagonal entry if there is a match. Otherwise we call the max of the recursive call above or below the current index. The base case is the first row/column where each entry is 0. (mimicing the example from lecture slides) 

the max function takes 2 ints as arguments and returns the larger of the two

the function recursiveLCS is the recursive function for solving the LCS problem.

this program outputs the solution length and run time to the output2.txt file

This program has the worst run time as the input sizes increase. The recursive calls are to blame because with the growing size of the inputs, the number of recursive calls increases exponentially. However, with small input sizes the run time acceptable.
