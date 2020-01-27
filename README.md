ID Management Library

The goal is to write an ID management library.  As input, the library takes a pointer to some opaque data of arbitrary length.  The library will return a 32 bit ID to identify the data.  The application should also be able to query for or delete the data using the ID.  If requested to generate an ID for the same data and a valid ID already exists for that data, the existing ID should be returned again.  Ideally, holes in the ID space should be kept to a minimum and recently freed IDs should not be reused for some time.
 
Example usage:
 
create_id ("abcassa") -> id 1
create_id ("kljkl") -> id 2
create_id ("abcassa") -> id 1 (again)
delete_id(1)
query_id(1) -> "abcassa" 
delete_id(1)
query_id(1) -> Not Exists
create_id ("abcassa") -> id 3 (not the recently freed value 1)
create_id ("abcassa") -> id 3 (again)
 
Please submit production quality code along with a running unit test driver for it.  Please explain what design tradeoffs you made and why you chose the approach that you did.






















Design and approach:

Basic functionality points:
1.	Id generator that would generate numbers using an algorithm. Let us call it id-gen algorithm.
2.	Id to Data association, that can be created with pointers/strings & deleted and queried with int32 number. Lets call it id-data-map algorithm.

id-gen

For id-gen, that is to generate unique numbers, we can have multiple approaches. 
1)	{Simple Incrementing index + minheap with timestamp as key}
Since the requirement is to generate sequential numbers, as per example, and also reduce the space to max extent, I chose a simple incrementing index, that would keep allotting numbers till max of int32. Along with this, there will be a minheap data structure, that would maintain the recently deleted numbers. It will behave like a freed pool that are ready to be reused. These minheap data nodes maintain a timestamp and are arranged with timestamp as key, so that the oldest entry is on top. The minimum time is configurable and the entry will be reused only if that time is elapsed. Any reusable id has higher priority over incrementing index.

2)	{Linked list of pre-allocated indexes i.e free list and then an allotted list and then a reuse queue}
The free list is arranged initially as per id numbers in increasing order with the head pointer to 1. When an id is allocated, the node from free list is taken and moved to allocated list.
When an entry is deleted, it is moved from allocated list to reuse queue where the oldest entry is available at the tail, which will picked up if the time is beyond our configured reuse time. This picked up node will re-inserted in free list head.
Note that we can even avoid using reuse list, if the time to reuse is not specified/not -configurable. We can just insert at the end of the free list. So that, it will be reused sometime later. 

3)	Another option is bitArray. bitArray can be used to find the free and available numbers serially and can also be used to allocate and free quickly. But to store int32 integers, we need 67108863 32 bit integers.  This is a very huge number. bitArray is good solution for smaller range of ids. Here it might not scale well in my opinion.
           
Approach chosen and reasons:
I chose approach 1 for its simplicity. Approach 2 is also possible however for large allocations close int32 max, the pool needs to be re-allocated to the capacity. That is it would keep growing. That too since it pre-allocated, there is lot of memory overhead for this requirement where the required id is sequential and not some random value.

Limitations of chosen approach:
In the test where we do a bulk delete beyond the capacity of minheap:
In the implementation, minheap is 10k max capacity. If 20k entries are deleted all at once, then first 10k will be stored in minheap for reuse. However from 10001 to 20k ids cannot be re-used as minheap did not or cannot store beyond its capacity. This will cause a huge hole in id set. 

To avoid this, we need to increase the minheap structure size OR reduce the reuse time to further less time, so that the minheap does not fill up too much. 

This approach is good if minheap is chosen on the basis that bulk deletes will be lesser than the capacity of minheap. That would help maintain id holes to nil.

id-data-map

For id-data-map that stores association of data and the generated id, there can be multiple approaches

1)	AVL tree + Trie
-	AVL tree/RBT tree that can be indexed by id: 
This is because query and delete is based on id, we need to quickly retrieve the data in these cases. RBT/AVL is a safe choice. Both have almost equal time complexity with O(log(n)). However, when search is frequent, AVL is the preferred choice. 
-	Trie that has key as string:
Since create is based on key as a string/pointer, we need Trie like data structure.
The pointer to buffer is given as input which will be used to create this trie. The last character’s trie node in trie structure will store the unique id as well. 
The AVL tree indexed by id will store the string pointer in its node. This is for cross reference. This way both AVL and trie are linked.
A reference count is maintained in AVL tree per index, the node of which will be deleted only when the reference becomes 0. This is to support the requirement that asks for multiple create_id to return the same index and supporting corresponding number of delete_id to actually delete the index. 
Note that trie will have 256 children to account for all ASCII characters. So, it will be easy to store sentences and paragraphs as well, as input to generate an id.

