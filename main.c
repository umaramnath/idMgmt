// C program to delete a node from AVL Tree 
#include<stdio.h> 
#include<stdlib.h> 
#include "avl.h"
#include "trie.h"
#include "minHeap.h"

/****DUMMY FILE. NOT TO BE USED****/

int main()
{

printf("TEST STASRT");

#if 0

int id  =  create_id("abcassa");
printf("The id returned for abcassa %d\n", id);
dumpIdDB();
dumpDataDB();


id  =  create_id("kjllik");
printf("The id returned for kjllik %d\n", id);
dumpIdDB();
dumpDataDB();



char * s = query_id(1);
printf("The string 1 is %s\n", s);

s = query_id(2);
printf("The string 2 is %s\n", s);




/*Delete*/
delete_id(1);
dumpIdDB();
dumpDataDB();
s = query_id(1);
printf("The string 1 is %s\n", s);
#endif
return 0;
}
