#include <iostream>
#include <fstream>
#include <cmath>
#include <ctime>
#include "test.h"

using namespace std;

template <class T>
void HoanVi(T &a, T &b) {
    T x = a;
    a = b;
    b = x;
}

//----------------------------
void GenerateRandomData(int a[], int n) {
    srand((unsigned int)time(NULL));
    for (int i = 0; i < n; i++) {
        a[i] = rand() % n;
    }
}

void GenerateSortedData(int a[], int n) {
    for (int i = 0; i < n; i++) {
        a[i] = i;
    }
}

void GenerateReverseData(int a[], int n) {
    for (int i = 0; i < n; i++) {
        a[i] = n - 1 - i;
    }
}

void GenerateNearlySortedData(int a[], int n) {
    for (int i = 0; i < n; i++) {
        a[i] = i;
    }
    srand((unsigned int)time(NULL));
    for (int i = 0; i < 10; i++) {
        int r1 = rand() % n;
        int r2 = rand() % n;
        HoanVi(a[r1], a[r2]);
    }
}

void GenerateData(int a[], int n, int dataType) {
    switch (dataType) {
        case 0: {
            GenerateRandomData(a, n);
            break;
        }
        case 1: {
            GenerateSortedData(a, n);
            break;
        }
        case 2: {
            GenerateReverseData(a, n);
            break;
        }
        case 3: {
            GenerateNearlySortedData(a, n);
            break;
        }
        default: {
            printf("Error: unknown data type!\n");
        }
    }
}

//----------------------------

void selectionSort(int a[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < n; j++) {
            if (a[j] < a[min_idx]) {
                min_idx = j;
            }
        }
        HoanVi(a[i], a[min_idx]);
    }
}

void insertionSort(int a[], int n) {
    for (int i = 1; i < n; i++) {
        int key = a[i];
        int j = i - 1;
        while (j >= 0 && a[j] > key) {
            a[j + 1] = a[j];
            j--;
        }
        a[j + 1] = key;
    }
}

void bubbleSort(int a[], int n) {
    for (int i = 0; i < n - 1; i++) {
        bool swapped = false;
        for (int j = 0; j < n - i - 1; j++) {
            if (a[j] > a[j + 1]) {
                HoanVi(a[j], a[j + 1]);
                swapped = true;
            }
        }
        if (!swapped) break;
    }
}

void shakerSort(int a[], int n) {
    bool swapped = true;
    int start = 0, end = n - 1;
    while (swapped) {
        swapped = false;
        for (int i = start; i < end; i++) {
            if (a[i] > a[i + 1]) {
                HoanVi(a[i], a[i + 1]);
                swapped = true;
            }
        }
        if (!swapped) break;
        swapped = false;
        end--;
        for (int i = end - 1; i >= start; i--) {
            if (a[i] > a[i + 1]) {
                HoanVi(a[i], a[i + 1]);
                swapped = true;
            }
        }
        start++;
    }
}

void shellSort(int a[], int n) {
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            int temp = a[i];
            int j;
            for (j = i; j >= gap && a[j - gap] > temp; j -= gap) {
                a[j] = a[j - gap];
            }
            a[j] = temp;
        }
    }
}

void heapify(int a[], int n, int i) {
    int largest = i, l = 2 * i + 1, r = 2 * i + 2;
    if (l < n && a[l] > a[largest]) largest = l;
    if (r < n && a[r] > a[largest]) largest = r;
    if (largest != i) {
        HoanVi(a[i], a[largest]);
        heapify(a, n, largest);
    }
}

void heapSort(int a[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(a, n, i);
    }
    for (int i = n - 1; i > 0; i--) {
        HoanVi(a[0], a[i]);
        heapify(a, i, 0);
    }
}

