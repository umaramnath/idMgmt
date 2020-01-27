#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 

#define ASCII_MAX 256
  
struct trie 
{ 
    struct trie *child[ASCII_MAX]; 
    int eow;
    int32_t id; 
}; 
  
struct trie * trieCreate(); 
int32_t trieGetId(struct trie *root, char *string);
struct trie* trieInsert(struct trie *root, char *string, int32_t id);
int trieSearch(struct trie *root, char *string);
struct trie * trieDelete(struct trie* node, char* string);
struct trie * trieDeleteOnePass(struct trie* node, char* string);
void trieDumpHelper(struct trie* root, int k, char * string);
