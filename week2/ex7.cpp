#include <iostream>
#include <vector>
using namespace std;

void bubbleSort(vector<int>& arr) {// Hàm sắp xếp mảng 
    for (int i = 0; i < arr.size() - 1; ++i) { 
        for (int j = 0; j < arr.size() - i - 1; ++j) {
            if (arr[j] > arr[j + 1]) {
                // Hoán đổi hai phần tử
                int tmp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = tmp;
            }
        }
    }
}

vector<vector<int>> SumofThreeNum(vector<int>& arr) {
    vector<vector<int>> result;
    bubbleSort(arr);
    for (int i = 0; i < arr.size() - 2; ++i) {// Kiểm tra điều kiện phần tử trùng lặp
        if (i == 0 || arr[i] != arr[i - 1]) {
            int left = i + 1, right = arr.size() - 1;

            while (left < right) {
                int sum = arr[i] + arr[left] + arr[right];
                if (sum == 0) {
                    result.push_back({arr[i], arr[left], arr[right]});

                    // Bỏ qua các phần tử trùng lặp
                    while (left < right && arr[left] == arr[left + 1]){
                        ++left;
                    }
                    while (left < right && arr[right] == arr[right - 1]){
                        --right;
                    }   
                    ++left;
                    --right;
                } else if (sum < 0) {
                    ++left; // Di chuyển con trỏ trái để tăng tổng
                } else {
                    --right; // Di chuyển con trỏ phải để giảm tổng
                }
            }
        }
    }

    return result;
}

int main() {
    vector<int> arr = {-1, 0, 1, 2, -1, -4};
    vector<vector<int>> res = SumofThreeNum(arr);
    for (int i = 0; i < res.size(); ++i) {
        cout << "[" << res[i][0] << ", " << res[i][1] << ", " << res[i][2] << "]" << endl;
    } 
    return 0;
}