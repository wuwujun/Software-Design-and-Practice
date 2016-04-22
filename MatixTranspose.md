### MatrixTranspose ###
* **Introduction:**

	Normally, we achieve this by transposing column to raw.
	But in this project, we focus on the `sparse matrix`, which can be denoted by `triples table`.
	In this way ,we can save lots of space.
	
	This algorithm is based on triples table : 
	
	Transposing SPMatrix A [m * n] to SPMatrix B [n * m] is equal to tranpose Triple Table A to Triple Table B.

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
		
		
