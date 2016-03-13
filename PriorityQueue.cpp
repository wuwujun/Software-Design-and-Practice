#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 200 


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

//初始化
heap init_heap()
{
	heap h = (struct HEAP *)malloc(sizeof(struct HEAP));
	h->n = 0;
	return h;
}

//判空
int is_empty(heap h)
{
	return (!h->n);
}

//判满
int is_full(heap h)
{
	return (h->n == MAXSIZE - 1);     //
}

//插入
heap insert(heap h, element_type e)
{
	int i;
	element_type t;

	if (!is_full(h))
	{
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
	}
	else
		printf("ERROR : The heap is full !\n");
	return h;
}

//删除
int del(heap h)
{
	int parent = 1, child = 2;
	element_type e, t, tmp;

	if (is_empty(h))
	{
		printf("ERROR : The heap is empty !\n");
		return INT_MIN;
	}
	else
	{
		e = h->member[1];
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
		return e.value;
	}
}

//改变结点的优先级
heap change_priority(heap h, int pos, int key)
{
	element_type t;

	if (h->member[pos].key < key)
	{
		h->member[pos].key = key;

		while (pos > 1 && h->member[pos].key > h->member[pos / 2].key)
		{
			t = h->member[pos];
			h->member[pos] = h->member[pos / 2];
			h->member[pos / 2] = t;

			pos /= 2;
		}
	}

	return h;
}
//打印
void show_heap(heap h)
{
	int i = 1;
	while (i <= h->n)
	{
		printf("%d ", h->member[i].value);

		if (i != h->n)
			printf("-> ");
		i++;
	}
	printf("\n");
	printf("\n");
}

//查找
int search(heap h, int value)
{
	int i;

	for (i = 1; i <= h->n; i++)
	{
		if (h->member[i].value == value)
			return i;
	}
	return 0;
}

int main()
{
	int flag = 1;
	int choice, i, j, nn, nnn, result;
	heap h = init_heap();
	element_type kkk[10];
	element_type n;

	for (i = 1; i < 10; i++)
	{
		kkk[i - 1].key = 10 - i;
		kkk[i - 1].value = 10 - i;
		h = insert(h, kkk[i - 1]);
	}

	while (flag)
	{
		printf("### FUNCITON TEST ###\n");
		printf("0.Show the priority queue.\n");
		printf("1.Insert a node.\n");
		printf("2.Search the index of one node.\n");
		printf("3.Increase the priority of one node.\n");
		printf("4.Delete the most senior node.\n");
		printf("5.Exit.\n");
		printf("####################################\n");
		printf("\n");
		printf("Please chose one point :\n");

		scanf_s("%d", &choice);

		switch (choice)
		{
			case 0:
				printf("Tips : the priority descends frome left to right. \n");
				show_heap(h);
				break;

			case 1:
				printf("Input the value:\n");
				scanf_s("%d", &n.value);
				printf("Input the priority: \n");
				scanf_s("%d", &n.key);
				h = insert(h, n);
				printf("DONE !\n");
				show_heap(h);
				break;

			case 2:
				printf("Input : \n");
				scanf_s("%d", &nn);
				result = search(h, nn);
				if (result != 0)
					printf("Find %d, its position is %d.\n", nn, result);
				else
					printf("NOT FOUND !\n");
				printf("\n");
				break;

			case 3:
				printf("Input the position of the node : \n");
				scanf_s("%d", &j);
				printf("Input the new priority: \n");
				scanf_s("%d", &nnn);
				h = change_priority(h, j, nnn);
				show_heap(h);
				break;

			case 4:
				result = del(h);
				if (result != INT_MIN)
					printf("The senior node %d has been deleted.\n", result);
				printf("\n");
				break;

			case 5:
				flag = 0;
				break;
		}
	}

	getchar();
	return 0;
}