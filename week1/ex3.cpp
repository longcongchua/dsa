#include <iostream>
using namespace std;

void generateBinaryStrings(int n, string str){
    if(str.length() == n){
        cout << str << endl; // nếu như độ dài của chuỗi bằng n thì in ra chuỗi
        return ;
    }
    generateBinaryStrings(n, str +"0");//gọi đệ quy với độ dài chuỗi có giá trị 0
    generateBinaryStrings(n, str +"1");//gọi đệ quy với độ dài chuỗi có giá trị 11
}

int main(){
    int n;cin >> n;
    generateBinaryStrings(n, "");
    return 0;
}
/*gọi đệ quy lúc đầu thêm 0 vào chuỗi sau đó cứ tiếp tục đến khi độ dài chuỗi bằng n
nếu độ dài chuỗi đạt yêu cầu thì in ra chuỗi đó và gọi đến vị trí mà nó dừng đó là chỗ +"0" và chuẩn bị thử với +"1"*/
 