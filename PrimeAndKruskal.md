# 最小生成树 #
## Prime 算法和 Kruskal 算法 ##
## 介绍 ##
    这里讨论的图都是带权无向连通图。
    
    构造最小生成树的准则：
    1. 必须使用且仅使用该连通图中的 n - 1 条边连接图中的 n 个顶点；
    2. 不能使用产生回路的边；
    3. 各边上的权值总和达到最小。
    
    最小生成树的两种算法 Prime 和 Kruskal 也是以以上三点为准则的。
    它们都属于贪心算法。
    算法课上已经证明了这两种算法的正确性。
    对于 Prime 算法，可以用二维数组或堆来实现；
    对于 Kruskal 算法，可以用一维数组或并查集来实现。
    
    
## 数据结构 ##
```c
costtype cost[maxsize][maxsize];         //Prime算法边权值数组
                    
struct EDGE{
	int bgn;
	int end;
	costtype wet;
};
typedef struct EDGE Edge;

Edge edges[maxsize];                    //Kruskal算法边权值数组

```
    cost数组时用来存储无向图任意两点间边的权值的，初始化如下：
```c
for (i = 0; i < maxsize; i++){
	for (j = 0; j < maxsize; j++){
		if (j == i)
			cost[i][j] = 0;
		else
			cost[i][j] = INT_MAX - 1;
	}
}
```
    之后，在图初始化的同时对cost数组和edges数组赋值。
    
    要注意的是：
    对于cost数组而言，若两点间无边，对应位置的权值标记为无穷大 INT_MAX - 1。
    之所以不标记为 INT_MAX，是因为后面会用到 lowcost[i] = INT_MAX 来标记顶点 i 已经加入最小生成树中，
    两者区别一下方便后续 lowcost 数组和 closet 数组的更新。
    
## 算法介绍 ##

### Prime 算法 ###

  【1】用二维数组来实现： 

    引入了两个辅助数组：
    lowcost数组用来保存集合V-U中各顶点与集合U中顶点最短边的权值；
    closest数组用来保存依附于该边的（集合V-U中各顶点与集合U中顶点的最短边）在集合U中的顶点。
>
    LOWCOST[j]=min{cost(vk，vj)|vj∈U,LOWCOST[j]}
>
    CLOSEST[j]=k
    
    用所有与给定树根节点有关的边的权值来初始化 lowcost 数组，树根结点的标号来初始化 closest 数组。
    
```c
costtype * lowcost = (costtype *)malloc(sizeof(costtype) * gr->n);
int * closest = (int *)malloc(sizeof(int) * gr->n);

for (i = 0; i < gr->n; i++){
	if (i == 0)
		lowcost[i] = INT_MAX;
	else
		lowcost[i] = cost[0][i]; 
	closest[i] = 0;
}
```
    
    算法的基本过程就是根据给定的树根节点先把它加入集合 U ，找出和它相关的所有边，作为lowcost数组的初始值，
    从中选出权值最小的边加入生成树中，即将该边的另一个结点加入 U。
    用现在的集合 U 更新一遍lowcost数组和closest数组。
    重复这一过程直到做了 N - 1 次【根据构造最小生成树的准则1，因为树根已经给定，只需要确定剩下的 N - 1即可】
    
    
  【2】用小根堆实现
    
    堆的数据结构：
```c
struct element_type{
	costtype key;            
	int tail;
	int head;
};

struct HEAP{
	struct element_type member[maxsize];
	int n;
};
typedef struct HEAP * heap;
```

    在图中取一个顶点为起始点，找出其邻接的所有顶点，将该点和邻接的顶点和边的权值一一压入小根堆中，
    接着从小根堆中退出小根堆的根，将没访问过的两个顶点及其关联边的权值插入到最小生成树中，以此类推。
    
【3】二者比较

    实际上两个算法的本质都是一样的，不过是实现的方式不一样。
    堆实现的时候是将边压入栈中，将边压入栈中的含义就是将边权值和边的两个顶点压入栈中，
    所以结束条件为 E-- = 0，它的效率是与边数和顶点数都有关的。
    在图很复杂的时候，用堆实现比用二维数组实现要更好，而且它也更适合边稀疏的图。
    
    
### Kruskal 算法 ###
    Kruskal算法很好理解，就是先将所有边按权值由小到大排一次序。
    从排好序的边中依次选择，尝试加入生成树，如果加入之后没有产生环路，则确认加入，产生了回路，就舍弃。
    
    所以算法之中很重要的两个点就是排序和判断是否产生回路。
    
    可以用并查集来判断是否产生了回路，这里采用的是引入一个辅助的数组 father 来判断：
    每加入一条边，就将边的一个顶点作为另一顶点的父节点。
    在判断一条边是否加入到生成树之前，通过下面的find函数上溯找到该边的两个节点的最远的祖父节点，
    如果两个顶点的最远的祖父节点是相同的，说明一定有回路存在，那就不能加入了。
```c
int find(int father[], int v){
	int f = v;
	while (father[f] > 0)         //father数组初始化为0
		f = father[f];
		return f;
}
```

## 复杂度分析 ##

* Prime 算法

    分析Prime算法，该算法由两个并列的循环组成，第一个循环次数为vex_num(即顶点的个数N)，
    
    第二个循环，外层循环的次数为N-1，内层的循环次数为N。
    
    所以总体来说，Prim的时间复杂度为O(N^2)，并且该算法与图中边数的多少无关。
    
    所以该算法适合于求边稠密的图的最小生成树。
 
 
* Kruskal算法
 
    Kruskal算法至多对E条边各扫描一次，假若用堆来存放网中的边，则每次选择最小代价的边仅需O(logE)的时间。
    
    又生成树T的每个连通分量可看成是一个等价类，则构造T加入新的边的过程类似于求等价类的过程，
    
    有算法保证其时间复杂度可以达到O(ElogE)。
    
    因此，Kruskal算法的时间复杂度为O(ElogE)。
    
    所以该算法适合求边稀疏的图的最小生成树。
