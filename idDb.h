#include<stdio.h>
#include<stdlib.h>
#include "avl.h"
#include "trie.h"
#include "minHeap.h"

#define SOMETIME 2
#define INT_32_MAX 0x7FFFFFFF
#define MIN_HEAP_CAPACITY 10000

/*TBD int can be 64 bit. Restrict to 32 bit*/
int32_t globalFree =1;/*Index of element that is free*/
struct Node *idDB = NULL;
struct trie *dataDB = NULL;
char queryError[20] = "Not Exists";
struct minHeap *min = NULL;

/*MUST CALL*/
void dbInit();

/*DUMP FUNCTIONS*/
void hDump();
void dumpIdDB(void);
void dumpDataDB(void);

/*DB OPERATIONS*/
int32_t create_id(char * string);
char * query_id(int32_t id);
void delete_id(int32_t id);

