#include <iostream>
using namespace std;

struct Node{
    int data;
    Node* left;
    Node* right;
    int height;
};

typedef struct Node* node;

node createNode(int x){
    node p = new Node();
    p -> data = x;
    p -> left = nullptr;
    p -> right = nullptr;
    p -> height =0;
    return p;
}

//hàm tính max
int max(int a, int b) {
    if (a > b) {
        return a;
    } else {
        return b;
    }
}

//hàm cập nhật chiều cao của cây
void updateHeight(node z){
    int lheight, rheight;
    if(z == nullptr) return;
    if(z -> left != nullptr){
        lheight = z -> left ->height;
    }
    else lheight = -1;
    if(z -> right != nullptr){
        rheight = z -> right -> height;
    }
    else rheight = -1;
    z -> height = 1 + max(lheight, rheight);
}

// các hàm thực hiện phép xoay-----------------------------------------------------------------------
//xoay phải phảiphải
node rotateRight(node z){
    node y = z -> left;
    node leaf = y -> right;
    y -> right = z;
    z -> left = leaf;
    updateHeight(z);
    updateHeight(y);
    return y;
}

//xoay trái trái
node rotateLeft(node z){
    node y = z -> right;
    node leaf = y -> left;
    y -> left = z;
    z -> right = leaf;
    updateHeight(z);
    updateHeight(y);
    return y;
}

// xoay trái phải
node leftrightcase(node z){
    z -> left = rotateLeft(z -> left);
    return rotateRight(z);
}

//xoay phải trái
node rightleftcase(node z){
    z -> right = rotateRight(z -> right);
    return rotateLeft(z);
}
//----------------------------------------------------------------------------------------------------

//hàm tính chiều cao của cây
int getHeight(node z){
    if(z == nullptr){
        return -1;
    }
    return z -> height;
}

//tính độ chênh lệch giữa các nhánh xem thử có cân bằng hay khôngkhông
int Balance(node z){
    if(z == nullptr){
        return -1;
    }
    int lh = getHeight(z -> left);
    int rh = getHeight(z -> right);
    int bl = lh - rh;
    return bl;
}

//Hàm kiểm tra và sửa để cây cân bằng
node checkandfix(node z, int k){
    if(z == nullptr) return nullptr;
    updateHeight(z);
    int tmp = Balance(z);
    if(tmp > 1 && z->left != nullptr && k < z -> left -> data){
        return rotateRight(z);
    }
    else if(tmp > 1 && z->left != nullptr && k > z -> left -> data){
        return leftrightcase(z);
    }
    else if(tmp < -1 && z->right != nullptr && k > z -> right -> data){
        return rotateLeft(z);
    }
    else if(tmp < -1  && z->right != nullptr && k < z -> right -> data){
        return rightleftcase(z);
    }
    return z;
}

//hàm chèn một node vào cây và cân bằng (phục vụ cho hàm thêm nodenode)
void insert(node &z, int key){
    if(z == nullptr){ 
        z = createNode(key);
        return;
    }
    if(key < z->data)
        insert(z->left, key);
    else if(key > z->data)
        insert(z->right, key);
    else
        return ; // Không cho phép trùng

    z = checkandfix(z, key);
}

//hàm tìm node nhỏ nhất của cây con bên phải(dùng để phục vụ cho hàm xóa nodenode)
node findmin(node z){
    if(z == nullptr) return nullptr;
    if(z -> left == nullptr) return z;
    return findmin(z -> left);
}

//hàm xóa một node khỏi cây và cân bằngbằng
void remove(node &z, int x){
    if(z == nullptr) return;
    if(x > z -> data){
        remove(z -> right, x);
    }
    if(x < z -> data){
        remove(z -> left, x);
    }
    if(x == z -> data){
        if( z -> right ==nullptr){
            node tmp = z;
            z = z -> left;
            delete tmp;
        }
        else if(z -> left == nullptr){
            node tmp = z;
            z = z -> right;
            delete tmp; 
        }
        else if(z -> left && z -> right){
            node tmp = findmin(z -> right);
            z -> data = tmp -> data;
            remove(z-> right , tmp -> data);
        }
    }   
    if(z == nullptr) return;
    updateHeight(z);
    int n = Balance(z);
    if(n < -1 && Balance(z -> left) <= 0){
        z = rotateRight(z);
    }
    else if(n > 1 && Balance(z -> right) >= 0){
        z = rotateLeft(z);
    }
    else if(n < -1 && Balance(z -> left) > 0){
        z = rightleftcase(z);
    }
    else if( n > 1 && Balance(z -> right) < 0){
        z = leftrightcase(z);
    }
}

//hàm bổ sung: in cây 
void preorder(node root) {
    if (root != nullptr) {
        cout << root->data << " ";      
        preorder(root->left);           
        preorder(root->right);          
    }
}

//kiểm tra xem thử cây có phải là cây AVL khôngkhông
bool isAVL(node z){
    if(z == nullptr) return true;
    int tmp = Balance(z);
    if(tmp > 1 || tmp < -1 ){
        return false;
    }
    return isAVL( z -> left) && isAVL(z -> right);
}



