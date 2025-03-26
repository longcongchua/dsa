#include <iostream> 
using namespace std;

int Fibonaci(int n){
    if (n <= 1){
        return n;// nếu n bé hơn hoặc bằng 1 thì trả về n
    }
    return Fibonaci(n -1) + Fibonaci(n -2); // gọi hàm đệ quy của dãy số Fibonaci
}

int main(){
    int n ; cin >>n ;
    cout << Fibonaci(n);
    return 0;
}