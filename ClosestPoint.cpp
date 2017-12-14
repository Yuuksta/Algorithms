#include <iostream>
#include <cmath>
#include <algorithm>
#define max 100
using namespace std;

struct Point{
    int x;
    int y;
    int operator=(Point q){
        x=q.x;
        y=q.y;
        return 0;
    }
};

struct PointList{   
    Point List[max];
    int num;
    PointList(){
        num = 0;
    }
};

double Distance(Point a, Point b);
bool compare_x(Point a, Point b);
bool compare_y(Point a, Point b);
double FindClosest(PointList xList, PointList yList);
double min(int a, int b);

int main (){
    PointList PList;
    PointList PxList,PyList;
    cout << "input number of point:" << endl;
    cin >> PList.num;
    int i;
    double mid,d;
    for(i = 0;i < PList.num;i++){ //initial point
        cin >> PList.List[i].x;
        cin >> PList.List[i].y;
    }
    for(i = 0;i < PList.num;i++){
        PxList.List[i] = PList.List[i];
        PxList.num++;
        PyList.List[i] = PList.List[i];
        PyList.num++;
    }
    sort(PxList.List,PxList.List + PxList.num,compare_x);
    sort(PyList.List,PyList.List + PyList.num,compare_y);
    //now px and py is sorted
    d = FindClosest(PxList,PyList);
    cout << d << endl;
    return 0;
}

double FindClosest(PointList xList, PointList yList){
    double dis = 10000, dis_temp;
    int count = 0,i,j;
    if(xList.num == 1){
        //cout << "return 1";
        return dis;
    }
    if(xList.num == 2){
        //cout << "return 2";
        return Distance(xList.List[0],xList.List[1]);
    }
    double mid = (xList.List[0].x + xList.List[xList.num - 1].x)/2;
    PointList xLeft,xRight,yLeft,yRight,temp;
    for(i = 0;i < xList.num;i++){ //make son xList sorted
        if(xList.List[i].x <= mid){
            xLeft.List[xLeft.num++] = xList.List[i];
        }
        else xRight.List[xRight.num++] = xList.List[i];
    } 
    for(i = 0;i < yList.num;i++){ //make son yList sorted
        if(yList.List[i].x <= mid){
            yLeft.List[yLeft.num++] = yList.List[i];
        }
        else yRight.List[yRight.num++] = yList.List[i];
    }
    double dis_left = FindClosest(xLeft,yLeft);
    double dis_right = FindClosest(xRight,yRight);
    dis = min(dis_left,dis_right);
    for(i = 0;i < yList.num;i++){
        if(fabs(yList.List[i].x - mid) <= dis){
            temp.List[temp.num++] = yList.List[i];
        }
    }
    //now temp is a sorted array within the strip according to y
    for(i = 0;i < temp.num;i++){
        for(j = i+1; temp.List[j].y - temp.List[i].y < dis; j++){
            dis_temp = Distance(temp.List[j],temp.List[i]);
            if(dis_temp < dis){
                dis = dis_temp;
            }
        }
    }
    return dis;
}


bool compare_x(Point a, Point b){
    if(a.x < b.x) return 1;
    else return 0;
}

bool compare_y(Point a, Point b){
    if(a.y < b.y) return 1;
    else return 0;
}

double min(double a,double b){
    if(a < b) return a;
    else return b;
}

double Distance(Point a, Point b){
    return sqrt((a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y));
}