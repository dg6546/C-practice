#include <iostream>
#include <string>
#include <sstream>
#include <math.h>
#include <cstdio>
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

void buildTree(TreeNode* n, int value){
    if(n == NULL){
        TreeNode *newNode = new TreeNode(value);
        n = newNode;
    }
        
    if(value <= n->val){
        if(n->left == NULL){
            TreeNode *newNode = new TreeNode(value);
            n->left = newNode;
        }else{
            buildTree(n->left, value);
        }
    }else if (value > n->val){
        if(n->right == NULL){
            TreeNode *newNode = new TreeNode(value);
            n->right = newNode;
        }else{
            buildTree(n->right, value);
        }
    }
}

void inOrder(TreeNode* root) 
{ 
    if (root != NULL) 
    { 
        inOrder(root->left); 
        cout << root->val <<" "; 
        inOrder(root->right); 
    } 
} 

void SolveD() {
    string s1;
    string s2;
    stringstream ss;
    bool builtRoot = false;
    int temp;
    int NumOfNode;
    getline(cin, s1);
    NumOfNode = stoi(s1);
    getline(cin, s2);
    ss << s2;
    ss >> temp;
    for(int i = 0; i < NumOfNode; i++){
        
    }
    while (ss >> temp){
        //cout << temp;
        buildTree(root, temp);
    }
    inOrder(root);

}



int main() {
    SolveD();
    return 0;
}