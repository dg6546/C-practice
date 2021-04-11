#include <iostream>
#include <string>
#include <math.h>
#include <vector>
#include <limits>
using namespace std;

// Definition for a binary tree node.
struct TreeNode {
    int val;
    int max; // maximum value of the subtree from this node
    int min; // minimum value of the subtree from this node
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), max(NULL), min(NULL), left(NULL), right(NULL) {}
    TreeNode() : val(NULL), max(NULL), min(NULL), left(NULL), right(NULL)  {}
};



TreeNode* insertTreeByLevel(TreeNode* node, vector<int> v, int i, int n){
    if (i<n){
        if(v[i] == 0){
            TreeNode* newNode = new TreeNode();
            node = newNode;
        }else{

            TreeNode* newNode = new TreeNode(v[i]);
            int value = newNode->val;
            node = newNode;
        }
        node->left = insertTreeByLevel(node->left, v, i*2 + 1, n);
        node->right = insertTreeByLevel(node->right, v, i*2 + 2, n);
    }
    return node;
}


/*void inOrder(TreeNode* root) 
{ 
    if (root != NULL) 
    { 
        inOrder(root->left); 
        cout << root->val <<" "; 
        inOrder(root->right); 
    } 
} */

int peak(TreeNode* node){
    if(node == NULL) return -1;
    if(node->val == NULL) return -1;
    return node->val;
}

bool checkBST(TreeNode* node, int min, int max){
    if (node == NULL) return true;
    if (node->val == NULL) return true;
    //cout << "Node:" << node->val << "MAX: " << max << " MIN:" << min << '\n';
    if (node->val < min || node->val > max){
        return 0;
    }
    return checkBST(node->left, min, node->val) && checkBST(node->right, node->val, max);
}

/*
bool checkBST(TreeNode* node){
    bool thisCorrect = true;
    if (node == NULL) return true;
    if (node->val == NULL) return true;
    int leftValue = peak(node->left);
    int rightValue = peak(node->right);
    if(leftValue != -1){
        if(node->val < leftValue){
            return false;
        }
    }
    if(rightValue != -1){
        if(node->val > rightValue){
            return false;
        }
    }
    return (checkBST(node->left) && checkBST(node->right));
}
*/



void SolveD() {
    vector<int> v;
    int temp;
    int NumOfNode;

    //first input
    cin >> NumOfNode;
    //second input
    for(int i = 0; i < NumOfNode; i++){
        cin >> temp;
        v.push_back(temp);
    }
    TreeNode* root = insertTreeByLevel(root, v, 0, NumOfNode);
    int result = checkBST(root, std::numeric_limits<int>::min(), std::numeric_limits<int>::max());
    result == 1 ? cout << "true" : cout << "false";
}



int main() {
    SolveD();
    return 0;
}