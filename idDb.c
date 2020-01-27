#include "idDb.h"

void dataDbInit()
{
    dataDB = trieCreate();
}

void minInit()
{
    min = (minHeap *)malloc(sizeof(minHeap));
    init(min, MIN_HEAP_CAPACITY); //TDB!!
}

/*BE SURE TO CALL THIS FROM MAIN OR PYTHON SCRIPT*/
void dbInit() {
    /*Need to initialse all DBs. esp data and min*/
    printf("INIT DONE from python test!\n");
    dataDbInit();
    minInit();
    idDB = NULL;
}

int32_t searchDataDB(char *string)
{
   return trieGetId(dataDB, string);
}

void createMapIdDB(int32_t id, char * string){
    struct Node *node = newNode(id, string,1);
    //printf("\n In function createMapIdDB %s\n", string);
    idDB = insert(idDB, node);
    //return idDB;
}

char * queryIdDB(int32_t id){
    struct Node *node = NULL;
    if(!idDB) return NULL;
    node = search(idDB,id);
    if(!node) {
        //printf("seach of id DB failed and hence returning NULL");
        return NULL;
    }
    return node->string;
    
}

struct Node* queryNodeIdDB(int32_t id){
    struct Node *node = NULL;
    if(!idDB) return NULL;
    node = search(idDB,id);
    if(!node) {
        //printf("seach of id DB failed and hence returning NULL");
        return NULL;
    }
    return node;
}

void deleteMapIdDB(int32_t id){
    if(!idDB) 
        return;
    idDB = deleteNode(idDB, id);
    printf("Deleting id %d \n", id);
}

void createMapDataDB(char *string,int32_t currentId){
    dataDB = trieInsert(dataDB,string,currentId);
}

void deleteMapDataDB(char *string) {
    printf("Deleting id %s\n", string);
    if(!dataDB) {
        printf("Nothing to delete");
        return;
    }
    dataDB = trieDelete(dataDB, string);
    //dataDB = trieDeleteOnePass(dataDB, string); 
}

void hDump(){
    heapDump(min);
}

void dumpIdDB(void){
    printf("\n.........ID DB........\n");
    inOrder(idDB);
    printf("\n......................\n");
}

void dumpDataDB(void){
    printf("\n........DATA DB........\n");
    char string[10000];
    trieDumpHelper(dataDB, 0, string);
    printf("\n........DATA DB.........\n");
}

/**********************ACTUAL DB OPERATIONS**********************************/

int32_t create_id(char * string){
    /*Generate an id. .
    Step 0a: If string already exits, just return the id. Also increase ref count
    Step 1a:Get an index from minHeap and if time of the top element is more than SOMETIME, pick it
    Step 1b:If not, Get an index from globalMax, say x,. Bit ARRAY option -? TBD
    Step 2:Now, insert this x in idDB, store the string
    Step 3:insert this string into dataDB, store x here
   */
    if(!dataDB) dataDbInit();
    int32_t currentId = 0;
    currentId = searchDataDB(string);
    if(currentId > 0)
    {
        /*String is already present*/
        struct Node *node  = queryNodeIdDB(currentId);
        node->ref = node->ref + 1;
        return currentId;    
    }

    if(min &&  min->heap_size && ((getCurrentTime() - getMin(min).timestamp) > SOMETIME)){
        struct heapMember x = extractMin(min);  
        printf("\nExtract min {%lf, %d}", x.timestamp, x.id);
        currentId = x.id;
    } else {
        if(globalFree == INT_32_MAX) {
            printf("****SYSTEM MAX REACHED. WAIT A WHILE*****");
            return -1;
        }
        currentId = globalFree++;
    }
    //printf("Inserting id %d and string %s \n", currentId, string);
    createMapIdDB(currentId, string); 
    createMapDataDB(string,currentId);
    return currentId;
}

char * query_id(int32_t id){
     //Search idDB and getch the string.
     char * s = queryIdDB(id);
     if(!s) {
         //printf("\nquery_id returned NULL so return queryyError");
         return queryError;
     } 
     return s;
}

void delete_id(int32_t id){

    /*Step 1: If node is presnt in IdDB only then process*/
    /*Step 2: If node is present and ref is > 1, just ref--*/
    /*Step 3: if ref is 1, delete. 
              delte the DataDB with the node->string.
              then finally delete from idDB*/
    /*Step 4: Add in minHeap for reuse*/

    struct Node *node  = queryNodeIdDB(id);
    if(!node) return;
    if(node && node->ref > 1) {
        node->ref--;
        return;
    }
    deleteMapDataDB(node->string); 
    deleteMapIdDB(id);
    //Genuine delete, so add this index in the heap
    double t = getCurrentTime();
    if(!min) minInit(); //Worst case will make a new instance
    insertKey(min, t, id);
}

