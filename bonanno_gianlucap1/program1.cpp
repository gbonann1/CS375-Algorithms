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

std::string solutionStr; //string to store solution 

int max(int arg1, int arg2){ //return the max of 2 values
	int retVal;
	if (arg1 > arg2)
		retVal = arg1;
	else
		retVal = arg2;

	return retVal;
}

void solution(std::vector<std::vector<int> > matrixDirection, std::string file1){ //solves for the solution string. writes it into the global solutionStr
	
	int i;
	int j;
	i = matrixDirection.size() - 1;
	j = matrixDirection[i].size() - 1;
	while (i > 0 && j > 0){
		if (matrixDirection[i][j] == 0){
			i--;
			j--;
			solutionStr = file1[i] + solutionStr; 				
		}
		else if (matrixDirection[i][j] == 1){
			i--;
		}
		else {
			j--;
		}
	}

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
	std::ofstream out("output1.txt");
	std::streambuf *coutbuf = std::cout.rdbuf();
	std::cout.rdbuf(out.rdbuf());
	
	int i = 0;
	int j = 0;
	
	std::vector<std::vector<int> > matrix (filex.size() + 1, std::vector<int> (filey.size() + 1, -1));//matrix with values of length of LCS
	std::vector<std::vector<int> > matrixDirection (filex.size() + 1, std::vector<int> (filey.size() + 1, -1));//matrix with arrows, 0 = diagonal, 1 = left, 2 = up
	
	gettimeofday (&before, NULL);
	//calculating the 2 matrices bottom up. 
	
	for (i = 0; i < matrix.size(); i++)
		matrix[i][0] = 0;
	for (j = 0; j < matrix[0].size(); j++)
		matrix[0][j] = 0;
	for (i = 1; i < matrix.size(); i++){
		for (j = 1; j < matrix[i].size(); j++){
			if (filex[i-1] == filey[j-1]){
				matrix[i][j] = matrix[i-1][j-1] + 1;
				matrixDirection[i][j] = 0; //diagonal
			}
			else {
				matrix[i][j] = max(matrix[i-1][j], matrix[i][j-1]);
				if (matrix[i][j] == matrix[i-1][j]) 
					matrixDirection[i][j] = 1; //left
				else
					matrixDirection[i][j] = 2; //up
			}
			
		}
	}
	gettimeofday (&after, NULL); //finished calculating the tables

	if (filex.size() <= 10 && filey.size() <= 10){
		for (i = 0; i < matrix.size(); i++){
			cout << '\n';
			for (j = 0; j < matrix[i].size(); j++){
				cout << matrix[i][j];
			}	
		}
		//solution
		cout << '\n';
		cout << "Solution String: ";
		solution(matrixDirection, filex);
		cout << solutionStr;
		//time elapsed (after.tv_usec - before.tv_usec)
		cout << '\n';
		cout << "time elapsed (us): ";
		cout << after.tv_usec - before.tv_usec;
		cout << '\n';
	}
	else {
		//length of lcs
		cout << "Length of LCS: ";
		cout << matrix.back().back();
		//time elapsed (after.tv_usec - before.tv_usec)
		cout << '\n';
		cout << "time elapsed (sec, usec): ";
		cout << after.tv_sec - before.tv_sec;
		cout << ", ";
		cout << after.tv_usec - before.tv_usec;
		cout << '\n';
	}
	
	return 0;

}
