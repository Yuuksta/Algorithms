#include <iostream>
#include <stdlib.h>

#define MAX 100
#define INF 99999

using namespace std;

int D[MAX][MAX],P[MAX][MAX];
void FloydWarshell(int W[MAX][MAX],int n);

int main (){
    int W[MAX][MAX],n,i,j;
    char temp[3];
    cout << "please input size of matrix: " << endl;
    cin >> n;
    cout << "input the matrix: " << endl;
    for(i = 1;i <= n;i++){
        for(j = 1;j <= n;j++){
            cin >> temp;
            if(temp[0] == 'f') W[i][j] = INF;
            else W[i][j] = atoi(temp);
        }
    }
    cout << "" << endl;
    FloydWarshell(W,n);
    cout << "D matrix: " << endl;
    for(i = 1;i <= n;i++){
        cout << "" << endl;
        for(j = 1;j <= n;j++){
            cout << D[i][j];
            if(D[i][j] >= 0) cout << "   ";
            else cout << "  ";
        }
    }
    cout << "" <<endl;
    cout << "P matrix: " << endl;
    for(i = 1;i <= n;i++){
        cout << "" << endl;
        for(j = 1;j <= n;j++){
            if(P[i][j] == INF) cout << "NIL ";
            else cout << P[i][j] << "   ";
        }
    }
    cout << "" <<endl;
    return 0;
}

void FloydWarshell(int W[MAX][MAX],int n){
    int D_count = 0;
    int k,i,j;
    for(i = 1;i <= n;i++){
        for(j = 1;j <= n;j++){
            D[i][j] = W[i][j];
        }
    }
    for(i = 1;i <= n;i++){
        for(j = 1;j <= n;j++){
            if(i == j || W[i][j] == INF) P[i][j] = INF;
            else P[i][j] = i;
        }
    }
    for(k = 1;k <= n;k++){
        for(i = 1;i <= n;i++){
            for(j = 1;j <= n;j++){
                if(D[i][k] + D[k][j] < D[i][j]) P[i][j] = P[k][j];
                if(D[i][k] + D[k][j] < D[i][j]) D[i][j] = D[i][k] + D[k][j];
            }
        }
    }
    return;
}