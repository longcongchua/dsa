#include <iostream>
#include <fstream>
#include <cmath>
#include <ctime>
#include <cstring>
#include "test.h"

using namespace std;

int main(int argc, char* argv[]) {
    string algorithm, inputFile, outputFile;

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-a") == 0) {
            algorithm = argv[++i];
        } else if (strcmp(argv[i], "-i") == 0) {
            inputFile = argv[++i];
        } else if (strcmp(argv[i], "-o") == 0) {
            outputFile = argv[++i];
        }
    }

    ifstream inFile(inputFile);
    ofstream outFile(outputFile);

    if (!inFile || !outFile) {
        cout << "Khong the mo file" << endl;
        return 1;
    }

    while (!inFile.eof()) {
        int n;
        inFile >> n;
        if (inFile.fail()) break;

        int* a = new int[n];
        for (int i = 0; i < n; i++) {
            inFile >> a[i];
        }

        if (algorithm == "selection-sort") {
            selectionSort(a, n);
        }
        else if (algorithm == "insertion-sort") {
            insertionSort(a, n);
        }
        else if (algorithm == "bubble-sort") {
            bubbleSort(a, n);
        }
        else if (algorithm == "shaker-sort") {
            shakerSort(a, n);
        }
        else if (algorithm == "shell-sort") {
            shellSort(a, n);
        }
        else if (algorithm == "heap-sort") {
            heapSort(a, n);
        }
        else if (algorithm == "merge-sort") {
            mergeSort(a, 0, n - 1);
        }
        else if (algorithm == "quick-sort") {
            quickSort(a, 0, n - 1);
        }
        else if (algorithm == "counting-sort") {
            countingSort(a, n);
        }
        else if (algorithm == "radix-sort") {
            radixSort(a, n);
        }
        else if (algorithm == "flash-sort") {
            flashSort(a, n);
        }
        else {
            cout << "Khong hop le" << endl;
            delete[] a;
            return 1;
        }

        outFile << n << endl;
        for (int i = 0; i < n; i++) {
            outFile << a[i] << " ";
        }
        outFile << endl;

        delete[] a;
    }

    inFile.close();
    outFile.close();

    cout << "Da sap xep va luu vao " << outputFile << endl;
    return 0;
}
