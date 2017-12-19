#include <iostream>

using namespace std;

int n; // node number of the tree
int root[100][100]; // root table

void PrintOptimalBST(int i, int j, int r);
int main (){
    int i,j;
    for(i = 0; i <= n; i++){
        for(j = 0;j <= n;j++){
            root[i][j] = 0;
        }
    }
    cout << "PLease input the number of node: " << endl;
    cin >> n; 
    cout << "Please input each subTree's root: " << endl;
    for(i = 1; i <= n; i++){
        for(j = i;j <= n;j++){
            cin >> root[i][j];
        }
    }
    PrintOptimalBST(1,n,root[1][n]);
    return 0;
}

void PrintOptimalBST(int i, int j, int r){
    int ChildRoot = root[i][j];
    if(ChildRoot == root[1][n]){
        cout << "Root of the tree is " << ChildRoot << endl;
        PrintOptimalBST(i,ChildRoot - 1, ChildRoot); //print leftchild subtree
        PrintOptimalBST(ChildRoot + 1, j, ChildRoot); //print rightchild subtree
        return;
    }
    else{
        if (j < i - 1){  
            return;  
        }  
        else if (j == i - 1){  
            if (j < r) cout << "d" << j << " is k" << r << "'s leftChild" << endl;
            else cout << "d" << j << " is k" << r << "'s rightChild" << endl;  
            return;  
        }  
        else{  
            if (ChildRoot < r) cout << "k" << ChildRoot << " is k" << r << "'s leftChild" << endl;   
            else cout << "k" << ChildRoot << " is k" << r << "'s rightChild" << endl;  
        }  
        PrintOptimalBST(i,ChildRoot - 1,ChildRoot);  
        PrintOptimalBST(ChildRoot + 1,j,ChildRoot);
    }
}