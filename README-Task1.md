# Task1 #

    Task1 are Software Engineering Homework in the first two week, 
    which includes the skip list, k-m-p algorithm, priority queue, and the matrix transpose.
    
### SikpList ###
* **Introduction:**
    
		SkipList is eqaul to many linked lists in parallel. The node in every raw has the same key. 
		We choose it because it has the same efficiency as AVL tree but it's simpler and it takes up less space.

* **Data Structure:**

 ```c
struct node_str
{
		key_type key;  
		value_type value;  
		struct node_str * next[1];	
};
struct list_str
{
		int level;     
		struct node_str * head;
};
typedef struct list_str * list;
 ```
	
	
* **Functional Interface:**

 ```c
struct node_str * init_node(key_type k, value_type v, int level);         
list init_list();
list insert(list l, key_type k, value_type v);
list del(list l, key_type k);
int search(list l, key_type k);
void free_list(list l);
void print(list l);
int random_level();      
```

>	In `ramdom_level()`, we compute the level which the data will be insert into randomly.
>	We use the method which has the same theory as "coin tossing" :
>>```c
while (rand() % 2)    // rand() % 2 = 0 or 1
{
	k++;
}
 ```
>> 	Particularly,
```c
if (k > max_level)
	k = max_level;
```

>	In `init_list()`, the part for dynamic application of memory space is :
>>```c
list l = (struct list_str *)malloc(sizeof(struct list_str));
```
>>	and we invoke `init_node()` to initialize the head node of the SikpList :
>>```c
l->head = init_node(0, 0, max_level - 1);
```

>	In `init_node()`, the part for dynamic application of memory space is :
>>```c
struct node_str * n = (struct node_str *)malloc(sizeof(struct node_str) + level *sizeof(struct node_str *));
```
    
>	In `insert()`, we finish this work by three steps :
> 
* the first one is to find the index the node should insert into.
> 
if the key has exisited, we return directly.
>>```c
//this marks the node path along which we find the inserts' index
struct node_str * update[max_level];  
```
> 	
* the second one is to get how many levels we should insert, invoke `random_level()`
> 
* if the new level we get is bigger than current level, we should upadate `update[]` and `l->level = level`
> 
* the third one is to insert, we finish this as the same as we do in linked list inserting job

> 
In `del()`, it's similar to the insert process : 
we find the index firstly and then delete the node as we do in linked list deleting job.

>	In `free_list()`, we free nodes layer by layer and then free l 

>	In `print()`, we print the SikpList layer by layer.

