//Strongly connected components using Kosaraju's algorithm- 2 DFS passes, first with grid revered to get finishing times and second on original map
#include<iostream>
#include<vector>
#include<stdlib.h>
#include<string.h>

using namespace std;

struct node {
	int data;
	node* prev;
	node* next;
};

class Stack {
private:
	node* head, *tail;

public:
	Stack() {
		head = NULL;
		tail = NULL;
	}
	void push(int value) {
		node* temp = new node;
		temp->data = value;
		temp->next = NULL;
		if (isEmpty()) {
			temp->prev = NULL;
			head = temp;
			tail = temp;
		}
		else {
			tail->next = temp;
			temp->prev = tail;
			tail = temp;
		}
	}
	int pop() {
		if (isEmpty()) {
			cout << "Stack is empty, nothing to remove" << endl;
		}
		else if (head->next == NULL) {
			int value=head->data;
			head = NULL;
			tail = head;
			return value;
		}
		else {
			int value=tail->data;
			node* temp = new node;
			temp = tail->prev;
			tail = temp;
			delete tail->next;
			temp->next = NULL;	//Just to make sure its not pointing to garbage value
			return value;
		}
	}
	void display() {
		if (isEmpty()) {
			cout << "Stack is empty" << endl;
			return;
		}
		node* temp = new node;
		temp = head;
		while (temp != NULL) {
			cout << temp->data << " ";
			temp = temp->next;
		}
		cout << endl;
	}
	bool isEmpty() {
		if (head == NULL) {
			return 1;
		}
		return 0;
	}
};

void DFS_Loop1(vector<vector<int>>&, vector<int>&, Stack&);
void DFS_inner(vector<vector<int>>&, vector<int>&, int);
void remap_gr(vector<vector<int>>& , vector<vector<int>>&) ;
void DFS_Loop2(vector<vector<int>>&, vector<int>&);
void DFS_inner2(vector<vector<int>>&, vector<int>&, int);
void quickSort(vector<int>& ,int,int);
void printVector2D(vector<vector<int>>&);
void Swap(vector<int>&, int, int);
void printVector1D(vector<int>& );


//Global variables
int t = 0, s = 0;
vector<int>finish_time = {};
vector<int>precedence = {};
int num=0;

void DFS_Loop1(vector<vector<int>>& arr1,vector<int>& E, Stack& list) {

	while (!list.isEmpty()) {
		int v1 = list.pop();
		if (E[v1 - 1] == 0) {
			DFS_inner(arr1, E, v1);
		}
	}
    
}

void DFS_inner(vector<vector<int>>& arr1,vector<int>& E, int v) {
	//Find all findable vertices from vertex v
	E[v - 1] = 1;
	vector<int> v2_options = arr1[v - 1];
	//v2_options.erase(v2_options.begin());
	int v2 = 0;
	for (int i = 1; i < v2_options.size(); i++) {
		v2 = v2_options[i];
		if (E[v2 - 1] == 0) {
			E[v2 - 1] = 1;
			DFS_inner(arr1, E, v2);
		}
	}
	t++;
	finish_time[v - 1] = t;
	//precedence.push_back(v);
}

void remap_gr(vector<vector<int>>& r_gr, vector<vector<int>>& gr) {
	//Remap graph according to finishing times
	int n = r_gr.size();
	int n2;

	int row, val;
	for (int i = 0; i < n; i++) {
		n2 = r_gr[i].size();
		for (int j = 1; j < n2; j++) {
			//Element to add- arr1[i][0] in row arr1[i][j] of gr
			row = finish_time[r_gr[i][j]-1]-1;
			val = finish_time[r_gr[i][0]-1];
			gr[row].push_back(val);
		}
	}
}

void DFS_Loop2(vector<vector<int>>& arr1, vector<int>& arr2) {
	int n = arr1.size();
	int count = 0;
    vector<int> scc;

	for (int i = n; i > 0; i--) {
        int v1=i;
		if (arr2[v1 - 1] == 0) {
			num=1;
			DFS_inner2(arr1, arr2, v1);
            if(num>100){
                scc.push_back(num);
            }
			//cout<<num<<endl;
			count++;
		}
	}
    // for(int i=0;i<scc.size();i++){
    //     cout<<scc[i]<<endl;
    // }
    int n2=scc.size();
    quickSort(scc,0,n2);
    for(int i=1;i<6;i++){
        cout<<scc[n2-i]<<endl;
    }
	cout << "SCCs:" << count << endl;
}

void quickSort(vector<int>& arr,int s,int N){
    //Get the largest 5 values
    if(N-1>s){
        int n=arr.size();
        int p=arr[s];
        int i=s+1;
        for(int j=s+1;j<N;j++){
            if(arr[j]<p){
                Swap(arr,i,j);
                i++;
            }
        }
        Swap(arr,s,i-1);
        if(i>n-6){
        quickSort(arr,s,i);
        }
        else{
        quickSort(arr,i,N);
        }
    }

}

void Swap(vector<int>& arr, int a, int b){
    int k=arr[a];
    arr[a]=arr[b];
    arr[b]=k;
}

void DFS_inner2(vector<vector<int>>& arr1, vector<int>& E, int v) {
	//Find all findable vertices from vertex v
	E[v - 1] = 1;
	
	vector<int> v2_options = arr1[v - 1];
	v2_options.erase(v2_options.begin());
	int v2 = 0;
	for (int i = 0; i < v2_options.size(); i++) {
		v2 = v2_options[i];
		if (E[v2 - 1] == 0) {
			num++;
			E[v2 - 1] = 1;
			DFS_inner2(arr1, E, v2);
		}
	}
	
}



int main() {
	// vector<vector<int>>Graph = { {1,4},{2,8},{3,6},{4,7},{5,2},{6,8},{7,1},{8,5,6},{9,3,7} };
	// vector<vector<int>>Graph_rev = { {1,7},{2,5},{3,9},{4,1},{5,8},{6,3,8},{7,4,9},{8,2},{9,6} };
	// int n = Graph.size();

	//Reading input file
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
	while(fgets(line, 1000, fp)!=NULL){
		char* pch = strtok(line, "\t \n");
		int u = atoi(pch);

		pch = strtok(NULL, "\t \n");
		while (pch != NULL)
		{
			int v = atoi(pch);
			//Enter here what you want to do with u and v
			//Graph[u-1].push_back(v);
			Graph_rev[v-1].push_back(u);

			pch = strtok(NULL, "\t \n");
		}
	}


	//Solve
	finish_time.resize(n, 0);
	vector<int> Explored = {};
	Explored.resize(n, 0);
    Stack list;
	for (int i = 1; i<=n; i++) {
		list.push(i);
	}
	DFS_Loop1(Graph_rev, Explored,list);
	vector<int>E = {};
	E.resize(n, 0);
    remap_gr(Graph_rev,Graph);
	DFS_Loop2(Graph, E);
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
void printVector1D(vector<int>& arr) {
	int n = arr.size();
	for (int i = 0; i < n; i++) {
		cout << arr[i] << " ";
	}
	cout << endl;
}