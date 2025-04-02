#include <iostream>
#include <vector>
using namespace std;

int findMinarr(vector<int>& arr) {
    int left = 0, right = arr.size() - 1;// tạo 2 con trỏ left và rightright

    while (left < right) {//dùng thuật toán binary search để giải quyết bài toántoán
        int mid = left + (right - left) / 2;
        
        if (arr[mid] > arr[right]) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }    
    return arr[left];
}

int main() {
    int n;
    cin >> n;
    vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    cout << findMinarr(arr) << endl;
    return 0;
}
