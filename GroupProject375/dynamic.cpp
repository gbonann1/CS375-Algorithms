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
std::vector<std::vector<int> > unsortedItems (1, std::vector<int> (3, -1));
std::vector<std::vector<int> > table (1, std::vector<int> (1, -1));


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
	ifstream input (argv[1]); 
	int a, b;
	char g;
	int count = 0;
	int n;
	int cap;
		
	while ((input >> a >> g >> b) && (g == ',')){
		if (count == 0){
			n = a;
			for (int p = 0; p < n; p++)
				unsortedItems.push_back(std::vector<int> (3, -1));
			cap = b;
			table.resize(n + 1);
			for (int q = 0; q < n + 1; q++){
				table[q].resize(b + 1, -1);
			}
			count++;
			
		}
		else {
			unsortedItems[count][0] = a; //weight //change to push
			unsortedItems[count][1] = b; //profit
			count++;
		}
	}
	std::ofstream out(argv[2]);
	std::streambuf *coutbuf = std::cout.rdbuf();
	std::cout.rdbuf(out.rdbuf());

	
	
	int i = 0;
	int c = 0;
	int j = 0;
	
	//cout << unsortedItems.size();
	//cout << table.size();
	//cout << table[table.size()].size();
	gettimeofday (&before, NULL);
	
	for (i = 0; i < table.size(); i++){
		table[i][0] = 0;
	}
	for (c = 0; c < table[0].size(); c++){
		table[0][c] = 0;
	}
	for (i = 1; i < table.size(); i++){
		for (c = 1; c < table[i].size(); c++){
			if (unsortedItems[i][0] <= c){
				if (table[i-1][c - unsortedItems[i][0]] + unsortedItems[i][1] > table[i-1][c]){
					table[i][c] = table[i-1][c - unsortedItems[i][0]] + unsortedItems[i][1];
				}
				else {
					table[i][c] = table[i-1][c];
				}
			}
			else {
				table[i][c] = table[i-1][c];
			}
		}
	}
	
	
	gettimeofday (&after, NULL); //finished calculating the tables
	for (i = 0; i < table.size(); i++){
		cout << '\n';
		for (j = 0; j < table[i].size(); j++){
			cout << table[i][j] << '\t';
		}	
	}
	//solution
	//cout << '\n';
	
	//cout << solutionStr;
	//time elapsed (after.tv_usec - before.tv_usec)
	cout << '\n';
	cout << "time elapsed (us): ";
	cout << after.tv_usec - before.tv_usec;
	cout << '\n';
	
	
	return 0;

}
