#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <cstring>
#include <sys/time.h>
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stddef.h>
using namespace std;

int max(int arg1, int arg2){ //return the max of 2 values
	int retVal;
	if (arg1 > arg2)
		retVal = arg1;
	else
		retVal = arg2;

	return retVal;
}

std::vector<std::vector<int> > memoTable (101, std::vector<int> (101, -1)); //table to check, initialized to -1. 100x100 to accomodate max test string length of 100

int recursiveLCS(std::string filex, std::string filey, int i, int j){ 
	if (i == 0 || j == 0){
		memoTable[i][j] = 0;
		return 0;
	}
	int retVal = 0;
	if (filex[i] == filey[j]){
		if (memoTable[i-1][j-1] != -1){ //if already calculated in memoTable
			retVal = memoTable[i-1][j-1] + 1; //take diagonal + 1 from table
		}
		else {
			retVal = recursiveLCS(filex, filey, i-1, j-1) + 1; //take diagonal + 1 from recursive call
			memoTable[i-1][j-1] = retVal - 1; //update table 
		}
	}
	else {
		if (memoTable[i-1][j] != -1 && memoTable[i][j-1] != -1) //if both already calculated in memoTable
			retVal = max(memoTable[i-1][j], memoTable[i][j-1]);
		else if (memoTable[i-1][j] != -1){ //if 1st already calculated in memoTable
			int calculation = recursiveLCS(filex, filey, i, j-1);
			retVal = max(memoTable[i-1][j], calculation);
			memoTable[i][j-1] = calculation; //update memoTable with 2nd value
		}
		else if (memoTable[i][j-1] != -1){ //if 2nd already calculated in memoTable
			int calculation = recursiveLCS(filex, filey, i-1, j);
			retVal = max(calculation, memoTable[i][j-1]);
			memoTable[i-1][j] = calculation; //update memoTable with first value
		}
		else{ //if neither already calculated in memoTable
			int calc1 = recursiveLCS(filex, filey, i-1, j);
			int calc2 = recursiveLCS(filex, filey, i, j-1);
			retVal = max(calc1, calc2); //don't call recursive more than once
			memoTable[i-1][j] = calc1; //update memoTable with both values
			memoTable[i][j-1] = calc2;
		}
	}
	memoTable[i][j] = retVal;//update memoTable 
	return retVal;
}



int main(int argc, char **argv)
{
	struct timeval before, after; //to track running time
	std::string filex; 
	std::string filey;
	ifstream input (argv[1]); 
	std::getline(input, filex);
	ifstream input2 (argv[2]);
	std::getline(input2, filey);
	std::ofstream out("output3.txt");
	std::streambuf *coutbuf = std::cout.rdbuf();
	std::cout.rdbuf(out.rdbuf());
	
	
	
	gettimeofday (&before, NULL);
	int lengthLCS = recursiveLCS(filex, filey, filex.size(), filey.size());
	gettimeofday (&after, NULL); //finished calculating

	
	//length of lcs
	cout << "Length of LCS: ";
	cout << lengthLCS;
	//time elapsed (after.tv_usec - before.tv_usec)
	cout << '\n';
	cout << "time elapsed (sec, usec): "; //negative usec means a full second didn't elapse
	cout << after.tv_sec - before.tv_sec;
	cout << ", ";
	cout << after.tv_usec - before.tv_usec;
	cout << '\n';
	
	
	return 0;

}
