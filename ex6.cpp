#include <iostream>
using namespace std;

const int N = 8;
int board[N][N] = {0};
int sol = 0; 

bool isSafe(int row, int col) {// Hàm kiểm tra xem có thể đặt hậu tại vị trí (row, col) không
   
    for (int i = 0; i < row; i++) {
        if (board[i][col] == 1){ // Kiểm tra cột dọc
            return false;
        }
    }

    for (int i = row, j = col; i >= 0 && j >= 0; i--, j--) {
        if (board[i][j] == 1){// Kiểm tra đường chéo trái trên
            return false;
        }
    
    }

    for (int i = row, j = col; i >= 0 && j < N; i--, j++) {
        if (board[i][j] == 1) return false; // Kiểm tra đường chéo phải trên
    }

    return true;
}


void count(int row) {// Hàm giải bài toán N-Queen 
    if (row == N) {
        sol++; // Đếm thêm 1 lời giải
        return;
    }

   
    for (int col = 0; col < N; col++) {// Thử đặt hậu ở từng cột của hàng hiện tại
        if (isSafe(row, col)) { 
            board[row][col] = 1;
            count(row + 1);// Gọi đệ quy để tiếp tục với hàng tiếp theo
            board[row][col] = 0;// Quay lui để thử vị trí khác
        }
    }
}

int main() {
    count(0);
    cout << sol << endl;
    return 0;
}
