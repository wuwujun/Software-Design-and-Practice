#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 1000


//行号和列号均从1开始
struct node
{
	int i;
	int j;
	int value;
};

struct triple
{
	int i_sum;    //行数
	int j_sum;    //列数
	int nzero_sum;
	struct node data[MAXSIZE];
};
typedef struct triple * matrix;

matrix transpose(matrix amt)
{
	matrix bmt = (struct triple *)malloc(sizeof(struct triple));
	bmt->i_sum = amt->j_sum;
	bmt->j_sum = amt->i_sum;
	bmt->nzero_sum = amt->nzero_sum;

	int i, j, k;
	int * num = (int *)malloc(sizeof(int) * (amt->j_sum + 1));
	int * cpot = (int *)malloc(sizeof(int) * (amt->j_sum + 1));

	if (bmt->nzero_sum > 0)
	{
		for (i = 1; i <= amt->j_sum; i++)
			num[i] = 0;
		
		for (i = 1; i <= amt->nzero_sum; i++)
		{
			j = amt->data[i].j;
			num[j]++;    //计算amt中第j列非零元素的个数
		}

		cpot[1] = 1;
		for (i = 2; i <= amt->j_sum; i++)
			cpot[i] = cpot[i - 1] + num[i - 1];    //求第i列第一个非零元素在bmt->data中的位置


		//扫描amt的三元组表，转置
		for (i = 1; i <= amt->nzero_sum; i++)
		{
			j = amt->data[i].j;
			k = cpot[j];

			bmt->data[k].i = amt->data[i].j;
			bmt->data[k].j = amt->data[i].i;
			bmt->data[k].value = amt->data[i].value;
			
			cpot[j]++;  //下一个j列元素在bmt->data中的位置
		}
	}
	return bmt;
}

//以三元组形式打印
void triple_print(matrix mt)
{
	int i;
	for (i = 1; i <= mt->nzero_sum; i++)
	{
		printf("第%d行 第%d列 元素值为%d \n", mt->data[i].i,
			mt->data[i].j, mt->data[i].value);
	}
}


//直接输入数据太过繁琐，使用读文件的形式比较方便
int main()
{
	matrix mt = (struct triple *)malloc(sizeof(struct triple));
	int i, j;

	if (mt != NULL)
	{
		FILE * fp;
		if ((fp = fopen("matrix.txt", "r")) == NULL)
		{
			printf("Fail to open it.\n");
			exit(0);
		}
		
		for (i = 0; !feof(fp); i++)
		{
			fscanf(fp, "%d", &mt->i_sum);
			fscanf(fp, "%d", &mt->j_sum);
			fscanf(fp, "%d", &mt->nzero_sum);

			for (j = 1; j <= mt->nzero_sum; j++)
			{
				fscanf(fp, "%d", &mt->data[j].i);
				fscanf(fp, "%d", &mt->data[j].j);
				fscanf(fp, "%d", &mt->data[j].value);
			}
		}

		fclose(fp);

		printf("原表：\n");
		triple_print(mt);
		printf("\n");

		printf("转置后的表：\n");
		mt = transpose(mt);
		triple_print(mt);
	}

	free(mt);
	getchar();
	return 0;
}