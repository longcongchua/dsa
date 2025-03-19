#include <iostream>
using namespace std;

void selectionsort(int a[], int n){
    for (int i =0; i< n; i++){
        int min = i  ;
        for (int j = i +1; j < n; j++){
            if(a[j] < a[min]){
                min = j;
            }
        }
        swap(a[min] , a[i]);
        }
}

int main(){
    int a[9] = {4,5,8,3,7,2,9,1,0};
    selectionsort(a, 9);
    for (int i = 0; i< 9 ; i ++ ){
        cout << a[i] << " ";
    }
return 0;
}