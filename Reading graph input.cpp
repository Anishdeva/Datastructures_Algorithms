//Creating adjacency list using input from a graph (u,v)
#include<iostream>
#include<stdlib.h>
#include<string.h>
#include<vector>
#include<ctime>

using namespace std;

void printVector2D(vector<vector<int>>&);

int main() {
	int n;
	cout << "Enter number of nodes:";
	cin >> n;
	cin.clear();

	vector<vector<int>>Graph(n);
	vector < vector<int>>Graph_rev(n);
	for(int i=0;i<n;i++){
		Graph[i].push_back(i+1);
		Graph_rev[i].push_back(i+1);
	}
	//Using strtok
	char line[1000]="";
	FILE* fp= fopen("SCC.txt", "r");
	bool endReached=0;
	//for (int i = 1; i <= n; i++) {
	while(fgets(line, 1000, fp)!=NULL){

		//fgets(line, 1000, fp);
		char* pch = strtok(line, "\t \n");
		int u = atoi(pch);

		pch = strtok(NULL, "\t \n");
		while (pch != NULL)				//Checks for end of string
		{
			int v = atoi(pch);
			//Enter here what you want to do with u and v
			Graph[u-1].push_back(v);
			Graph_rev[v-1].push_back(u);

			pch = strtok(NULL, "\t \n");
		}
	}

	printVector2D(Graph);
	//cout<<"Reversed Graph:"<<endl;
	//printVector2D(Graph_rev);
	return 0;
}

void printVector2D(vector<vector<int>>& arr) {
	int n1 = arr.size();
	for (int i = 0; i < n1; i++) {
		int n2 = arr[i].size();
		for (int j = 0; j < n2; j++) {
			cout << arr[i][j] << " ";
		}
		cout << endl;
	}

}