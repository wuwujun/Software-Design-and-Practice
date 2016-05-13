# 森林和二叉树的相互转换 #

## 介绍 ##
    二叉树是树的一种，森林是树的集合，所以森林和二叉树之间的转换就是树和二叉树之间的转换。
    
    下文将讨论以下两个问题：
    1. 森林转换为二叉树
    2. 二叉树转换为森林
    
## 数据结构 ##
### 森林转换为二叉树 ###
* **森林的存储结构**
	
		树的存储结构是二维数组，行列数均为树的结点总数，如果结点 i 和 j 之间有边，
		则对应二维数组 root[i][j].key 置为 1， 否则置为 0。
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
		int side;		//树的边数
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

		这里，森林中的树采取的是双亲表示法（单练表示、父链表示），树的双亲表示法实质上是一个静态链表。
		存储特点是将每个节点层序地存储在一维数组里，同时记录其唯一双亲结点的下标和紧挨着的兄弟节点的下标。
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
		int treenum;					//森林中树的总数
		int treesize[MAXTREENUM];			//森林中每颗树的大小
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
### 森林转换为二叉树 ###

		森林转换为二叉树实际就是将森林中的每颗树转换为二叉树，取森林中任意一棵树的根作为二叉树的根。
		设森林中树结点数目为 N ，则先初始化 N 个二叉树的结点，节点存储的数据与树中 N 个节点存储的数据完全一致。
		
		然后，森林中的树一棵一棵依次转换为二叉树。
		即，第一棵树转换为二叉树，二叉树根的右子树是空的，再将第二棵树转换为二叉树根的右子树，依此类推。
		这个过程可以先单独将每颗树转换为二叉树，然后将所得的每棵二叉树的根节点如下连接起来即可：
```c
for (i = 1; i < ft->treenum; i++){
	bt[i - 1]->rchild = bt[i];
}
```
		单独看一棵树怎么转换为二叉树：
		因为树的存储结构是二维数组，所以直接按行扫描二维数组即可，遇到两个结点之间有树边的，
		则将二叉树相对应节点的边连起来就好。
		主要要考虑是作为左儿子连起来还是右儿子连起来：
		
		
		
		

### 二叉树转换为森林 ###

## 复杂度分析 ##
* **森林转换为二叉树**
	
		设森林中树的数目为 N ，每颗树的边数为 s1 s2 s3 s4... sn，每颗树的顶点数为 p1 p2 p3 p4... pn，
		则单独一棵树转换为二叉树的时间为：si * pi，最后将这样得到的每棵二叉树组合成二叉树所需要的时间为 N,
		
