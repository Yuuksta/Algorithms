#include <iostream>
#include <cmath>
#include <cstring>

using namespace std;

class MyString:public string{
    public:
        int weight;
        int sign;
        MyString(){
            weight = 0;
            sign = 0;
        }
        MyString Assign(string s){
            for(int i = 0; i < s.length();i++)
                string::insert(string::length(),1,s[i]);
            return *this;
        }
};

int Min(int a,int b);
int Max(int a,int b);
MyString IMul(MyString num1, MyString num2);
MyString Mul(MyString num1, MyString num2);
MyString Sub(MyString num1, MyString num2);
MyString Add(MyString num1, MyString num2);
MyString RemoveZero(MyString number);
MyString AddZero(MyString number, int len);

int main (){
    MyString number1, number2,temp;
    cout << "Please input number1: " << endl;
    cin >> number1;
    cout << "Please input number2: " << endl;
    cin >> number2;
    if(number1[0] == '-'){
        number1.sign = 1;
        number1.erase(0,1);
    }
    if(number2[0] == '-'){
        number2.sign = 1;
        number2.erase(0,1);
    }
    cout << "Add Answer: ";
    if(Add(number1,number2).sign == 1) cout << "-";
    cout << Add(number1,number2) << endl;

    cout << "Sub Answer: ";
    if(Sub(number1,number2).sign == 1) cout << "-";
    cout << Sub(number1,number2) << endl;
    cout << "Mul Answer: ";
    if(IMul(number1,number2).sign == 1) cout << "-";
    cout << IMul(number1,number2) << endl;
    return 0;   
}

MyString IMul(MyString num1, MyString num2){
    return RemoveZero(Mul(num1,num2));
}
MyString Mul(MyString num1, MyString num2){ 
    MyString temp1,temp2,temp3,answer,A,B,C,D;
    int sign;
    if(num1.sign ^ num2.sign == 1) sign = 1; // judge number's sign
    else sign = 0;
    num1.sign = 0;
    num2.sign = 0;
    int mid,temp_int,max_len;
    max_len = Max(num1.length(),num2.length());
    if(num1.length() == 1 && num2.length() == 1){
        if(num1[0] == '0' || num2[0] == '0'){
            answer.insert(0,1,'0');
            answer.sign = sign;
            return answer;
        }
        else{
            temp_int = (int(num1[0] - 48)) * (int(num2[0] - 48));
            answer.insert(0,1,(temp_int%10) + 48);
            answer.insert(0,1,(temp_int/10) + 48);
            answer.sign = sign;
            return answer;
        }
    }
    else{
        //Align two numbers
        if(max_len%2 == 1) max_len++;
        num1 = AddZero(num1,max_len);
        num2 = AddZero(num2,max_len);
        mid = num1.length()/2;
        //divide two numbers into 4 parts
        A.Assign(num1.substr(0,mid));
        B.Assign(num1.substr(mid,mid));
        C.Assign(num2.substr(0,mid));
        D.Assign(num2.substr(mid,mid));
        temp1 = Mul(A,C);
        temp1.weight = num1.length();
        temp3 = Mul(B,D);
        temp3.weight = 0;
        answer = Add(temp1,temp3);
        temp1.weight = 0;
        temp2 = Add(temp1,temp3);
        temp2 = Add(Mul(AddZero(Sub(A,B),mid),AddZero(Sub(D,C),mid)),temp2);
        temp2.weight = mid;
        answer = Add(answer,temp2);
        answer.sign = sign;
        return answer;
    }
}
MyString Add(MyString num1, MyString num2){
    int len;
    char carry = 0,c1 = '0',c2 = '0';
    MyString temp;
    int i;
    //when input have negative
    if(num1.sign == 0 && num2.sign == 1){
        num2.sign = 0;
        return Sub(num1,num2);
    }
    else if(num1.sign == 1 && num2.sign == 0){
        num1.sign = 0;
        return Sub(num2,num1);
    }
    else if(num1.sign == 1 && num2.sign == 1){
        temp.sign = 1;
    }
    //restore numbers
    for(i = 0;i < num1.weight;i++){
        num1.append("0");
    }
    for(i = 0;i < num2.weight;i++){
        num2.append("0");
    }
    len = Max(num1.length(),num2.length());
    //start add
    for(i = 1;i <= len;i++){
        if(num1.length() >= i){
            c1 = num1[num1.length()-i];
        }
        else c1 = 48;
        if(num2.length() >= i){
            c2 = num2[num2.length()-i];
        }
        else c2 = 48;

        if(c1 + c2 + carry > 105){ // need to carry
            temp.insert(0,1,c1 + c2 + carry - 58);
            carry = 1;
        }
        else{
            temp.insert(0,1,c1 + c2 + carry - 48);
            carry = 0;
        }
        if(i == len && carry == 1){
            temp.insert(0,1,'1');
        }
    }
    temp.weight = 0;
    return temp;
}

