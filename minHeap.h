#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <sys/time.h>
#include <limits.h> 

typedef struct heapMember{
double timestamp;
int32_t id;
}heapMember;

struct heapMember invalidHeap;

typedef struct minHeap{
struct heapMember *harr; // pointer to array of elements in heap 
int capacity; // maximum possible size of min heap 
int heap_size; // Current number of elements in min heap 
}minHeap;

void heapDump(struct minHeap *min);
void swap(struct heapMember *x, struct heapMember *y);
void MinHeapify(struct minHeap *min, int i);  
void init(struct minHeap *min, int cap); 
struct heapMember getMin(struct minHeap *min);
void insertKey(struct minHeap *min, double timestamp, int32_t id); 
void decreaseKey(struct minHeap *min,int i, double new_val);
struct heapMember extractMin(struct minHeap *min);
void deleteKey(struct minHeap *min, int i);
double getCurrentTime();
