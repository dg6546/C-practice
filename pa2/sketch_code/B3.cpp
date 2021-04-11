#include <stdio.h>
#include <assert.h>
#include <algorithm>
#include <iostream>
#include <limits>
#include <vector> 

using namespace std;

struct node
{
    int key;
    int height;
    int factor;
    node *left, *right;
    node(int k)
    {
        key = k;
        height = 0;
        factor = 0;
        left = right = NULL;
    }
};


int max(int a, int b){
    return (a > b) ? a : b;
}

int getHeight(node* r)
{
 
    if (r == NULL)  
        return 0;  
    return r->height;  

}

int getFactor(node* r)
{
    if (r == NULL)  
        return 0;  
    return r->factor;  
}

void update(node*& root)
{
    //cout << "start update";
    if(root == NULL) return;
    else{
        int leftHeight = getHeight(root->left);
        int rightHeight = getHeight(root->right);

        root->height = 1 + max(leftHeight, rightHeight);
        root->factor = leftHeight - rightHeight;
    }
    //cout << "finish update";
}

//void update_size(node*)



/*void inOrder(node* root) 
{ 
    if (root != NULL) 
    { 
        inOrder(root->left); 
        cout << root->key <<" "; 
        inOrder(root->right); 
    } 
} */

void preOrder(node *root)  
{  
    if(root != NULL)  
    {  
        cout << root->key << " ";  
        preOrder(root->left);  
        preOrder(root->right);  
    }  
}  
  

node* right_right_rotate(node* ref_root)
{
   // cout << "right right rotation\n";
   node *t;
   t = ref_root->right;
   ref_root->right = t->left;
   t->left = ref_root;
   return t;
}

node* left_left_rotate(node* ref_root)
{
   // cout << "left left rotation\n";
   node *t;
   t = ref_root->left;
   ref_root->left = t->right;
   t->right = ref_root;
   return t;
}

node* left_right_rotate(node* ref_root){
   // cout << "left right rotation\n";
   node *t;
   t = ref_root->left;
   ref_root->left = right_right_rotate(t);
   return left_left_rotate(ref_root);
}

node* right_left_rotate(node* ref_root){
   // cout << "right left rotation\n";
   node *t;
   t = ref_root->right;
   ref_root->right = left_left_rotate(t);
   return right_right_rotate(ref_root);
}


node* maintain(node*& ref_root){
    //cout << "maintain start\n";
    if(ref_root == NULL) return NULL;
    
    int diff = getFactor(ref_root);
    if (diff == -2){
        if(getFactor(ref_root->left) <= 0){
            return right_right_rotate(ref_root);
        }else{
            return left_right_rotate(ref_root);
        }
    }
    else if (diff == 2){
        if(getFactor(ref_root->right) >= 0){
            return left_left_rotate(ref_root);
        }else{
            return right_left_rotate(ref_root);
        }
    } 
    return ref_root;
}



node* insert_key(int key, node*& ref_root)  
{  
    //cout << "insert :" <<key << '\n';
    if (ref_root == NULL)  {
        return new node(key);
    }
    else if (key < ref_root->key) {
        ref_root->left = insert_key(key, ref_root->left);
    }
    else if (key > ref_root->key) {
        ref_root->right = insert_key(key, ref_root->right); 
    }
    return ref_root;  
}  


int findMin(node* n){
    while(n->left != NULL){
        n = n->left;
    }
    return n->key;
}

int findMax(node* n){
    while(n->right != NULL){
        n = n->right;
    }
    return n->key;
}

node* delete_key(int key, node* ref_root)
{
    if(ref_root == NULL) return NULL;

    if(key < ref_root->key)
        delete_key(key, ref_root->left);
    else if(key > ref_root->key)
        delete_key(key, ref_root->right);
    else{
        if(ref_root->left == NULL)
            return ref_root->right;
        else if(ref_root->right == NULL)
            return ref_root->left;
        else{
            if(getHeight(ref_root->left) > getHeight(ref_root->right)){
                int sueecessorV = findMax(ref_root->left);
                ref_root->key = sueecessorV;
                ref_root->left = delete_key(sueecessorV, ref_root->left);
            }else{
                int sueecessorV = findMin(ref_root->right);   
                ref_root->key = sueecessorV;
                ref_root->right = delete_key(sueecessorV, ref_root->right);             
            }
        }
    }
    return ref_root;
}



/*
int KthMin(node* root, int *i, int k)
{
	// base case
	if (root == nullptr)
		return INT_MAX;

	// search in left subtree
	int left = KthMin(root->left, i, k);

	// if k'th smallest is found in left subtree, return it
	if (left != INT_MAX)
		return left;

	// if current element is k'th smallest, return its value
	if (++*i == k)
		return root->key;

	// else search in right subtree
	return KthMin(root->right, i, k);
}

// Function to find k'th smallest element in BST
int KthMin(node* root, int k)
{
	// maintain index to count number of nodes processed so far
	int i = 0;

	// traverse the tree in in-order fashion and return k'th element
	return KthMin(root, &i, k);
}*/



int KthMin(node *root, int k) 
{ 
    //cout << "KthMin\n";
    int count = 0; 
    int result = std::numeric_limits<int>::min(); 
    node *current = root;
    while (current != NULL) 
    { 
        if (current->left == NULL) 
        { 
            count++; 
            if (count==k) 
                result = current->key; 
            current = current->right; 
        } 
        else
        { 
            node *successor = current->left; 

            while (successor->right != NULL && successor->right != current) 
                successor = successor->right; 

            if (successor->right==NULL) 
            { 
                successor->right = current; 
                current = current->left; 
            } 
            else
            { 
                successor->right = NULL; 
                count++; 
  
                if (count==k) 
                    result = current->key; 
  

                current = current->right; 
            } 
        } 
    } 
    return result;
} 



int main()
{
    node *root = 0;
    char op[10] = "";
    int k;
    while(true)
    {
        scanf("%s", op);
        if(op[0] == 'E') break;
        switch(op[0])
        {
            case 'A': scanf("%d", &k); root = insert_key(k, root); update(root); root = maintain(root); break;
            case 'D': scanf("%d", &k); root = delete_key(k, root); update(root); root = maintain(root); break;
            case 'M': scanf("%d", &k); printf("%d\n", KthMin(root, k));break;
            //case 'T': scanf("%d", &k); root = right_rotate(root); break;
            default: assert(0);
        }
        cout << "Preorder: ";
        preOrder(root);
        cout << '\n';
    }

    return 0;
}
