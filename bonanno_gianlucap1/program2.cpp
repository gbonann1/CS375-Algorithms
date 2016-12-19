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

int recursiveLCS(std::string filex, std::string filey, int i, int j){ //recursive solution
	if (i == 0 || j == 0)
		return 0;
	int retVal = 0;
	if (filex[i] == filey[j])
		retVal = recursiveLCS(filex, filey, i-1, j-1) + 1; //take diagonal + 1
	else
		retVal = max(recursiveLCS(filex, filey, i-1, j), recursiveLCS(filex, filey, i, j-1));
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
	std::ofstream out("output2.txt");
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
