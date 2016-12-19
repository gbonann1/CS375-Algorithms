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
#include <algorithm>
#include <queue>
using namespace std;
const int MAXITEM = 100;
const int MAXTREE = 2*MAXITEM*MAXITEM - 1;

//2n^2 - 1 nodes
//n items
std::vector<std::vector<int> > tree (MAXTREE, std::vector<int> (5, -1)); //bound, profit weight, index, level
std::vector<std::vector<int> > unsortedItems (MAXITEM, std::vector<int> (3, -1)); //weight profit density
//std::vector<std::vector<int> > sortedItems (11, std::vector<int> (3, -1)); //not needed
std::priority_queue<std::vector<int> > pq;
std::vector<std::vector<int> > path (MAXTREE, std::vector<int> (MAXITEM, 0));






void sortItems(){ //sorts the items in order of descending profit density
	for (int i = 1; i < MAXITEM; i++){
		unsortedItems[i][2] = unsortedItems[i][1]/unsortedItems[i][0];
	}
	//sort items in unsorted
	std::sort(unsortedItems.begin(), unsortedItems.end(), [](const std::vector< int >& a, const std::vector< int >& b){ return a[2] > b[2]; } );
	
	
}

int calcBound(int level, int totalCap, int weight, int profit, int n){ //function to calculate bound of node
	int bound = 0;
	int remCap = totalCap - weight;
	int i = level;
	while (remCap > 0 && i < n){
		if (remCap - unsortedItems[i][0] > 0){
			bound += unsortedItems[i][1];
			remCap -= unsortedItems[i][0];
			i++;
		}
		else{
			double frac = remCap/(double)unsortedItems[i][0];
			bound += (unsortedItems[i][1] * frac);
			remCap = 0;
		}
	}
	
	return bound + profit;

}



int main(int argc, char **argv)
{ 
	ifstream input (argv[1]); 
	int a, b;
	char c;
	int count = 0;
	int n;
	int cap;
	int best = -1;
	int numItems = 0;
	int nodesVisited = 0;
	int leafsVisited = 0;
	int bestNode = -1;
	
	while ((input >> a >> c >> b) && (c == ',')){
		if (count == 0){
			n = a;
			cap = b;
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
	
	
	sortItems();
	//root
	
	
	tree[0][1] = 0;//profit
	tree[0][2] = 0;//weight
	tree[0][0] = calcBound(0,cap,tree[0][2],tree[0][1],n); //bound 
	tree[0][3] = 0; //index
	tree[0][4] = 0; //level
	best = tree[0][1];
	pq.push(tree[0]);
	while (!pq.empty()){
		int currentWeight = pq.top()[2];
		int currentProfit = pq.top()[1];
		int currentBound = pq.top()[0];
		int currentIndex = pq.top()[3];
		int currentLevel = pq.top()[4];
		//printf("%d", currentBound);
		pq.pop();
		nodesVisited++;
		//path[currentIndex] = path[(currentIndex-1) / 2];
		//path[currentIndex][currentLevel] = 0;
		
		if (currentLevel == n - 1)
			leafsVisited++;
		if (currentBound > best){
			//numItems++;
			nodesVisited++;
			tree[2*currentIndex + 1][2] = currentWeight + unsortedItems[currentLevel][0];
			if (tree[2*currentIndex + 1][2] <= cap){
				tree[2*currentIndex + 1][1] = currentProfit + unsortedItems[currentLevel][1];
				//printf("%d", currentIndex);
			}
			else{
				tree[2*currentIndex + 1][1] = currentProfit;
				
			}
			tree[2*currentIndex + 1][0] = calcBound(currentLevel + 1, cap, tree[2*currentIndex + 1][2],tree[2*currentIndex + 1][1], n);
			//printf("%d", tree[2*currentIndex + 1][0]);
			//printf("%d", tree[2*currentIndex + 1][1]);
			tree[2*currentIndex + 1][3] = 2*currentIndex + 1;
			tree[2*currentIndex + 1][4] = currentLevel + 1;
			if ( tree[2*currentIndex + 1][4] == n - 1)
				leafsVisited++;
			tree[2*currentIndex + 2][2] = tree[currentIndex][2];
			tree[2*currentIndex + 2][1] = tree[currentIndex][1];
			tree[2*currentIndex + 2][0] = calcBound(currentLevel + 1, cap, tree[2*currentIndex + 2][2], tree[2*currentIndex + 2][1], n);
			//printf("%d", tree[2*currentIndex + 2][2]);
			tree[2*currentIndex + 2][3] = 2*currentIndex + 2;
			tree[2*currentIndex + 2][4] = currentLevel + 1;
			if ( tree[2*currentIndex + 2][4] == n - 1)
				leafsVisited++;
			path[2*currentIndex + 1] = path[currentIndex];
			path[2*currentIndex + 2] = path[currentIndex];
			path[2*currentIndex + 1][currentLevel] = 1;
			path[2*currentIndex + 2][currentLevel] = 0;
			if ( tree[2*currentIndex + 1][1] > best){
				best = tree[2*currentIndex + 1][1];
				//keep track of optimal path
				bestNode = 2*currentIndex + 1;
				
			}
			if ( tree[2*currentIndex + 2][1] > best){
				best = tree[2*currentIndex + 2][1];
				bestNode = 2*currentIndex + 2;
			}
			if ( tree[2*currentIndex + 1][0] > best)
				pq.push(tree[2*currentIndex + 1]);
			if ( tree[2*currentIndex + 2][0] > best)
				pq.push(tree[2*currentIndex + 2]);

		}
	}
	for (int i = 0; i < n; i++){
		if (path[bestNode][i] == 1)
			numItems++;
	}
	cout << n;
	cout << ",";
	cout << best;
	cout << ",";
	cout << numItems;	
	cout << '\n';

	cout << nodesVisited - 1;
	cout << ",";
	cout << leafsVisited;
	cout << '\n';

	for (int i = 0; i < n; i++){
		if (path[bestNode][i] == 1){
			cout << unsortedItems[i][0];
			cout << ",";
			cout << unsortedItems[i][1];
			cout << '\n';
		}
	}
	//printf("%d", bestNode);
	return 0;

}
