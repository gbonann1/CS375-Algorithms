compile using makefile
'./program1 filex.txt filey.txt' to run

program1 uses 2 2d vectors of ints. One vector (matrix) contains the values of the LCS problem at each index. The second vector (matrixDirection) contains values ranging from 0 to 2. 0 represents a diagonal arrow, 1 represents a left arrow, 2 represents an up arrow. These two matrices are initialized to -1.

This program uses the bottom up approach as it calculates the values for each entry in the 2d array. There are 2 2d arrays and each has a length of filex.size() + 1 and width of filey.size() + 1. Therefore the run time of this program is 2 * (input1size + 1) * (input2size + 1) since setting each value in the matrix is constant time.

the max function takes 2 ints as arguments and returns the larger of the two

the function solution takes the matrixDirection and one of the files and figures out the solution string by working backwards through the array of arrows. It updates the global solutionStr variable which is used when the length of each input is <= 10.

this program outputs the solution string and run time or the solution length and run time to the output1.txt file



