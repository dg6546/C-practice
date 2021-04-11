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
    int size;
    node *left, *right;
    Node(int k)
    {
        key = k;
        height = 1;
        size = 1;
        left = right = NULL;
    }
};


int max(int a, int b){
    return (a > b) ? a : b;
}


int height(node* r)
{
    
    if (r == NULL) return -1;
    else{
        int left_height = height(r->left);
        int right_height = height(r->right);
        int h;
        h = max(left_height, right_height) + 1;
        return h;
    }
}

int size(node* r)
{
    return r ? r->size : 0;
}

//void update_size(node*)



void inOrder(node* root) 
{ 
    if (root != NULL) 
    { 
        inOrder(root->left); 
        cout << root->key <<" "; 
        inOrder(root->right); 
    } 
} 

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
   node *t;
   t = ref_root->right;
   ref_root->right = t->left;
   t->left = ref_root;
   return t;
}

node* left_left_rotate(node* ref_root)
{
   node *t;
   t = ref_root->left;
   ref_root->left = t->right;
   t->right = ref_root;
   return t;
}

node* left_right_rotate(node* ref_root){
   node *t;
   t = ref_root->left;
   ref_root->left = right_right_rotate(t);
   return left_left_rotate(ref_root);
}

node* right_left_rotate(node* ref_root){
   node *t;
   t = ref_root->right;
   ref_root->right = left_left_rotate(t);
   return right_right_rotate(ref_root);
}

int getHeightDifference(node* root){
    //cout << "start getHeightDifference \n";
    int left_height;
    int right_height;
    if (root == NULL)  {
        return 0; 
    }
    else{
        left_height = height(root->left);
        right_height = height(root->right);
        //cout << "finish getHeightDifference \n";
        return left_height - right_height;  
          
    }
    //cout << "finish getHeightDifference \n";  
}

node* maintain(node* ref_root){
    //cout << "maintain start\n";
    int diff = getHeightDifference(ref_root);
    if (diff > 1){
        if(getHeightDifference(ref_root->left) > 0){
            ref_root = left_left_rotate(ref_root);
        }else{
            ref_root = left_right_rotate(ref_root);
        }
    } else if (diff < -1){
        if(getHeightDifference(ref_root->right) > 0){
            ref_root = right_left_rotate(ref_root);
        }else{
            ref_root = right_right_rotate(ref_root);
        }
    }
    return ref_root;
}



node* insert_key(int key, node* ref_root)  
{  
    //cout << "insert :" <<key << '\n';
    if (ref_root == NULL)  {
        node* newNode = new node(key);
        return newNode;  
    }
    else if (key < ref_root->key) {
        ref_root->left = insert_key(key, ref_root->left);
    }
    else if (key > ref_root->key) {
        ref_root->right = insert_key(key, ref_root->right); 
    }
    
    return ref_root;  
}  


node* getSmallestNode(node* n){
    if(n->left == NULL){
        return n;
    }else{
        getSmallestNode(n->left);
    }
    return n;
}

node* delete_key(int key, node* ref_root)
{
    //cout << "delete :" <<key << '\n';
    if(ref_root == NULL){
        return ref_root;
    }
    if( key < ref_root->key){
        ref_root->left = delete_key(key, ref_root->left);
    }
    else if(key > ref_root->key){
        ref_root->right = delete_key(key, ref_root->right);
    }
    else{
        if (ref_root->right == NULL || ref_root->left == NULL){
            node* temp = ref_root->left? ref_root->left : ref_root->right;
            if (temp == NULL){
                temp = ref_root;
                ref_root = NULL;
            }
            else{
                *ref_root = *temp;
            }
            
            free(temp);
        }else{
            node* temp = getSmallestNode(ref_root->right);
            ref_root->key = temp->key;
            ref_root->right = delete_key(temp->key, ref_root->right);
        }
    }
    return ref_root;
}


/*

// Function to find k'th smallest element in BST
// Here i denotes the number of nodes processed so far
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
}
*/

/*
void inOrderArray(node* root, int (&arr)[170000], int &count){
    if (root != NULL) 
    { 
        inOrderArray(root->left, arr, count); 
        arr[count] = root->key;
        //cout << arr[count] << ' ';
        count++;
        inOrderArray(root->right, arr, count); 
    } 
}



int KthMin(node *root, int k){
    int arr[170000];
    int count = 0;
    inOrderArray(root, arr, count);
    //cout << "returning " << arr[count] << '\n';
    return arr[k];
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
            case 'A': scanf("%d", &k); root = insert_key(k, root); root = maintain(root); break;
            case 'D': scanf("%d", &k); root = delete_key(k, root); root = maintain(root); break;
            case 'M': scanf("%d", &k); printf("%d\n", KthMin(root, k));break;
            //case 'T': scanf("%d", &k); root = right_rotate(root); break;
            default: assert(0);
        }
        cout << "Preorder: ";
        preOrder(root);
        cout << '\n';
        cout << "Inorder: ";
        inOrder(root);
        cout << '\n';
    }

    return 0;
}
