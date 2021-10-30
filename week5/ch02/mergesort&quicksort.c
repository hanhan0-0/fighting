//归并排序，快速排序
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
void Merge(int A[], int tmparray[],int lops,int rops,int rightend)
{
	int i, leftend, numelements, tmppos;
	leftend = rops - 1;
	tmppos = lops;
	numelements = rightend - lops + 1;
	while (lops <= leftend && rops <= rightend)
	{
		if (A[lops] <= A[rops])
			tmparray[tmppos++] = A[lops++];
		else
			tmparray[tmppos++] = A[rops++];
	}
	while (lops <= leftend)
		tmparray[tmppos++] = A[lops++];
	while (rops <= rightend)
		tmparray[tmppos++] = A[rops++];
	for (i = 0; i < numelements; i++, rightend--)
		A[rightend] = tmparray[rightend];
}
void MSort(int A[], int tmparray[], int left, int right)
{
	int center;
	if (left < right)
	{
		center = (left + right) / 2;
		MSort(A, tmparray, left, center);
		MSort(A, tmparray, center + 1, right);
		Merge(A, tmparray,left, center + 1, right);

	}
}
void mergesort(int A[], int N)
{
	int *tmparray;
	tmparray = malloc(N * sizeof(int));
	MSort(A, tmparray, 0, N - 1);

}
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
void qsort(int A[], int left, int right)
{
	int i, j, pivot;//pivot是枢纽元
	if (left + 3 <= right)
	{
		pivot = median3(A, left, right);
		i = left;
		j = right - 1;
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
		qsort(A, left, i - 1);
		qsort(A, i + 1, right);
	}
	else
		Insertion(A + left, right - left + 1);
}
void quicksort(int A[], int N)
{
	qsort(A, 0, N - 1);
}
int main()
{
	int i;
	//归并排序
	int A[8] = { 3,1,4,1,5,9,2,6 };
	double time;
	clock_t start, finish;
	start = clock();
	mergesort(A, 8);
	finish = clock();
	time = (double)(finish - start) / CLOCKS_PER_SEC;
	printf("使用归并排序将3，1，4，1，5，9，2，6排序：\n");

	for (i = 0; i < 8; ++i)
	{
		printf("%d ", A[i]);
	}
	printf("\n");
	//快速排序
	printf("使用快速排序将3,1,4,1,5,9,2,6,5,3,5排序：\n");
	int B[11] = { 3,1,4,1,5,9,2,6,5,3,5 };
	quicksort(B, 11);
	for ( i = 0; i < 11; ++i)
	{
		printf("%d ", B[i]);
	}
	
	return 0;
}
