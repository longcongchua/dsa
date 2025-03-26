#include <iostream>
using namespace std;

void HNtower(int n, char cotA, char cotB , char cotC){
    if(n == 1){
        cout << "move disk "<< n << " from " << cotA << " to " << cotC << endl;// nếu n=1 chuyển đĩa từ A sang C
        return;
    }
    HNtower(n -1, cotA,cotC,cotB);// gọi đệ quy để chuyển n-1 đĩa từu cột A sang cột B, tiếp theo chuyển đĩa thứ n sang cột C
    cout << "move disk "<< n << " from " << cotA << " to " << cotC <<endl;
    HNtower(n -1 , cotB , cotA ,cotC);// gọi đệ quy để chuyển n-1 cột từ đĩa trung gian B sang đĩa C

}
int main(){
    int n = 3;
    HNtower(n, 'A', 'B' , 'C');
    return 0;
}