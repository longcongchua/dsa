#include  <iostream>
using namespace std;

int sentinal_search(int a[], int n , int target ){
    if( n == 0){
        return -1;// nếu n =0, mảng rỗng
    }

    int i =0;

    if(target != a[n-1]){// kiểm tra nếu phần tử cần tìm nằm cuối dãy trả về giá trị i
        int x = a[n-1];
        a[n-1] = target;

        while (a[i] != target){
            i++; // vòng lặp xét nêu giá trị cần xét bằng với target thì dừng vòng lặp
        }

        a[n - 1] = x;

        if(i < n-1 ){
            return i;// nếu i nhỏ hơn độ dài mảng nghĩa là tìm thấy giá trị
        }
        else {
            return -1;
        }

    }
    else {
        return n-1;// nếu giá trị cuối bằng giá trị cần tìm trả về chỉ số
    }
    return -1;
}

int main(){
    int n;
    cin >> n;
    int *a = new int[n];
    for(int i =0; i < n; i++){
        cin >> a[i];
    }
    int tar;
    cin >> tar;
    int res = sentinal_search(a, n, tar);
    if(res != -1){
        cout << res ;
    }
    else{
        cout << "not found";
    }
    return 0;
    delete[] a;
}