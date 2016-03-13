#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define max_num 50

int next_array[max_num];

//递归求next数组
void find_next(char * st, int next[])
{
	int len = strlen(st);
	next[0] = -1;
	int k = -1, j = 0;

	while (j < len - 1)
	{
		if (k == -1 || st[k] == st[j])
		{
			k++;
			j++;

			if (st[j] != st[k])
				next[j] = k;
			else
				next[j] = next[k];
		}
		else
			k = next[k];
	}
}

//利用next数组进行匹配
int kmp_index(char * ts, char * ps, int next[])
{
	int i = 0, j = 0;

	int ts_len = strlen(ts);
	int ps_len = strlen(ps);

	while (i < ts_len && j < ps_len)
	{
		if (j == -1 || ts[i] == ps[j])
		{
			i++;
			j++;
		}
		else
		{
			j = next[j];
		}
	}

	if (j == ps_len)
		return i - j;
	else
		return -1;
}

int main()
{
	char * ts = (char *)malloc(max_num * sizeof(char));
	char * ps = (char *)malloc(max_num * sizeof(char));

	if (!ts || !ps)
	{
		printf("Memory allocation fails \n");
		exit(0);
	}

	printf("Please input a text string :\n");

	gets_s(ts, max_num);

	printf("Please input a pattern string :\n");

	gets_s(ps, max_num);

	find_next(ps, next_array);

	int result = kmp_index(ts, ps, next_array);

	if (result == -1)
		printf("Match fail \n");
	else
		printf("Match succeed and the match index is %d \n", result);

	free(ts);
	free(ps);

	getchar();
	return 0;
}
