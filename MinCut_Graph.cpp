//Karger Min Cut
#include<iostream>
#include<vector>
#include<ctime>

using namespace std;

void printVector(vector<vector<int>>&);
void printVector1D(vector<int>&);
void ChooseEdge(vector<vector<int>>&, vector<vector<int>>&, vector<int>&, vector<int>&);
void ContractEdge(vector<vector<int>>&,vector<int>&, int, int, int, int);
void DefineSets(vector <vector<int>>&, vector<int>&, int, int);
int findSet(vector<vector<int>>, int);
void RefineMap(vector<vector<int>>&, vector<vector<int>>&);

void printVector(vector<vector<int>>& arr) {
	int n = arr.size();
	int m;
	for (int i = 0; i < n; i++) {
		m = arr[i].size();
		for (int j = 0; j < m; j++) {
			cout << arr[i][j] << " ";
		}
		cout << "\n";
	}
	cout << endl;
}

void printVector1D(vector<int>& arr) {
	int n = arr.size();
	for (int i = 0; i < n; i++) {
		cout << arr[i] << " ";
	}
	cout << endl;
}

int checkColumn(vector<vector<int>>arr, int a) {
	int n = arr.size();
	for (int i = 0; i < n; i++) {
		if (arr[i][0] == a) {
			return i;
		}
	}
}

void ChooseEdge(vector<vector<int>>& arr1, vector<vector<int>>& arr2, vector<int>& List,vector<int>& included) {

	if (arr1.size() > 2) {
		//Choose v1
		int r = rand() % List.size();
		int v1 = List[r];
		//Find row in arr1
		int row1 = checkColumn(arr1, v1);
		//Row 1 is always chosen from the first column, it must always exist
	//Choose v2
		//First check if any element from row1 still exists in List
		vector<int>v2options = {};
		int row1size = arr1[row1].size();
		int Listsize = List.size();
		bool found = 0;
		for (int i = 1; i < row1size; i++) {
			if (arr1[row1][i] != v1) {		//Cant choose v1 as v2
				for (int j = 0; j < Listsize; j++) {
					if (arr1[row1][i] == List[j]) {
						v2options.push_back(arr1[row1][i]);
						found = 1;
					}
				}
			}
		}
		if (!found) {
			ChooseEdge(arr1, arr2, List,included);
		}
		if (v2options.size() == 0) {
			ChooseEdge(arr1, arr2, List, included);
		}
		else {
			r = rand() % v2options.size();
			int v2 = v2options[r];
			int row2 = checkColumn(arr1, v2);
			//Sets
			DefineSets(arr2, included, v1, v2);

			//Testing
				//cout << "v1 options:";
				//printVector1D(List);
				//cout << "v1:" << v1 << endl;
				//cout << "v2 options:";
				//printVector1D(v2options);
				//cout << "v2:" << v2 << endl;
			ContractEdge(arr1, List, v1, v2, row1, row2);
			//printVector(arr1);
			//cout << "Sets:" << endl;
			//printVector(arr2);
			ChooseEdge(arr1, arr2, List, included);
		}
	}
	

}

void ContractEdge(vector<vector<int>>& arr1,vector<int>& List, int node1, int node2, int r1, int r2) {
	//Remove the edge from the array
	//Make the two nodes one- Add the elements from node 2 to node 1
	int n2 = arr1[r2].size();
	int num = 0;
	for (int i = 1; i < n2; i++) {
		num = arr1[r2][i];
		if (num != node1 && num != node2) {
			arr1[r1].push_back(num);
		}
	}
	arr1.erase(arr1.begin() + r2);

	//Also remove node2 from List
	for (int i = 0; i < List.size(); i++) {
		if (List[i] == node2) {
			List.erase(List.begin() + i);
			break;
		}
	}
	
}

void DefineSets(vector<vector<int>>& arr2, vector<int>& included, int e1, int e2) {
	//Place the two vertices into sets defined
		//Check if either of the two vertices exist in "Sets"
	bool found1 = 0, found2 = 0;
	vector<int>newset;
	for (int i = 0; i < included.size(); i++) {
		if (included[i] == e1) {
			found1 = 1;
		}
		if (included[i] == e2) {
			found2 = 1;
		}
	}
	int row1, row2;
	if (found1 && !found2) {	//Already have v1 in one of the sets
		included.push_back(e2);
		//Linear search to find row
		row1 = findSet(arr2, e1);	//Find which set e1 is in
		arr2[row1].push_back(e2);	//Put e2 in that set
	}
	else if (!found1 && found2) {	//Already have v2 in one of the sets
		included.push_back(e1);
		//Linear search to find row
		row2 = findSet(arr2, e2);	//Find which set e2 is in
		arr2[row2].push_back(e1);	//Put e1 in that set
	}
	else if (!found1 && !found2) {
		newset = { e1,e2 };
		arr2.push_back(newset);	//Create new set
		included.push_back(e1);
		included.push_back(e2);
	}
	else if (found1 && found2) {		//If they both exist in the set they should be in different rows/sets
		row1 = findSet(arr2, e1);
		row2 = findSet(arr2, e2);
		if (row1 != row2) {
			//Combine both rows
			int n2 = arr2[row2].size();
			for (int i = 0; i < n2; i++) {
				arr2[row1].push_back(arr2[row2][i]);
			}
			arr2.erase(arr2.begin() + row2);
		}
	}
}

