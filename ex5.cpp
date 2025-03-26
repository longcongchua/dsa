#include <iostream>
using namespace std;


int Sort(int a[], int n) {
    if (n == 1 || n == 0){ //nếu mảng có 1 hoặc 0 phần tử thì mặc định mảng đã được sắp xếp
        return 1;
    }
    if (a[n - 1] < a[n - 2]){ //xét 2 phần tử liền kề bắt đầu từ cuối dãy trở về trước 
        return 0;
    }
    return Sort(a, n - 1);//gọi đệ quy với kích thước của mảng trừ 1 cho tới khi n = 1
}

int main() {
    int a[5] = {1, 2, 2, 4, 5}; 
    int res = Sort(a, 5);

    if (res == 1) {
        cout << "Mang da duoc sap xep";
    } else {
        cout << "Mang chua duoc sap xep";
    }

    return 0;
}
