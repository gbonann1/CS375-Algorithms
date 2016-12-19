compile using makefile
'./program1 input.txt output.txt' to run

program1 uses 2d vectors of ints. The tree vector is a 2d vector that represents the tree. It is initialized to 2n^2 - 1 by 5 and each entry represents a node in the tree initialized as -1. Each node stores 5 int values which represent the bound, profit, weight, index, and level in the tree respectively.

The input is read in from the 2nd command line argument and output to a file specified by the 3rd command line argument. The input is stored in a vector of int vectors named unsortedItems which is initialized to -1. Each vector stores 3 int values, the weight, the profit, and the profit/weight. 

This 2d vector named unsortedItems is then sorted by density using the std::sort function in the function sortItems(). The complexity of this sort is O(N*logN).

The calcBound function is used to calculate the bound of a node given its level in the tree, the totalCapacity of the problem, the current weight and profit at that node, and the total number of items. The complexity here is O(N) because you are looping through the array of sorted items.

The priority queue pq is a queue of vectors of ints. Each vector corresponds with a node in the tree. These vectors hold the 5 values mentioned above in the tree. They are prioritized by their value at index 0 (their bound)

Finally there is a 2d vector path which stores and array of integers representing whether each item is selected or not selected. It is initialized to 0 to represent the item at index i is not selected. A value of 1 represents that the item at this index has been selected as part of the solution for a given node.

The main function adds the root node to the priority queue. From there, it adds children to the priority queue which have bounds that are greater than the best feasible solution thus far. 2*currentIndex + 1 represents a left child (item at that level is selected) and 2*currentIndex + 2 indicates a right child. (item at that level is not selected. The values in the tree are updated as we consider children. There are also several counters that are updated and the path is updated at the nodes that are being considered.

The complexity of this solution is at worst the case where you can't prune out much of the tree. Assuming the tree is a complete binary tree this would be O(2^n). The Best case would be if the first item considered fills the capacity and is the optimal solution. O(1). The average case would be that you are able to prune out a large portion of the tree because you are considering the nodes in order of the most promising ones. The complexity can vary greatly due to the fact that it depends on the input how much you are able to prune.
