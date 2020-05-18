//Random Selection using quicksort

#include<iostream>
#include<vector>
using namespace std;

void Swap(vector<int>& , int , int );

void RSort(vector<int>& arr, int s, int N,int selection) {
	
	if (N - 1 > s) {
		int m;
		int p = arr[s];
		int i = s+1;
		for (int j = s+1; j < N; j++) {
			if (arr[j] < p) {
				Swap(arr, j, i);
				i++;
			}
		}
		Swap(arr, s, i - 1);
		
		//Select the given number
			//If required number of left- Sort left part
		if (selection < i) {   
			RSort(arr, s, i - 1,selection);
		}
			//If required number of right-sort right part
		else if (selection > i) {
			RSort(arr, i, N,selection);
		}
	}
}

void Swap(vector<int>& ar, int a, int b) {
	int k = ar[a];
	ar[a] = ar[b];
	ar[b] = k;
}

void PrintVector(vector<int> arr) {
	int n = arr.size();
	for (int i = 0; i < n; i++) {
		cout << arr[i] << " ";
	}
	cout << endl;
}
int main() {
	vector<int>List = {11,5,4,10,34,1,27,7,8,3};
	//Select median
	int m = 2;
	RSort(List, 0,List.size(),m);
	cout << "The number you're looking for is:" << List[m-1] << endl;
	PrintVector(List);
}