//Finds an element a in complete 2D array and returns the row value else returns -1
int findSet(vector<vector<int>>arr2, int a) {
	int n1 = arr2.size();
	int n2;
	for (int i = 0; i < n1; i++) {
		n2 = arr2[i].size();
		for (int j = 0; j < n2; j++) {
			if (arr2[i][j] == a) {
				return i;
			}
		}
	}
	return -1;
}

void RefineMap(vector<vector<int>>& arr1, vector<vector<int>>& arr2) {
	int n1 = arr1.size();
	int n2 = arr2.size();
	bool found = 0;
	int k = 0, l = 0;
	for (int i = 0; i < n1; i++) {
		int n1a = arr1[i].size();
		for (int j = 0; j < n1a; j++) {
			found = 0; k = 0; l = 0;
			while (k < arr2.size()) { //k tracks row in sets and l tracks element of row in Set
				if (arr1[i][j] == arr2[k][l]) {
					arr1[i][j] = arr2[k][0];
					found = 1;
				}
				if (l == (arr2[k].size() - 1)) {
					k++;
					l = 0;
				}
				l++;
			}
		}
	}
}

int MinCut(vector<vector<int>>& arr, vector<vector<int>>& arr2) {
	RefineMap(arr, arr2);
	//Now there are only 2 nodes left- find min cut
	int v1 = arr[0][0];
	int v2 = arr[1][0];
	int count1 = 0, count2 = 0, min_count;

	for (int j = 1; j < arr[0].size(); j++) {
		if (arr[0][j] == v2) {
			count2++;
		}
	}
	for (int i = 1; i < arr[1].size(); i++) {
		if (arr[1][i] == v1) {
			count1++;
		}
	}
	if (count1 >= count2) {
		return count1;
	}
	return count2;

}

int main() {

	vector<vector<int>>Map = { {1,2,4},{2,1,3,4},{3,2,4},{4,1,2,3} };
	//vector<vector<int>> Map = { {1,2,3,4},{2,1,5,6,4},{3,1,5},{4,2,1,5},{5,2,3,4,6},{6,2,5} };
	/*vector<vector<int>> Map = {
	{1,14,21,11,3,10,17,20,22,24,25},
	{2,3,6,8,9,10,14,17,22,25 },
	{3,1,2,13,5,7,11,6,4,22,9,12,14,15,16,17,18,20,23},
	{4 ,3 ,23 ,15 ,11 ,17 ,7 ,22 ,12 ,20 ,25 ,18 ,24 },
	{5, 3, 19, 18, 10, 7, 9, 16, 22},
	{6 ,3 ,14 ,15 ,2 ,10 ,18 ,12 ,8 ,22 ,25 ,19 ,21 },
	{7, 3, 4,5, 25, 12, 16, 17, 20, 22},
	{8 ,6 ,17 ,21 ,15 ,22 ,2 ,20 ,10 ,23 },
	{9, 3, 11, 5, 12, 16, 14, 10, 2, 25, 18, 20},
	{10 ,1 ,5 ,6 ,8 ,9 ,2 ,19 ,16 ,17 ,24 ,18 ,22 ,23 },
	{11, 1, 3, 4, 9, 21, 12, 13, 14, 22},
	{12 ,3 ,4 ,6 ,9 ,23 ,7 ,11 ,16 ,20 ,25 ,21 ,18 ,19 },
	{13, 3, 11, 24, 16, 20, 21},
	{14 ,1 ,6 ,9 ,11 ,3 ,16 ,24 ,2 ,17 ,20 ,23 },
	{15, 4, 6, 8, 3, 25, 19, 20, 16, 21, 22, 24},
	{16 ,9 ,10 ,12 ,13 ,14 ,15 ,21 ,5 ,17 ,23 ,3 ,7 ,18 },
	{17, 4, 8, 10, 16, 3, 14, 7, 19, 1, 2 ,22, 23, 25},
	{18 ,5 ,6 ,23 ,12 ,22 ,9 ,10 ,24 ,20 ,16 ,3 ,4 ,21 },
	{19, 5, 10, 15, 17, 12, 6, 21, 22, 23},
	{20 ,4 ,8 ,12 ,15 ,18 ,9 ,13 ,22 ,1 ,3 ,14 ,7 ,25 },
	{21, 1, 8, 11, 12, 16, 25, 23, 6 ,15, 18, 13, 19, 24},
	{22 ,3 ,4 ,6 ,8 ,18 ,20 ,5 ,17 ,11 ,19 ,2 ,24 ,15 ,1 ,7 ,10 ,23 },
	{23, 4, 12, 16, 18, 21, 8, 10, 14, 25, 17, 3, 19, 22},
	{24 ,10 ,13 ,14 ,18 ,22 ,25 ,21 ,1 ,4 ,15 },
	{25, 4, 6, 7, 9, 12 ,15, 21, 23, 24, 1, 2, 17, 20},
	};*/
	vector<vector<int>>Cuts = {};
	vector<int>nodes = {};
	vector<int>included = {};
	for (int i = 0; i < Map.size(); i++) {
		nodes.push_back(Map[i][0]);
	}

	//printVector(Map);
	srand((unsigned)time(0));
	//cout << "Updated List:" << endl;
	int cut = 0, mincut = 1000;
	for (int i = 0; i < 100; i++) {
		ChooseEdge(Map, Cuts, nodes,included);
		cut = MinCut(Map, Cuts);
		//printVector(Map);
		if (cut < mincut) {
			mincut = cut;
		}
	}
	cout << "Min Cut is:" << mincut << endl;
}