#include <stdio.h>
#include <iostream>
#include <assert.h>

using namespace std; 

struct Node  
{  
    int key;  
    Node *left;  
    Node *right;  
    int height;
    Node(int k)
    {
        key = k;
        height = 1;
        left = right = NULL;
    }
}; 

int height(Node *r)  
{  
    if (r == NULL)  
        return 0;  
    return r->height;  
}  

int getBalanceFactor(Node *ref_root)  
{  
    if (ref_root == NULL)  
        return 0;  
    return height(ref_root->left) -  
           height(ref_root->right);  
}  

int max(int a, int b)  
{  
    if(a > b)
        return a;
    else return b;
}  

Node * getSmallestNode(Node* ref_root)  
{  
    Node* current = ref_root;  
    while (current->left != NULL)  
        current = current->left;  
  
    return current;  
}  

/*
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
*/


Node *right_rotate(Node *ref_root)  
{  
    Node *a = ref_root->left;  
    Node *b = a->right;  
  
    a->right = ref_root;  
    ref_root->left = b;  
  
    ref_root->height = max(height(ref_root->left), height(ref_root->right)) + 1;  
    a->height = max(height(a->left), height(a->right)) + 1;  
    return a;  
}  
  
 
Node *left_rotate(Node *ref_root)  
{  
    Node *a = ref_root->right;  
    Node *b = a->left;  

    a->left = ref_root;  
    ref_root->right = b; 

    ref_root->height = max(height(ref_root->left), height(ref_root->right)) + 1;  
    a->height = max(height(a->left), height(a->right)) + 1;  
   
    return a;  
}  




/*
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
*/
  
Node* insert_key(int key, Node* ref_root)  
{  
    if (ref_root == NULL)  
        return new Node(key);
  
    if (key < ref_root->key)  
        ref_root->left = insert_key(key, ref_root->left);  
    else if (key > ref_root->key)  
        ref_root->right = insert_key(key, ref_root->right);  
    else 
        return ref_root;  
        
    ref_root->height = 1 + max(height(ref_root->left), height(ref_root->right));  
  

    int balance = getBalanceFactor(ref_root);  
  

    if (balance < -1 && key > ref_root->right->key)  
        return left_rotate(ref_root);  

    if (balance > 1 && key < ref_root->left->key)  
        return right_rotate(ref_root);  

    if (balance < -1 && key < ref_root->right->key)  
    {  
        ref_root->right = right_rotate(ref_root->right);  
        return left_rotate(ref_root);  
    }  
 
    if (balance > 1 && key > ref_root->left->key)  
    {  
        ref_root->left = left_rotate(ref_root->left);  
        return right_rotate(ref_root);  
    }  

    return ref_root;  
}  



  
Node* delete_key(int key, Node* ref_root)  
{  
    if (ref_root == NULL)  
        return ref_root;  
  
    if ( key < ref_root->key )  
        ref_root->left = delete_key(key, ref_root->left);  
  
    else if( key > ref_root->key )  
        ref_root->right = delete_key(key, ref_root->right);  
  
    else
    {  
        if( (ref_root->left == NULL) || 
            (ref_root->right == NULL) )  
        {  
            Node *newNode;
            if(ref_root->left != NULL){
                newNode = ref_root->left;
            }else{
                newNode = ref_root->right;
            }  
  
            if (newNode == NULL)  
            {  
                newNode = ref_root;  
                ref_root = NULL;  
            }  
            else  
            *ref_root = *newNode; 
            free(newNode);  
        }  
        else
        {  
            Node* newNode = getSmallestNode(ref_root->right);  
            ref_root->key = newNode->key;  
            ref_root->right = delete_key(newNode->key ,ref_root->right);  
        }  
    }  

    if (ref_root == NULL)  
    return ref_root;  
  
    ref_root->height = 1 + max(height(ref_root->left),  
                           height(ref_root->right));  
  
    int balance = getBalanceFactor(ref_root);  
 
    if (balance > 1 &&  
        getBalanceFactor(ref_root->left) >= 0)  
        return right_rotate(ref_root);   
    if (balance > 1 &&  
        getBalanceFactor(ref_root->left) < 0)  
    {  
        ref_root->left = left_rotate(ref_root->left);  
        return right_rotate(ref_root);  
    }  
    if (balance < -1 &&  
        getBalanceFactor(ref_root->right) <= 0)  
        return left_rotate(ref_root);   
    if (balance < -1 &&  
        getBalanceFactor(ref_root->right) > 0)  
    {  
        ref_root->right = right_rotate(ref_root->right);  
        return left_rotate(ref_root);  
    }  
  
    return ref_root;  
}  

/*void inOrder(node* root) 
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


*/


int KthMin(Node *root, int k) 
{ 
    //cout << "KthMin\n";
    int count = 0; 
    int result = INT_MIN;
    Node *current = root;
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
            Node *successor = current->left; 

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
  

/*
int KthMin(node *root, int k){
    int arr[170000];
    int count = 0;
    inOrderArray(root, arr, count);
    //cout << "returning " << arr[count] << '\n';
    return arr[k];
}

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
*/
  

int main()
{
    Node *root = 0;
    char op[10] = "";
    int k;
    while(true)
    {
        scanf("%s", op);
        if(op[0] == 'E') break;
        switch(op[0])
        {
            case 'A': scanf("%d", &k); root = insert_key(k, root); break;
            case 'D': scanf("%d", &k); root = delete_key(k, root); break;
            case 'M': scanf("%d", &k); printf("%d\n", KthMin(root, k));break;
            //case 'T': scanf("%d", &k); root = right_rotate(root); break;
            default: assert(0);
        }
    }

    return 0;
}