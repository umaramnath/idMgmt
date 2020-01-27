// C program to delete a node from AVL Tree 
#include<stdio.h> 
#include<stdlib.h> 
#include "avl.h"
  
// A utility function to get height of the tree 
int height(struct Node *N) 
{ 
    if (N == NULL) 
        return 0; 
    return N->height; 
} 
  
// A utility function to get maximum of two integers 
int32_t max(int32_t a, int32_t b) 
{ 
    return (a > b)? a : b; 
} 
  
/* Helper function that allocates a new node with the given key and 
    NULL left and right pointers. */
struct Node* newNode(int32_t key, char *string, int ref) 
{ 
    struct Node* node = (struct Node*) 
                        malloc(sizeof(struct Node)); 
    node->key   = key; 
    node->left   = NULL; 
    node->right  = NULL; 
    node->height = 1;  // new node is initially added at leaf 
    node->string = string;
    node->ref = ref;
    return(node); 
} 
  
struct Node *rightRotate(struct Node *y) 
{ 
    struct Node *x = y->left; 
    struct Node *T2 = x->right; 
    x->right = y; 
    y->left = T2; 
    y->height = max(height(y->left), height(y->right))+1; 
    x->height = max(height(x->left), height(x->right))+1; 
    return x; 
} 
  
struct Node *leftRotate(struct Node *x) 
{ 
    struct Node *y = x->right; 
    struct Node *T2 = y->left; 
    y->left = x; 
    x->right = T2; 
    x->height = max(height(x->left), height(x->right))+1; 
    y->height = max(height(y->left), height(y->right))+1; 
    return y; 
} 
  
int getBalance(struct Node *N) 
{ 
    if (N == NULL) 
        return 0; 
    return height(N->left) - height(N->right); 
} 
  
struct Node* insert(struct Node* node, struct Node* keyNode) 
{
    if (node == NULL)
        return keyNode; 
  
    if (keyNode->key < node->key) 
        node->left  = insert(node->left, keyNode); 
    else if (keyNode->key > node->key) 
        node->right = insert(node->right, keyNode); 
    else // Equal keys not allowed 
        return node; 
  
    node->height = 1 + max(height(node->left), 
                           height(node->right)); 
  
    int balance = getBalance(node); 
    if (balance > 1 && keyNode->key < node->left->key) 
        return rightRotate(node); 
  
    if (balance < -1 && keyNode->key > node->right->key) 
        return leftRotate(node); 
  
    if (balance > 1 && keyNode->key > node->left->key) 
    { 
        node->left =  leftRotate(node->left); 
        return rightRotate(node); 
    } 
  
    if (balance < -1 && keyNode->key < node->right->key) 
    { 
        node->right = rightRotate(node->right); 
        return leftRotate(node); 
    } 
  
    return node; 
} 
  
struct Node * minValueNode(struct Node* node) 
{ 
    struct Node* current = node; 
  
    while (current->left != NULL) 
        current = current->left; 
  
    return current; 
} 
  
struct Node* deleteNode(struct Node* root, int32_t key) 
{ 
    if (root == NULL) 
        return root; 
    if ( key < root->key ) 
        root->left = deleteNode(root->left, key); 
    else if( key > root->key ) 
        root->right = deleteNode(root->right, key); 
    else
    { 
        if( (root->left == NULL) || (root->right == NULL) ) 
        { 
            struct Node *temp = root->left ? root->left : 
                                             root->right; 
  
            // No child case 
            if (temp == NULL) 
            { 
                temp = root; 
                root = NULL; 
            } 
            else // One child case 
             *root = *temp; // Copy the contents of 
                            // the non-empty child 
            free(temp); 
        } 
        else
        { 
            // node with two children: Get the inorder 
            // successor (smallest in the right subtree) 
            struct Node* temp = minValueNode(root->right); 
  
            // Copy the inorder successor's data to this node 
            root->key = temp->key; 
  
            // Delete the inorder successor 
            root->right = deleteNode(root->right, temp->key); 
        } 
    } 
  
    // If the tree had only one node then return 
    if (root == NULL) 
      return root; 
  
    // STEP 2: UPDATE HEIGHT OF THE CURRENT NODE 
    root->height = 1 + max(height(root->left), 
                           height(root->right)); 
  
    // STEP 3: GET THE BALANCE FACTOR OF THIS NODE (to 
    // check whether this node became unbalanced) 
    int balance = getBalance(root); 
  
    // If this node becomes unbalanced, then there are 4 cases 
  
    // Left Left Case 
    if (balance > 1 && getBalance(root->left) >= 0) 
        return rightRotate(root); 
  
    // Left Right Case 
    if (balance > 1 && getBalance(root->left) < 0) 
    { 
        root->left =  leftRotate(root->left); 
        return rightRotate(root); 
    } 
  
    // Right Right Case 
    if (balance < -1 && getBalance(root->right) <= 0) 
        return leftRotate(root); 
  
    // Right Left Case 
    if (balance < -1 && getBalance(root->right) > 0) 
    { 
        root->right = rightRotate(root->right); 
        return leftRotate(root); 
    } 
  
    return root; 
} 
  
void preOrder(struct Node *root) 
{ 
    if(root != NULL) 
    { 
        printf("%d ", root->key); 
        preOrder(root->left); 
        preOrder(root->right); 
    } 
} 
  
void inOrder(struct Node *root)
{
    if(root != NULL)
    {
        inOrder(root->left);
        printf("\n{id: %d, data: %s ref:%d}", root->key, root->string, root->ref);
        inOrder(root->right);
    }
}


struct Node* search(struct Node* node, int32_t key)
{
    if ((!node) || (node->key == key)) 
       return node; 
     
    if (node->key < key) 
       return search(node->right, key); 
  
    return search(node->left, key); 
} 

