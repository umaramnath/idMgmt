#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include "trie.h"

struct trie *trieCreate() 
{ 
    struct trie *node = (struct trie *)malloc(sizeof(struct trie)); 
    int i = 0;
    if (node) 
    { 
        for (i = 0; i < ASCII_MAX; i++) 
            node->child[i] = NULL; 
            node->eow = 0; /*Need this to differentiate sub*/    
            node->id =0;/*0 is invalid id*/
    } 
    return node; 
} 
  
struct trie * trieInsert(struct trie *root, char *string, int32_t id) 
{ 
    struct trie *node = root; 
    int i = 0;
    for (i = 0; i < strlen(string); i++) 
    { 
        if (!node->child[string[i]]) 
            node->child[string[i]] = trieCreate(); 
        node = node->child[string[i]]; 
    } 
    node->eow = 1; 
    node->id = id;
    return root;
} 
  
int trieSearch(struct trie *root, char *string) 
{ 
    struct trie *node = root; 
    int i = 0;
    for (i = 0; i < strlen(string); i++) 
    { 
        if (!node->child[string[i]]) 
            return 0; 
        node = node->child[string[i]]; 
    } 
    if(!node) return 0;
    else if (!node->eow) return 0;
    else return 1; //found!!!!
}

int32_t trieGetId(struct trie *root, char *string)
{
    struct trie *node = root;
    int i = 0;
    for (i = 0; i < strlen(string); i++)
    {
        if (!node->child[string[i]])
            return 0;
        node = node->child[string[i]];
    }
    if(!node) return 0;
    else if (!node->eow) return 0;
    else return node->id; //found!!!!
}


struct trie * trieDeleteOnePass(struct trie * root, char* string) {
   
    struct trie **buffer = (struct trie**)malloc(sizeof(struct trie*) * strlen(string));
    //fill this buffer all along the path  
    struct trie *node = root;
    int i = 0;
    int k = 0;
    for (i = 0; i < strlen(string); i++)
    {
        if (!node->child[string[i]])
            return 0;
        buffer[i] = (struct trie*) node->child[string[i]];
        node = node->child[string[i]];
    }
    if(!node && (!node->eow)) {
        printf("\nCannot delete, something that is not present");
        return root;
    }
    //Node is present
    if(node->eow) node->eow=0;
    //We know its there for sure.
    for (i = strlen(string)-1;i>=0; i--)
    {
        int cannotDelete = 0;
        printf("\n %c", string[i]);
        //Does buffer[i] have even one child? Dont delete
        for(k =0 ; k < ASCII_MAX; k++) {
             if(buffer[i]->child[k]) {
                 cannotDelete = 1;
                 break;
             }
        }
        if(!cannotDelete && i!=0) {
                buffer[i-1]->child[string[i]] = NULL;
        }
        if(!cannotDelete && i==0) {
                root->child[string[i]] = NULL;
        }
    }
   free(buffer);
   return root;
}

static struct trie * trieDeleteHelper(struct trie* root, int h, char* string) 
{ 
    if (!root) 
        return NULL; 
    int i;
    int cannotDelete = 0;
    if (h == strlen(string)) { 
        if (root->eow == 1) root->eow = 0; 
        cannotDelete = 0;
        for (i = 0; i < ASCII_MAX; i++){
            if (root->child[i])
            {  
                cannotDelete = 1;
                break;
            }
        }
        if (!cannotDelete) { 
            free(root);
            root = NULL; 
        } 
        return root; 
    } 
  
    root->child[string[h]] =  
          trieDeleteHelper(root->child[string[h]], h+1, string); 
  
    if(root->eow == 0) {
        cannotDelete = 0;
        for (i = 0; i < ASCII_MAX; i++){
            if (root->child[i])
            {
                cannotDelete = 1;
                break;
            }
        }
        if(!cannotDelete) {
            free(root); 
            root = NULL; 
        }
    } 
  
    return root; 
}

struct trie * trieDelete(struct trie* node, char* string)
{
    trieDeleteHelper(node, 0, string);
}  

void trieDumpHelper(struct trie* root, int k, char * string) 
{

    if(!root) return; 
    if (root->eow)  
    { 
        string[k] = '\0'; 
        printf("\n{%s, %d}\n",string, root->id);
    } 
  
    int i; 
    for (i = 0; i < ASCII_MAX; i++)  
    { 
        if (root->child[i])  
        { 
            string[k] = i; 
            trieDumpHelper(root->child[i], k + 1, string); 
        } 
    } 
}


