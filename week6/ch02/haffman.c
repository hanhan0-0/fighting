// a failed try
#include<stdio.h>
#include<stdlib.h>
typedef struct node* Node;
struct node
{
	int p;
	char zf;
	Node right;
	Node left;
	Node parent;
};
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
	swap(&A[center], &A[right - 1]);
	return A[right - 1];
}
void qselect(int A[],int k,int left, int right)
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
		if(k<=i)
		    qselect(A,k, left, i - 1);
		else if(k>i+1)
		    qselect(A, k,i + 1, right);
	}
	else
		Insertion(A + left, right - left + 1);
}
int quickselect(int A[], const int N,int a)
{
	int* B;
	int c;
	B = malloc(sizeof(int) * N);
	for (int i = 0; i < N; i++)
	{
		B[i] = A[i];
	}
	qselect(B, 0, a, N - 1);
	for (int j = 0; j < N; j++)
	{
		if (A[j] = B[a])
			c = j;
	}
	return c;
}
void Huffman(int A[],char B[],int N)
{
	int i;
	Node Huffmantree;
	Huffmantree = malloc(sizeof(struct node)*N);
	Huffmantree[i].parent = NULL;
	Huffmantree[i].left = NULL;
	Huffmantree[i].right = NULL;
	for (i = N; i < N*2; i++)
	{
		Huffmantree[i].parent = NULL;
		Huffmantree[i].left = NULL;
		Huffmantree[i].right = NULL;
	}
	for (i = 0; i < N; i++)
	{
		Huffmantree[i].p = A[i];
		Huffmantree[i].zf =B[i];
	}
	int a, b;
	for (i = 0; i < N - 1; i++)
	{
		a = quickselect(A[i], N, 1);
		b = quickselect(A[i], N, 2);
		Huffmantree[i + N].left = Huffmantree[a].parent;
	}
	
	

}
int main()
{
	int A[14] = { 100.605,100,705,431,242,176,59,185,250,174,199,205,217 };
	char B[15] = { ':','k','h',',','0','1','2','3','4','5','6','7','8','9' };

}
