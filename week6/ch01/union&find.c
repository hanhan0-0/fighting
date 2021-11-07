#include<stdio.h>
#include<stdlib.h>
void initialize(int S[], int N)
{
	for (int i = 0; i < N; i++)
	{
		S[i] = -1;
	}
}
int Find(int x, int S[])
{
	if (S[x] <= 0)
		return x;
	else
		return Find(S[x], S);
}
void uion1(int S[], int root1, int root2)
{
	S[root2] = root1;
}
void uion2(int S[], int root1, int root2)//按高度
{
	if (S[root2] < S[root1])
		S[root1] = root2;
	else
	{
		if (S[root1] == S[root2])
			S[root1]--;
		S[root2] = root1;
	}
}
void uion3(int S[], int root1, int root2)//按大小
{
	if (S[root2] < S[root1])
	{
		S[root2] = S[root1] + S[root2];
		S[root1] = root2;
		
	}
	else
	{
		S[root1] = S[root1] + S[root2];
		S[root2] = root1;
		
	}
}
int Find1(int x, int S[])
{
	if (S[x] <= 0)
		return x;
	else
		return S[x]=Find(S[x], S);
}
int main()
{
	int A[18];
	int i;
	initialize(A, 18);
	//任意进行
	printf("任意进行的结果为：\n");
	uion1(A, Find(1,A), Find(2,A));
	uion1(A, Find(3, A), Find(4, A));
	uion1(A, Find(3, A), Find(5, A));
	uion1(A, Find(1, A), Find(7, A));
	uion1(A, Find(3, A), Find(6, A));
	uion1(A, Find(8, A), Find(9, A));
	uion1(A, Find(1, A), Find(8, A)); 
	uion1(A, Find(3, A), Find(10, A));
	uion1(A, Find(3, A), Find(11, A));
	uion1(A, Find(3, A), Find(12, A));
	uion1(A, Find(3, A), Find(13, A));
	uion1(A, Find(14, A), Find(15, A));
	uion1(A, Find(16, A), Find(17, A));
	uion1(A, Find(14, A), Find(16, A));
	uion1(A, Find(1, A), Find(3, A));
	uion1(A, Find(1, A), Find(14, A));
	for (i = 1; i < 18; i++)
		printf("%d ",A[i]);
	printf("\n");
	//按高度进行
	printf("按高度进行union的结果为：\n");
	initialize(A, 18);
	uion2(A, Find(1, A), Find(2, A));
	uion2(A, Find(3, A), Find(4, A));
	uion2(A, Find(3, A), Find(5, A));
	uion2(A, Find(1, A), Find(7, A));
	uion2(A, Find(3, A), Find(6, A));
	uion2(A, Find(8, A), Find(9, A));
	uion2(A, Find(1, A), Find(8, A));
	uion2(A, Find(3, A), Find(10, A));
	uion2(A, Find(3, A), Find(11, A));
	uion2(A, Find(3, A), Find(12, A));
	uion2(A, Find(3, A), Find(13, A));
	uion2(A, Find(14, A), Find(15, A));
	uion2(A, Find(16, A), Find(17, A));
	uion2(A, Find(14, A), Find(16, A));
	uion2(A, Find(1, A), Find(3, A));
	uion2(A, Find(1, A), Find(14, A));
	for (i = 1; i < 18; i++)
		printf("%d ", A[i]);
	printf("\n");
	//按大小进行
	printf("按大小进行union的结果为：\n");
	initialize(A, 18);
	uion3(A, Find(1, A), Find(2, A));
	uion3(A, Find(3, A), Find(4, A));
	uion3(A, Find(3, A), Find(5, A));
	uion3(A, Find(1, A), Find(7, A));
	uion3(A, Find(3, A), Find(6, A));
	uion3(A, Find(8, A), Find(9, A));
	uion3(A, Find(1, A), Find(8, A));
	uion3(A, Find(3, A), Find(10, A));
	uion3(A, Find(3, A), Find(11, A));
	uion3(A, Find(3, A), Find(12, A));
	uion3(A, Find(3, A), Find(13, A));
	uion3(A, Find(14, A), Find(15, A));
	uion3(A, Find(16, A), Find(17, A));
	uion3(A, Find(14, A), Find(16, A));
	uion3(A, Find(1, A), Find(3, A));
	uion3(A, Find(1, A), Find(14, A));
	for (i = 1; i < 18; i++)
		printf("%d ", A[i]);
	printf("\n");
	return 0;
}
