#include <iostream>
#include <vector>
using namespace std;

int linearSearch(const vector<int>& arr, int target) {
    for (size_t i = 0; i < arr.size(); ++i) {
        if (arr[i] == target) {
            return i;
        }
    }
    return -1;
}

int main() {
    vector<int> numbers = {1, 3, 5, 7, 9};
    int targetValue = 5;
    int index = linearSearch(numbers, targetValue);

    if (index != -1) {
        cout << index ;
    } else {
        cout << "-1";
    }
    return 0;
}