# 森林和二叉树的相互转换 #

## 介绍 ##
    二叉树是树的一种，森林是树的集合，所以森林和二叉树之间的转换就是树和二叉树之间的转换。
    
    下文将讨论以下两个问题：
    1. 树转换为二叉树
    2. 二叉树转换为树
    
## 数据结构 ##
### 树转换为二叉树 ###
* **森林的存储结构**
```c
struct treenode{
	datatype data;
	int key;
};
typedef struct treenode nodetype;

struct treetype{
	//nodetype (*root)[MAXSIZE];
	nodetype root[MAXSIZE][MAXSIZE];
	int row;
	int column;
	int side;
};

struct FOREST{
	struct treetype treearray[MAXTREENUM];        
	int treenum;
};
typedef struct FOREST * forest;
```
* **二叉树的存储结构**
```c
struct node{
	datatype data;
	struct node * lchild;
	struct node * rchild;
};
typedef struct node * btree;
```


### 二叉树转换为森林 ###
* **森林的存储结构**
```c
struct treenode{
	char data;
	int parent;
	int firstchild;
	int rightsib;
};
typedef struct treenode tree;

struct fo{
	tree treearray[MAXTREENUM][MAXSIZE];
	int treenum;
	int treesize[MAXTREENUM];
};
typedef struct fo * forest;
```

* **算法需要用到队列**
```c
struct q{
	int front;
	int rear;
	struct node * elements[MAXSIZE];  
};
typedef struct q * queue;

```
    
## 算法介绍 ##
### 树转换为二叉树 ###

### 二叉树转换为森林 ###

## 复杂度分析 ##
