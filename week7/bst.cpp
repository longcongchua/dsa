#include <iostream>
using namespace std;

struct Node{
    int data;
    Node* left;
    Node* right;
};

typedef struct Node* node;

node createNode(int x){
    node p = new Node();
    p -> data = x;  
    return p;
}

//1. Find and return a NODE with a specified value from a binary search tree
node search(node pRoot, int x){
    if(pRoot == nullptr){
        return 0;
    }
    if(pRoot -> data == x){
        return pRoot;
    }
    if(pRoot -> data > x){
        search(pRoot -> left , x);
    }
    if(pRoot -> data < x){
        search(pRoot -> right , x);
    }
    return 0;
}

//2. Add a NODE with a specified value to a binary search tree:
void insert(node &pRoot, int x){
    if(pRoot == nullptr){
        node p = new Node();
        p -> data;
        pRoot = p;
    }
    if(pRoot -> data > x){
        if(pRoot -> left ==nullptr){
            node p = new Node();
            p -> data = x;
            p -> left = nullptr;
            p -> right = nullptr;
            pRoot -> left = p;
        }
        else{
            insert(pRoot -> left, x);
        }
    }
    if(pRoot -> data < x){
        if(pRoot -> right ==nullptr){
            node p = new Node();
            p -> data = x;
            p -> left = nullptr;
            p -> right = nullptr;
            pRoot -> right = p;
        }
        else{
            insert(pRoot -> right, x);
        }
    }
}

//3. Delete a NODE with a given value from a binary search tree:
void remove(node &pRoot, int x){
    if(pRoot == nullptr){
        return;
    }
    if(pRoot -> data > x){
        remove(pRoot -> left, x);
    }      
    if(pRoot -> data < x){
        remove(pRoot -> right, x);
    } 
    if(pRoot -> data == x){
        if(pRoot -> left == nullptr){
            node p = pRoot;
            pRoot = pRoot -> right;
            delete p;
        }
        else if(pRoot -> right == nullptr){
            node p = pRoot;
            pRoot = pRoot -> left;
            delete p;
        }
        else if(pRoot -> left && pRoot -> right){
            node newp = findmax(pRoot -> left);
            pRoot -> data = newp -> data;
            remove(pRoot -> left , newp -> data);
        }
    }
}

node findmax(node pRoot){
    if(pRoot -> left == nullptr){
        return pRoot;
    } 
    return findmax(pRoot -> left); 
}

//4. Initialize a binary search tree from a given array:
node createTree(int *a, int n){
    node tree = new Node();
    tree -> data = a[0];
    for(int i = 1; i< n ; i++){
        insert(tree , a[i]);
    }
    return tree;
}

//5. Delete a binary search tree entirely:dd
void removeTree(node &pRoot){
    if(pRoot == nullptr) return;
    removeTree(pRoot -> left);
    removeTree(pRoot -> right);
    delete pRoot;
    pRoot = nullptr;
}

//6. Calculate the height of a binary search tree:
int Height(node pRoot){
    if(pRoot == nullptr) return 0;
    return 1 + max(Height(pRoot -> left), Height(pRoot -> right) );
}

int max(int a, int b) {
    if (a > b) {
        return a;
    } else {
        return b;
    }
}

int countNode(node pRoot){
    if(pRoot == nullptr){
        return 0;
    }
    return 1 + countNode(pRoot -> left) + countNode(pRoot -> right );
}

//7. * Count the number of NODEs in a binary search tree with key values smaller than a given value:
int countLess(node pRoot, int x){
    if(pRoot == nullptr) return 0;
    if(pRoot -> data >= x){
        return countLess(pRoot -> left, x);
    }else {
        return 1 + countNode(pRoot -> left) + countLess(pRoot -> right , x);
    }
}   

//8. * Count the number of NODEs in a given binary search tree whose key values are greater than a specified value:
int countGreater(node pRoot, int x){
    if(pRoot == nullptr) return 0;
    if(pRoot -> data <= x){
        return countLess(pRoot -> right , x);
    }else {
        return 1 + countNode(pRoot -> right ) + countLess(pRoot -> left , x);
    }
}  

//9. * Determine if a binary tree is a binary search tree:
bool isBSTUtil(node pRoot, node &prev) {
    if (pRoot == nullptr) return true;
    if (!isBSTUtil(pRoot->left, prev))
        return false;
    if (prev != nullptr && pRoot->data <= prev->data)
        return false;
    prev = pRoot;  
    return isBSTUtil(pRoot->right, prev);
}

bool isBST(node pRoot) {
    node prev = nullptr;
    return isBSTUtil(pRoot, prev);
}

//10. * Check if a binary tree is a full binary search tree (BST):
bool isFullBST(node pRoot){
    if(pRoot ==nullptr) return true;
    if ((pRoot->left == nullptr && pRoot->right != nullptr) || (pRoot->left != nullptr && pRoot->right == nullptr)) {
        return false;
    }
    return  isFullBST(pRoot -> left) && isFullBST(pRoot -> right);
}