void merge(int a[], int l, int m, int r) {
    int n1 = m - l + 1, n2 = r - m;
    int *L = new int[n1], *R = new int[n2];
    for (int i = 0; i < n1; i++) L[i] = a[l + i];
    for (int i = 0; i < n2; i++) R[i] = a[m + 1 + i];
    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        a[k++] = (L[i] <= R[j]) ? L[i++] : R[j++];
    }
    while (i < n1) a[k++] = L[i++];
    while (j < n2) a[k++] = R[j++];
    delete[] L;
    delete[] R;
}

void mergeSort(int a[], int l, int r) {
    if (l < r) {
        int m = (l + r) / 2;
        mergeSort(a, l, m);
        mergeSort(a, m + 1, r);
        merge(a, l, m, r);
    }
}

int partition(int a[], int low, int high) {
    int mid = low + (high - low) / 2;
    if (a[low] > a[mid]) HoanVi(a[low], a[mid]);
    if (a[low] > a[high]) HoanVi(a[low], a[high]);
    if (a[mid] > a[high]) HoanVi(a[mid], a[high]);
    HoanVi(a[mid], a[high]);
    int pivot = a[high];
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (a[j] < pivot) {
            i++;
            HoanVi(a[i], a[j]);
        }
    }
    HoanVi(a[i + 1], a[high]);
    return i + 1;
}

void quickSort(int a[], int low, int high) {
    if (low < high) {
        int pi = partition(a, low, high);
        quickSort(a, low, pi - 1);
        quickSort(a, pi + 1, high);
    }
}

void countingSort(int a[], int n) {
    int maxVal = a[0];
    for (int i = 1; i < n; i++) {
        if (a[i] > maxVal) maxVal = a[i];
    }
    int* count = new int[maxVal + 1]();
    for (int i = 0; i < n; i++) count[a[i]]++;
    int index = 0;
    for (int i = 0; i <= maxVal; i++) {
        while (count[i]-- > 0) a[index++] = i;
    }
    delete[] count;
}

void countRadix(int a[], int n, int exp) {
    int* output = new int[n];
    int count[10] = {};
    for (int i = 0; i < n; i++) count[(a[i] / exp) % 10]++;
    for (int i = 1; i < 10; i++) count[i] += count[i - 1];
    for (int i = n - 1; i >= 0; i--) output[--count[(a[i] / exp) % 10]] = a[i];
    for (int i = 0; i < n; i++) a[i] = output[i];
    delete[] output;
}

void radixSort(int a[], int n) {
    int maxVal = a[0];
    for (int i = 1; i < n; i++) if (a[i] > maxVal) maxVal = a[i];
    for (int exp = 1; maxVal / exp > 0; exp *= 10) {
        countRadix(a, n, exp);
    }
}

void flashSort(int a[], int n) {
    if (n == 0) return;
    int m = int(0.43 * n);
    int* L = new int[m]();
    int minVal = a[0], maxIdx = 0;
    for (int i = 1; i < n; i++) {
        if (a[i] < minVal) minVal = a[i];
        if (a[i] > a[maxIdx]) maxIdx = i;
    }
    if (a[maxIdx] == minVal) return;
    double c = double(m - 1) / (a[maxIdx] - minVal);
    for (int i = 0; i < n; i++) L[int(c * (a[i] - minVal))]++;
    for (int i = 1; i < m; i++) L[i] += L[i - 1];
    HoanVi(a[maxIdx], a[0]);
    int count = 0, i = 0, k = m - 1, t = 0;
    while (count < n) {
        while (i > L[k] - 1) k = int(c * (a[++i] - minVal));
        int y = a[i];
        while (i != L[k]) {
            k = int(c * (y - minVal));
            HoanVi(y, a[--L[k]]);
            count++;
        }
        a[i++] = y;
        count++;
    }
    for (int i = 1; i < n; i++) {
        int key = a[i], j = i - 1;
        while (j >= 0 && a[j] > key) {
            a[j + 1] = a[j];
            j--;
        }
        a[j + 1] = key;
    }
    delete[] L;
}
