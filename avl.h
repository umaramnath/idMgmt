// C program to delete a node from AVL Tree 
#include<stdio.h> 
#include<stdlib.h> 
  
// An AVL tree node 
struct Node 
{ 
    int32_t key; 
    struct Node *left; 
    struct Node *right; 
    int height; 
    char *string;
    int ref;
}; 
  
int max(int32_t a, int32_t b); 
int height(struct Node *N); 
struct Node* newNode(int32_t key, char *string, int ref);
struct Node* insert(struct Node* node, struct Node* keyNode);
struct Node* deleteNode(struct Node* root, int32_t key);
void preOrder(struct Node *root);
void inOrder(struct Node *root);
struct Node* search(struct Node* node, int32_t key);
