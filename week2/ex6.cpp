#include <iostream>
using namespace std;

int checksum(int a[], int n, int target){
    for (int i =0; i< n; i++){
        for(int j = i+1; j < n; j++){
            if (a[i] + a[j] == target){
                    return 1;
            }
        }
    }
    return -1;
}

int main(){
    int n;cin>>n;
    int *a = new int[n];
    for (int i =0; i< n; i++){
        cin >> a[i];
    }
    int target;cin >> target;
    int res = checksum(a, n, target);
    if(res == 1){
        cout << "YES";
    }
    else{cout<<"NO";
    }
    return 0;
}