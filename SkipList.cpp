#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define max_level 10
#define TRUE 1
#define FALSE 0

typedef int key_type;
typedef int value_type;

struct node_str
{
	key_type key;  //存储的数值
	value_type value;  
	struct node_str * next[1];	
};

struct list_str
{
	int level;     //当前跳表的最大层数
	struct node_str * head;
};
typedef struct list_str * list;

//初始化一个节点
struct node_str * init_node(key_type k, value_type v, int level)
{
	struct node_str * n = (struct node_str *)malloc(sizeof(struct node_str) + level *sizeof(struct node_str *));


	if (n == NULL)
	{
		printf("fail to create!");
		return NULL;
	}
	else
	{
		n->key = k;  //
		n->value = v;
		return n;
	}
}

//初始化跳表
list init_list()
{
	int i;

	list l = (struct list_str *)malloc(sizeof(struct list_str));

	if (l == NULL)
	{
		printf("fail to create!");
		return NULL;
	}
	
	l->level = 0;          //
	 
	l->head = init_node(0, 0, max_level - 1); //

	if (l->head == NULL)
	{
		free(l);
		printf("fail !");
		return NULL;
	}

	for (i = 0; i < max_level; i++)
	{
		l->head->next[i] = NULL;
	}

	return l;
}

//随机确定当前数据被插到哪一层
int random_level()
{
	int k = 1;
	
	while (rand() % 2)
	{
		k++;
	}
	
	if (k > max_level)
		k = max_level;

	printf("%d\n", k);
	return k;
}

//插入部分
list insert(list l, key_type k, value_type v)
{
	int i, level;

	struct node_str * update[max_level]; 
	struct node_str * node = l->head;
	struct node_str * node_next = NULL;

	/*--------------------step 1-------------------*/
	for (i = l->level - 1; i >= 0; i--)  
	{

		while ((node_next = node->next[i]) && node_next->key < k)
		{
			node = node_next;
		}
		
		update[i] = node;
	}

	node_next = node->next[0]; //
	if (node_next != NULL)
	{
		if (node_next->key == k)
		{
			printf("Have existed !\n");
			return l;
		}
	}


	/*--------------------step 2-------------------*/
	level = random_level();   //列高

	if (level > l->level)
	{
		for (i = l->level; i < level; i++)      //
		{
			update[i] = l->head;
		}
		l->level = level;
	}

	/*---------------------step 3---------------------*/
	struct node_str * add_node = init_node(k, v, level);
	struct node_str * p = NULL;

	if (add_node != NULL)
	{
		for (i = level - 1; i >= 0; i--)        //
		{
			add_node->next[i] = update[i]->next[i];
			update[i]->next[i] = add_node;
		}
	}

	return l;
}

//删除部分
list del(list l, key_type k)
{
	int i;

	struct node_str * update[max_level];
	struct node_str * node = l->head;
	struct node_str * node_next = NULL;

	for (i = l->level - 1; i >= 0; i--)
	{
		while ((node_next = node->next[i]) && node_next->key < k)
		{
			node = node_next;
		}
		update[i] = node;
	}

	node_next = node->next[0];
	if (node_next == NULL)
	{
		printf("NOT FOUND !\n");
		return NULL;
	}
	else
	{
		if (node_next->key == k)
		{
			for (i = l->level - 1; i >= 0; i--)
			{
				if (update[i]->next[i] == node_next)
				{
					update[i]->next[i] = node_next->next[i];
				}
			}
			free(node_next);

			i = l->level - 1;
			while (l->head->next[i] == NULL && i >= 0)
			{
				l->level = i;
				i--;
			}

			printf("DELETE %d SUCCESS \n", k);
			return l;
		}
		else
		{
			printf("NOT FOUND !\n");
			return NULL;
		}		
	}
}

//查找部分
int search(list l, key_type k)
{
	int i;

	struct node_str  * node_next = NULL;
	struct node_str * node = l->head;

	for (i = l->level - 1; i >= 0; i--)
	{
		while ((node_next = node->next[i]) && node_next->key < k)
			node = node_next;

		if (node_next != NULL)
		{
			if (node_next->key == k)
			{
				return TRUE;
			}
		}
	}

	return FALSE;
}

//释放部分
void free_list(list l)
{
	if (l)
	{
		struct node_str * node = l->head;
		struct node_str * node_next = NULL;

		while (node)
		{
			node_next = node->next[0];
			free(node);
			node = node_next;
		}

		free(l);          //?
	}
}

//打印部分
void print(list l)
{
	int i;
	struct node_str * node;

	for (i = 0; i < l->level; i++)          //
	{
		printf("L%d: ", i);
		
		node = l->head->next[i];

		while (node != NULL)
		{
			printf("%d -> ", node->key);
			node = node->next[i];
		}
		
		printf("NULL\n");
	}
}

//给定的是一组无序数据
int main()
{
	int i, p, result, choice;
	int flag = 1;
	int num[7] = {4, 6, 3, 2, 5, 9, 7};

	struct list_str li;
	list l = &li;

	l = init_list();

	srand((unsigned)time(NULL));

	for (i = 1; i < 8; i++)
	{
		l = insert(l, num[i - 1], i);
	}

	printf("=== Creat Skip List ===\n");
	print(l);

	while (flag)
	{
		printf("### Function Test ###\n");
		printf("Please chose one point:\n");
		printf("1.Insert\n");
		printf("2.Delete\n");
		printf("3.Search\n");
		printf("4.Exit\n");
		scanf_s("%d", &choice);

		switch (choice)
		{
			case 1:
				printf("=== Insert ===\n");

				printf("Input: ");
				scanf_s("%d", &p);

				l = insert(l, p, 1);
				printf("New list: \n");
				print(l);
				break;

			case 2:
				printf("=== Delete ===\n");

				printf("Input: ");
				scanf_s("%d", &p);

				l = del(l, p);
				if (l != NULL)
				{
					printf("New list: \n");
					print(l);
				}
				else
					printf("The list is NULL\n");
				break;

			case 3:
				printf("=== Search ===\n");

				printf("Input: ");
				scanf_s("%d", &p);

				result = search(l, p);

				if (result) printf("%d FOUND !\n", p);
				else
					printf("%d NOT FOUND !\n", p);
				break;

			case 4:
				flag = 0;
				break;
		}
	}

	free_list(l);
	getchar();
	return 0;
}