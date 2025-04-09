#ifndef TEST
#define TEST

template <class T>
void HoanVi(T &a, T &b);
void GenerateRandomData(int a[], int n);
void GenerateSortedData(int a[], int n);
void GenerateReverseData(int a[], int n);
void GenerateNearlySortedData(int a[], int n);
void GenerateData(int a[], int n, int dataType);

void selectionSort(int a[], int n);
void insertionSort(int a[], int n);
void bubbleSort(int a[], int n);
void shakerSort(int a[], int n);
void shellSort(int a[], int n);
void heapSort(int a[], int n);
void mergeSort(int a[], int l, int r);
void quickSort(int a[], int low, int high);
void countingSort(int a[], int n);
void radixSort(int a[], int n);
void flashSort(int a[], int n);

#endif
