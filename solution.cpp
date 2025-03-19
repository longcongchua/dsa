#include <iostream>
using namespace std;

// Recursive function to solve Tower of Hanoi
void towerOfHanoi(int n, char rod1, char rod3, char rod2)
{
    if (n == 1)
    {
        cout << "Move disk 1 from " << rod1 << " to " << rod3 << endl;
        return;
    }
    towerOfHanoi(n - 1, rod1, rod2, rod3);
    cout << "Move disk " << n << " from " << rod1 << " to " << rod3 << endl;
    towerOfHanoi(n - 1, rod2, rod3, rod1);
}

int main()
{
    int n = 10; // Number of disks
    towerOfHanoi(n, 'A', 'C', 'B');
    return 0;
}