MyString Sub(MyString num1, MyString num2){
    int i;
    MyString temp;
    char borrow = 0,c1,c2;
    //when input have negative
    if(num1.sign == 0 && num2.sign == 1){
        num2.sign = 0;
        return Add(num1,num2);
    }
    else if(num1.sign == 1 && num2.sign == 0){
        num2.sign = 1;
        return Add(num1,num2);
    }
    else if(num1.sign == 1 && num2.sign == 1){
        temp.sign = 1;
    }
    //restore numbers
    for(i = 0;i < num1.weight;i++){
        num1.append("0");
    }
    for(i = 0;i < num2.weight;i++){
        num2.append("0");
    }
    //start sub
    int len = Max(num1.length(), num2.length());
    //when two numbers are in different length
    for(i = 1;i <= len;i++){
        if(num1.length() >= i){
            c1 = num1[num1.length()-i];
        }
        else c1 = 48;
        if(num2.length() >= i){
            c2 = num2[num2.length()-i];
        }
        else c2 = 48;
        if(num1.length() > num2.length()){
            temp.sign = 0;
            if(c1 - borrow >= c2 ){
                temp.insert(0,1,c1 - borrow - c2 + 48);
                borrow = 0;
            }
            else{
                temp.insert(0,1,c1 - borrow - c2 + 58);
                borrow = 1;
            }
        }
        else if(num1.length() < num2.length()){
            temp.sign = temp.sign ^ 1;
            if(c2 - borrow >= c1 ){
                temp.insert(0,1,c2 - borrow - c1 + 48);
                borrow = 0;
            }
            else{
                temp.insert(0,1,c2 - borrow - c1 + 58);
                borrow = 1;
            }
        }
    }
    //when two numbers are in same length
    if(num1.length() == num2.length()){
        for(i = 1;i <= num1.length();i++){

            if(num1.length() >= i){
                c1 = num1[num1.length()-i];
            }
            else c1 = 48;
            if(num2.length() >= i){
                c2 = num2[num2.length()-i];
            }
            else c2 = 48;

            if(c1 - borrow >= c2 ){
                temp.insert(0,1,c1 - borrow - c2 + 48);
                borrow = 0;
            }
            else{
                temp.insert(0,1,c1 - borrow - c2 + 58);
                borrow = 1;
            }
        }
        if(borrow == 1){ //means answer is negative
            borrow = 0;  //so we need to sub again
            temp.sign = temp.sign ^ 1;
            temp.erase(0,temp.length());
            for(i = 1;i <= num1.length();i++){
                if(num1.length() >= i){
                    c2 = num1[num1.length()-i];
                }
                else c2 = 48;
                if(num2.length() >= i){
                    c1 = num2[num2.length()-i];
                }
                else c1 = 48;
                if(c1 - borrow >= c2 ){
                    temp.insert(0,1,c1 - borrow - c2 + 48);
                    borrow = 0;
                }
                else{
                    temp.insert(0,1,c1 - borrow - c2 + 58);
                    borrow = 1;
                }
            }    
        }
    }
    temp.weight = 0;
    return RemoveZero(temp);
}
int Min(int a, int b){
    if(a > b) return b;
    else return a;
}
int Max(int a, int b){
    if(a < b) return b;
    else return a;
}

MyString RemoveZero(MyString number){
    while(number.length() > 1 && number[0] == '0') number.erase(0,1);
    if(number.length() == 1 && number[0] == '0') number.sign = 0;
    return number;
}

MyString AddZero(MyString number, int len){
    while(number.length() < len) number.insert(0,1,'0');
    return number;
}