#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct Node
{
    int data;
    Node *left;
    Node *right;
};

typedef struct Node *node;

node createNode(int x)
{
    node p = new Node();
    p->data = x;
    p -> left = nullptr;
    p -> right = nullptr;
    return p;
}

vector<int> NLR(node pRoot)
{
    vector<int> res;
    if (pRoot == NULL)
        return res;
    if (pRoot != nullptr)
    {
        res.push_back(pRoot->data);
        vector<int> left = NLR(pRoot->left);
        vector<int> right = NLR(pRoot->right);
        res.insert(res.end(), left.begin(), left.end());
        res.insert(res.end(), right.begin(), right.end());
    }
    return res;
}

vector<int> LNR(node pRoot)
{
    vector<int> res;
    if (pRoot == NULL) return res;
    vector<int> left = LNR(pRoot -> left);
    res.insert(res.end(), left.begin(),left.end());
    res.push_back(pRoot ->data);
    vector<int> right = LNR(pRoot -> right);
    res.insert(res.end(), right.begin(), right.end());
    return res;
}

vector<int> LRN(node pRoot){
    vector<int> res;
    if(pRoot == nullptr) return res;
    vector<int> left = LRN(pRoot -> left);
    res.insert(res.end(), left.begin(),left.end());
    vector<int> right = LRN(pRoot -> right);
    res.insert(res.end(), right.begin(), right.end());
    res.push_back(pRoot ->data);
    return res;
}

vector<vector<int>> LevelOrder(node pRoot){
    queue<node> q;
    vector<vector<int>> res;
    if(pRoot ==nullptr) return res;
    q.push(pRoot);
    while(!q.empty()){
        int size = q.size();
        vector<int> curlevel;
        for(int i =0; i< size; i++){
            node p = q.front();
            q.pop();
            curlevel.push_back( p-> data);
            if(p -> left != nullptr){
                q.push(p -> left);
            }
            if(p -> right != nullptr){
                q.push(p -> right);
            }
        }
        res.push_back(curlevel);
    }
    return res;
}

int countNode(node pRoot){
    if(pRoot == nullptr){
        return 0;
    }
    return 1 + countNode(pRoot -> left) + countNode(pRoot -> right);
}

int sumNode(node pRoot){
    if(pRoot == nullptr){
        return 0;
    }
    int sum = pRoot -> data;
    return sum + sumNode(pRoot -> left) + sumNode(pRoot -> right);
}

int height(node pRoot){
    if(pRoot == nullptr) return -1;
    int left = height(pRoot -> left);
    int right = height(pRoot -> right);
    return 1 + max(left, right);
}

int heightNode(node pRoot, int val)
{
    if(pRoot == NULL) return -1;
    if(pRoot -> data == val) return height(pRoot);
    int left = heightNode(pRoot -> left, val);
    if(left != -1) return 1 + left;
    int right = heightNode(pRoot -> right , val);
    if(right != -1) return 1 + right;
    return -1;
}

int findlevel(node pRoot, node p, int n){
    if(pRoot == nullptr) return -1;
    if(pRoot == p) return n;
    int lres = findlevel(pRoot -> left, p, n+1);
    if(lres != -1) return lres;
    int rres = findlevel(pRoot -> right , p , n+1);
    if(rres != -1) return rres;
    return -1;
}

int level(node pRoot, node p){
    return findlevel(pRoot , p , 0);
}

int countLeaf(node pRoot){
    if(!pRoot) return 0;
    if(pRoot -> left == nullptr && pRoot -> right == nullptr) return 1;
    return countLeaf(pRoot -> left) + countLeaf(pRoot -> right);
}


