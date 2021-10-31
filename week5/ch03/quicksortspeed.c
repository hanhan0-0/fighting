//测试输入数据和枢纽元的选择对快速排序速度的影响
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<windows.h>
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
void swap(int* a, int* b)
{
	int c;
	c = *a;
	*a = *b;
	*b = c;
}
int median3(int A[], int left, int right)
{
	int center = (left + right) / 2;
	if (A[left] > A[center])
		swap(&A[left], &A[center]);
	if (A[left] > A[right])
		swap(&A[left], &A[right]);
	if (A[center] > A[right])
		swap(&A[center], &A[right]);
	swap(&A[center], &A[right-1]);
	return A[right - 1];
}
void qsort(int A[], int left, int right,int k)
{
	int i, j, pivot;//pivot是枢纽元
	if (left + 3 <= right)
	{
		if (k == 1)//枢纽元选前中后的中位数
		{
			pivot = median3(A, left, right);
			i = left;
			j = right - 1;
		}
		if (k == 2)//第一个元素
		{
			pivot = A[0];
			swap(&A[0], &A[right]);
			i = left-1;
			j = right ;
		}
		if (k == 3)//一个随机元素
		{
			srand((unsigned)time(NULL));
			i = rand()%(right-left+1);
			pivot = A[i];
			i = left - 1;
			j = right+1;
		}
		if (k == 4)//平均值
		{
			int sum=0;
			for (i = 0; i < (right - left + 1); i++)
				sum = sum + A[i];
			pivot = sum / (right - left + 1);
			i = left - 1;
			j = right+1;
		}
		
		for (;;)
		{
			while (A[++i] < pivot) {}
			while (A[--j] > pivot) {}
			if (i < j)
				swap(&A[i], &A[j]);
			else
				break;
		}
		swap(&A[i], &A[right - 1]);
		qsort(A, left, i - 1,k);
		qsort(A, i + 1, right,k);
	}
	else
		Insertion(A + left, right - left + 1);
}
void quicksort(int A[], int N,int k)
{
	qsort(A, 0, N - 1,k);
}
int main()
{
	int i,a;
	i = 100000;
	//int A[100000];//顺序
	int B[100000];//逆序
	//int C[100000];//随机
	clock_t start, finish;
	double  T;
	//快速排序
	a = 0;
	/*while (i--)
	{
		A[a++] = 100000 - i;
	}*/
	while (i--)
	{
		B[a++] =  i;
	}
	
	/*int b;
	while (i--)
	{
		srand((unsigned)time(NULL));
		b= rand()% 100000;
		C[a++] = b;
	}*/
	start = clock();
	//quicksort(A, 100000,1);
	//quicksort(A, 100000,2);
	//quicksort(A, 100000,3);
	//quicksort(A, 100000,4);
	quicksort(B, 100000,2);
	//quicksort(B, 100000,3);
	//quicksort(B, 100000,1);
	//quicksort(B, 100000,4);
	//quicksort(C, 100000,1);
	//quicksort(C, 100000,2);
	//quicksort(C, 100000,4);
	//quicksort(C, 100000,3);
	finish = clock();
	T = ((double)finish - (double)start) / CLOCKS_PER_SEC;
	printf("用的时间为：\n");
	printf("%0.6f\n", T);
	return 0;
}