2)	Hash table approach
For storing the strings, create a hashcode out of it and store it in the hash table. Since the hash table cannot be as large as int32, and in fact be a much smaller number, we will have collisions. So we in-turn need to search for the string with the bucket (we will have a sub list per bucket). This is a good approach as it saves a lot of memory especially for really long char */void * data. However, if the number of strings in the sub list is many, the search is linear and might tend to O(n).  
For indexing with id, we need another data structure. We could also use a hash table here as well with just modulo for the id, to index into one of the buckets. This node will have a sublist, and each entry here will link to the other (hash table with string as key) hash table entry. Instead of hash table for id, we could use trees. Hashing might require us to main in-use/valid bits to identify if the list is in use and valid.

Approach chosen and reason:
In approach 2 (Hash table), for hash, we really need a good hashcode generator for generating unique codes for least collision. Given that the number of possible ids are 2 pow 31, the possibility of collision is very high. Moreover we also we need to manage a sublist. Though this solution is possible, I just chose approach 1 for simplicity and predictability for quick turnaround.

Limitations of chosen approach:
a)	The problem with this approach is the inherent assumption that the input will be a string/sentence/paragraph that is null terminated. If it were, a random pointer with associated length, we might need modify the code to some extent.
That is, we can have a solution with input as void *, and store the data byte by byte. However, when a pointer is passed, the corresponding length must be passed. create_id(void *data, int length) would be a better API for this generic approach to store any kind of data, in my opinion.
b)	Another problem is, every Trie node has 256 children to support ASCII set. However, to support latest Unicode data set to support all languages, we need approximately 2 pow 61 entries, which would not scale well at all with respect to storage. So to support Unicode, we might need a flavor of compressed trie.

Code files added:
idDb.c -> This has the main APIs create_id.
idDb.h  
avl.c  -> AVL tree functions for id to string storage and reference
avl.h  
main.c  -> dummy for unit testing. Not used for now.
main.so  -> Need this for python script interface
makefile  -> make file for generating .so file
makefile-c  -> backup for testing using normal executable using main
makefile-so  -> unused
minHeap.c  -> For minheap implementation.
minHeap.h  
test.log  -> sample log
test.py  -> The main test case suite in python using ctypes and unittest
trie.c  -> Trie implementation with id.
trie.h  
work.py  -> helper function for test.py (ctypes function arguments  type definitions)
work.pyc


Compiling and running the code:

Cleaning the files:
make clean 

Compiling (both steps needed):
make
make main.so

Running the test suite
python test.py
or
python test.py > test.log



Unit test description (test.py):
	
For a few tests, I used assert to validate against expected output. For some tests I use dictionaries to cross the check the output. Due to limitation in time, I have not been able to automate all the tests. For example in scale tests, I would need to add the total members in each data structure as well, which would help with scale tests automation. I checked if entries are manually in dump logs(like test.log).

	Tests can be selectively run using defining required tests in skipOrRunTest in test.py
	
	Test 1: Create data, fetch id, query id and cross check if data matches

	Test 2: Delete the id and make sure “Not Exists” is seen. Match with number of creates

Test 3: Create a group of strings

Test 4: Sleep for re-use time or more, delete the entry and verify the id is reused.

Test 5: Create multiple times and queried should give same id. Match with number of  deletes (reference test), should give “Not Exists”

Test 6: Create multiple entries now, if minheap has data past the reuse time, it will be reused

Test 7: Create in a group, delete in a group. Create again in a group, delete again in a group. All entries should be in minheap.

Test 9: Add 1 lakh entries,  delete all, delay of reuse time, create 1000 back. All the 100 entries should be from 1 to 1000, that is reused. 

This test will also reveal the limitation of this solution where minheap can have a max of capacity – in our case 10k. So, if 1 lakh entries were to be deleted, only 10k will be in minheap. The remaining is rejected. So 90k entries are lost and cannot be reused. That is the first 10k entries will be reused when created, beyond which the allocated id would 100001 (1 lakh and 1)

Test 10: Create a group multiple times and delete multiple times for reference and            query testing.

Test 11: See if we can store a paragraph.



