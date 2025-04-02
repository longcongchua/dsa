#include <iostream>
#include <vector>
using namespace std;

int minSubArrayLen(vector<int>& arr,int target ) {
    int n = arr.size();
    int left = 0;
    int sum = 0;
    int minLength = n + 1;
    
    for (int right = 0; right < n; right++) {// Thêm phần tử hiện tại vào tổng đang chạy
        sum += arr[right];
        while (sum >= target) {
            int currentLength = right - left + 1;
            if (currentLength < minLength) {
                minLength = currentLength;
            }
            sum -= arr[left];// Loại bỏ phần tử ngoài cùng bên trái và thu nhỏ cửa sổ
            left++;
        }
    }
    if (minLength <= n) {// nếu không tìm thấy dãy hợp lệ, trả về 0
        return minLength;
    } else {
        return 0;
    }
}

int main() {
    vector<int> arr = {2, 3, 1, 2, 4, 3};
    int target ;
    cin >> target;
    int res = minSubArrayLen(arr, target);
    cout << res << endl;  
    return 0;
}