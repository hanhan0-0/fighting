#include<stdio.h>
#include<stdlib.h>
void Insertion(int A[], int N)//插入排序
{
	int j, p;
	int tmp;
	for (p = 1; p < N; ++p)
	{
		tmp = A[p];
		for (j = p; j > 0 && A[j - 1] > tmp; j--)
		{
			A[j] = A[j - 1];
		}
		A[j] = tmp;
	}
}
void shellsort(int A[], int N)
{
	int i, j,Increment;
	int Incrementarray[3] = { 1,3,7 };
	int tmp;
	int x = 0;
	for (x = 2; x >-1; x--)
	{
		Increment = Incrementarray[x];
		for (i = Increment; i < N; i++)
		{
			tmp = A[i];
			for (j = i; j >= Increment; j -= Increment)
			{
				if (tmp < A[j - Increment])
					A[j] = A[j - Increment];
				else
					break;
			}
			A[j] = tmp;
		}
	}
}
int main()
{
	int i;
	//插入排序
	int A[9] = { 3,1,4,1,5,9,2,6,5 };
	printf("使用插入排序将序列3,1,4,1,5,9,2,6,5排序： \n");
	Insertion(A,9);
	for ( i= 0; i < 9; i++)
		printf("%d", A[i]);
	//希尔排序
   printf("\n");
   int  B[9] ={ 9,8,7,6,5,4,3,2,1};
   printf("使用增量{1，3，7}对数据9,8,7,6,5,4,3,2,1进行希尔排序： \n");
   shellsort(B, 9);
	for ( i = 0; i < 9; i++)
		printf("%d", B[i]);
}
