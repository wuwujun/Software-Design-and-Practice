### MatrixTranspose ###
* **Introduction:**
	
	矩阵的转置是通过将矩阵A的每一行转换成矩阵B的每一列来实现的，矩阵B称为矩阵A的转置矩阵。
	但是在这个程序中，我们主要关注`稀疏矩阵`，它可以用`三元组`形式进行存储，这样可以节省很多空间。
	其中，将三元组按行优先的顺序，同一行中列号由小到大的规律排列成一个线性表，称为`三元组表`。

	`测试数据按照这样的要求进行提供`
	
	矩阵A的转置可以通过处理三元组表A实现,这里介绍的是稀疏矩阵转置的快速算法：

	一般而言，我们是通过反复搜索A的三元组表，找到第一列、第二列、...，进行转换，这样的时间复杂度往往为O(n * t)，
	其中n为矩阵A的列数，t为矩阵的非零元个数；
	
	如果能只扫描一次A的三元组表就完成，可以大大提高效率。
	
	根据我们规定的存储规则，矩阵A的第一列的第一个非零元素一定存储在三元组表B的第一个位置，
	如果我们知道矩阵A每一列的非零元素个数，就可以推算出第二列的第一个非零元在三元组表B中的位置，
	而且，三元组表A中三元组的存放顺序是先行后列，
	所以对于同一行来说，一定先遇到列号小的元素，因此只需要扫描一遍三元组表A就能完成操作。


* **Data Structure:**
	```c
	struct node
	{
		int i;     //line number (start from 1)
		int j;	   //row number  (start from 1)
		int value;
	};
	struct triple
	{
		int i_sum;    	       //total number of column
		int j_sum;            //total number of row
		int nzero_sum;       //total number of nzero element
		struct node data[MAXSIZE];
	};
	typedef struct triple * matrix;
	```
	
* **Functional Interfaces:** 
	```c
	matrix transpose(matrix amt);
	void triple_print(matrix mt);
	```
>	In `transpose()`, we import two vectors `num[n + 1]`, `cpot[n + 1]`,
	
	>	the former is to denote the number of nonzero elements in A[:j],

	>	the latter is to denote A[:j]'s first nonzero element's index in triple table B.
	
	>	cpot[1]=1;

	>	cpot[col]=cpot[col-1]+num[col-1]; 2≤col≤n

* **Complexity:**
	* Time:	O(n + t)
	* Space: O(n)
		
