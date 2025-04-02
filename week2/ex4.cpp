#include <iostream>
using namespace std;

bool canShip(int weights[], int n, int capacity, int days) {// Hàm kiểm tra liệu có thể vận chuyển hàng với tải trọng trong ngày không
    int currentLoad = 0; 
    int requiredDays = 1;

    for (int i = 0; i < n; i++) {
        if (currentLoad + weights[i] > capacity) {
            requiredDays++;  
            currentLoad = 0;
        }
        currentLoad += weights[i];
    }
    return requiredDays <= days;
}

int shipWithinDays(int weights[], int n, int days) {// Tìm tải trọng tối thiểu
    int left = weights[0];
    int right = 0;

    for (int i = 0; i < n; i++) {// Tìm max weights và sum weights
        if (weights[i] > left){ 
        left = weights[i];  // Lấy phần tử lớn nhất
        }
        right += weights[i];  
    }

    while (left < right) {//hàm thay đổi tải trọng
        int mid = left + (right - left) / 2;

        if (canShip(weights, n, mid, days)) {
            right = mid;  
        } else {
            left = mid + 1; 
        }
    }
    return left;
}

int main() {
    int n, days;
    cin >> n;
    int weights[n];
    
    for (int i = 0; i < n; i++) {
        cin >> weights[i];
    }
    
    cin >> days;
    cout << shipWithinDays(weights, n, days) << endl;

    return 0;
}
