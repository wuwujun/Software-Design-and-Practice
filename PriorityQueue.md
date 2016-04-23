### PriorityQueue ###

* **Introduction**

    Every element in the PriorityQueue has its own priority, and the element with highest priority was serviced firstly. 
    
    The elements which have the same priority was serviced according to their order in the queue. 
    
    PriorityQueue is always achieved by heap. In this program, we use `Maximum Heap` to achieve it, and we finish four functions:
    
    insert, delete, search and adjust node's priority.
    
* **Data Structure**

  ```c
  struct element_type
  {
  	  int key;       //优先级
    	int value;      //存储的信息
  };

  struct HEAP
  {
  	  struct element_type member[MAXSIZE];
  	  int n;    
  };
  typedef struct HEAP * heap;
  ```
  
* **Functional Interface**
  ```c
  heap init_heap();
  int is_full(heap h);
  int is_empty(heap h);
  heap insert(heap h, element_type e);
  int del(heap h);
  heap change_priority(heap h, int pos, int key);
  int search(heap h, int value);
  void show_heap(heap h);
  ```
  
  >     
     Both in `del()` and `insert()`, we should adjust the heap to satisfy heap's characters after inserting or deleting one node.
     Particularly, 
  >   
     In `del()`, we just need to delete the top element of the heap and return its value. 
     In this case, it's the element of the highest priority.
     
  >>    In `insert(heap h, element_type e)`, we adjust the heap in this way : 
    
  >>```c
  h->n++;
i = h->n;
	h->member[i] = e;
  while (i != 1 && e.key > h->member[i / 2].key)
  {
  	  t = h->member[i / 2];
  	  h->member[i / 2] = h->member[i];
  	  h->member[i] = t;
      i = i / 2;
  }
  ```
  >>    Firstly add it as a leaf node, and then just compare it with its father node until it has encountered the root.
    
  >>    In `del(heap h)`, we adjust the heap in this way :
  
  >>```c
  t = h->member[h->n];
h->member[h->n] = h->member[1];
	h->member[1] = t;
	h->n--;
  while (child <= h->n)  
{
		if (child < h->n && h->member[child].key < h->member[child + 1].key)
				child++;
		if (t.key >= h->member[child].key)
				break;
		tmp = h->member[parent];
		h->member[parent] = h->member[child];
		h->member[child] = tmp;
		parent = child;
		child *= 2;
}
	```
	>>    Firstly we exchange the root with the last leaf so that we just need to delete the last leaf.
	
	>>    And then, we adjust the heap using the top-down strategy. 
	
	>>    That is to say, we compare the new root with its children :
	
	>>    If bigger, do nothing; if smaller, exchange.
	
  >   In `change_priority(heap h, int pos, int key)`, the operation is similar to the content above.
	
	
* **Complexity**

  * Time: 
    * Initial: O(nlogn)
    * Insert, delete and change priority: O(logn)
    * Search: O(n)
    
  * Space: O(n)
