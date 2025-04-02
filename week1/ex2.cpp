#include <iostream>
using namespace std;

int Factorial(int n){
    if (n <=1 ){
        return 1;// nếu n bé hơn hoặc bằng 1, trả về 1
    }
    return n * Factorial (n -1); // gọi hàm đệ quy lấy n nhân với n-1
}

int main(){
    int n = 4;
    cout << Factorial (n); // in ra đáp án
    return  0;
}