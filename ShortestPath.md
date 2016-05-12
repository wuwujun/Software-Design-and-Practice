# 最短路径问题 #

## 介绍 ##

    这里讨论的图都是带权有向图，最短路径的含义是指路径上各边的权值总和最小。
    
    最短路径问题包括：
    1. 单源最短路径问题；
    2. 所有顶点之间的最短路径问题。
    
    以下将讨论解决以上两个最短路径问题的算法和相对应的优化。

## 数据结构 ##

    都是采用邻接表存储图
    
    1. Dijkstra 算法 
    引入三个辅助数组：
    一维数组d[n]：d[i] 表示源点1到顶点 i 的当前最短路径长度，初始时，d[i] = 边(1,i)的权值；
    一维数组p[n]：p[i] 表示源点1到顶点 i 的当前最短路径上，最后经过的顶点，初始时，p[i]=1（源点）；
    一维数组iss[n]：iss[i] 标记顶点 i 是否已经访问过。
    
    2. 改进的 Dijkstra 算法 
    用到了队列：
```c
struct qu{
	int front;
	int rear;
	int elements[maxsize];
};
typedef struct qu * queue;
```
  
    3. Floyd 算法
    因为 Floyd 算法是动态规划算法，所以必然要利用迭代公式：
    于是引入了辅助数组存放在迭代过程中求得的最短路径长度，
    即迭代公式：
>   cost0[i][j] = C[i][j]

>   costk[i][j] = min{costk-1[i][j],costk-1[i][k]+Ak-1[k][j]}, 0 ≤ k ≤ n-1

    数组p[n][n]：存放从vi到vj求得的最短路径，初始时,p[i][j]= -1。
    
## 算法介绍 ##
### 单源最短路径问题 ###
    
    1. 边上权值非负情形的单源最短路径问题，采用的算法是 Dijkstra 算法： 
    
    Dijikstra(SPF)算法是一种贪心算法，本质是按路径长度的递增次序逐步产生最短路径。
    它的实现和 Prime 非常类似。
    首先求出长度最短的一条最短路径,再参照它求出长度次短的一条最短路径，
    依次类推，直到从顶点v到其它各顶点的最短路径全部求出为止。
    
    2. Dijkstra算法缺陷：
    
    无法处理负权值问题，因为一旦出现负权值的边，可能有包含负权边的回路，
    最后导致一直循环下去，无法求得解。
    
    3. 优化1——解决有负权值边的问题
    
    如果存在负值圈，Dijkstra算法将无限循环下去，因此需要一个机制来确保算法得以中止。
    关键在于判断图中是否存在负开销的回路，这里我们利用队列和一个一维数组scratch：
    
    队列，用来存放待访问顶点；
    scratch数组用于计数，计算每个顶点出队和入队次数，用此来区别它是否还在队列中。
    即，顶点v入队，scratch[v]++；出队，scratch[v]++；
    已经在队列中的顶点w，若只是更新w的权值，scratch[w] += 2。
    显然，若scratch[v]为奇数，则v在队列中，若为偶数，则已经出队。

    由于最短路最长只含有 N - 1 条边，所以如果任何一个顶点已经出队 N + 1 次，则算法停止运行。
    其中 N 为图的顶点数。对应到scratch数组上就是若scratch[w] > 2 * N，说明存在负开销回路。
    
    4. 优化2——无环路有向图(DAG)的最快算法ASP
    
    可以构造一个拓扑升序序列，
    由拓扑排序的性质，无圈图的任意路径中，顶点都是沿着「拓扑升序序列」排列的，因此我们只需要按照这个序列执行更新操作即可。
    显然，这样可以在线性时间内解决问题。因为排序和更新可以在一趟内完成。
    
    5. 要注意的是由于单源最短路径需要给定一个源点，我们采用随机选取的方法，但是出度为0的点显然不能作为源点，
    所以按下面的代码处理一下，p 即为选出的源点。
```c  
for (j = 0; j < gr->n; j++){
	p = gr->list[j].firstedge;
    if (p)
      break;
}
```
    
### 全源最短路径 ###
    1. 所有顶点之间的最短路径问题，采用的算法是 Floyd 算法：
    
    Floyd 算法是一种动态规划算法，显见应用了迭代的方法，所以关键是找出的迭代公式。
    因为算法本质就是通过不断的试探，即在已经确定的路径上依次添加剩下的顶点中，看是否会导致路径权值缩小，是的话就将顶点加入路径。
    由此就能得出迭代公式了，见数据结构部分。
    
    2. 实际上 Floyd 算法只能适用于无负长度的圈的图，我们可以对此做一点改进：
    
    看迭代公式的 cost 数组，考虑 cost[i][i] ，它的含义是由 i 出发再回到 i 的最短路径的长度（权值和），
    如果存在负长度的圈，那 cost[i][i] 一定为负值，用这个条件就可以判断是否存在负长度的圈啦，
    如果存在，说明无法求出最短路径，直接返回即可。
    
    
## 复杂度分析 ##
    1. Dijkstra 算法 
    显而易见，算法两层循环，都是执行 N 次，N 为图的顶点数目，所以时间复杂度为 O(N ^ 2)
    
    2. ASP 算法
    即拓扑排序的效率 O(N + E)，其中 E 为图的边数
    
    2. Floyd 算法 
    显而易见，算法三层循环，都是执行 N 次，N 为图的顶点数目，所以时间复杂度为 O(N ^ 3)

## 参考文献 ##

[带权最短路算法分析](https://www.renfei.org/blog/weighted-shortest-path.html)