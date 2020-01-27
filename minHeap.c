#include "minHeap.h"

void init(struct minHeap *min, int cap) 
{ 
    min->heap_size = 0; 
    min->capacity = cap; 
    min->harr = malloc(sizeof(struct heapMember) *cap); 
    invalidHeap.timestamp = -1;
    invalidHeap.id = -1;
} 

struct heapMember getMin(struct minHeap *min) { return min->harr[0]; } 
int parent(int i) { return (i-1)/2; } 
int left(int i) { return (2*i + 1); } 
int right(int i) { return (2*i + 2); } 


void heapDump(struct minHeap *min){
    int i =0;
    if(!min) return;
    printf("\n.....HEAP DUMP.......\n");  
    for(i =0; i < min->heap_size; i++)
     printf("\n{%lf,%d}",min->harr[i].timestamp, min->harr[i].id);
    printf("\n.....................\n");
}
 
void insertKey(struct minHeap *min, double timestamp, int32_t id) 
{ 
    if (min->heap_size == min->capacity) 
    { 
        printf("\nAlready full!, Sorry\n"); 
        return; 
    } 
    // First insert the new key at the end 
    min->heap_size++; 
    int i = min->heap_size - 1; 
    min->harr[i].timestamp = timestamp;
    min->harr[i].id=id; 
  
    // Fix the min heap property if it is violated 
    while (i != 0 && min->harr[parent(i)].timestamp > min->harr[i].timestamp) 
    { 
       swap(&min->harr[i], &min->harr[parent(i)]); 
       i = parent(i); 
    } 
} 
  
void decreaseKey(struct minHeap *min,int i, double new_val) 
{ 
    min->harr[i].timestamp = new_val; 
    while (i != 0 && min->harr[parent(i)].timestamp > min->harr[i].timestamp) 
    { 
       swap(&min->harr[i], &min->harr[parent(i)]); 
       i = parent(i); 
    } 
} 
  
// Method to remove minimum element (or root) from min heap 
struct heapMember extractMin(struct minHeap *min) 
{ 
    if (min->heap_size <= 0) 
        return invalidHeap;//INT_MAX 
    if (min->heap_size == 1) 
    { 
        min->heap_size--; 
        return min->harr[0]; 
    } 
  
    // Store the minimum value, and remove it from heap 
    struct heapMember root = min->harr[0]; 
    min->harr[0] = min->harr[min->heap_size-1]; 
    min->heap_size--; 
    MinHeapify(min,0); 
  
    return root; 
} 
  
  
void deleteKey(struct minHeap *min, int i) 
{ 
    decreaseKey(min, i, INT_MIN); 
    extractMin(min); 
} 
  
void MinHeapify(struct minHeap *min, int i) 
{ 
    int l = left(i); 
    int r = right(i); 
    int smallest = i; 
    if (l < min->heap_size && min->harr[l].timestamp < min->harr[i].timestamp) 
        smallest = l; 
    if (r < min->heap_size && min->harr[r].timestamp < min->harr[smallest].timestamp) 
        smallest = r; 
    if (smallest != i) 
    { 
        swap(&min->harr[i], &min->harr[smallest]); 
        MinHeapify(min,smallest); 
    } 
} 
  
void swap(struct heapMember *x, struct heapMember *y) 
{ 
    struct heapMember temp;
    temp.timestamp = x->timestamp;
    temp.id = x->id;

    x->timestamp = y->timestamp;
    x->id = y->id;

    y->timestamp = temp.timestamp;
    y->id = temp.id;
 
} 


double getCurrentTime(){

   double time;
   struct timeval tv;
   gettimeofday( &tv, NULL );
   time = tv.tv_sec + ( tv.tv_usec / 1000000.0 );
   return time;
}

