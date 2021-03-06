#include<stdlib.h>
#include<stdio.h>
void OptMatrix(const long C[], int N,int M[][10], int LastChange[][10])
{
	int i, k, Left, Right;
	long ThisM;
	for (Left = 1; Left <= N; Left++)
		M[Left][Left] = 0;
	for (k = 1; k < N; k++)
		for (Left = 1; Left <= N - k; Left++)
		{
			Right = Left + k;
			M[Left][Right] = 1000;
			for (i = Left; i < Right; i++)
			{
				ThisM = M[Left][i] + M[i + 1][Right] + C[Left - 1] * C[i] * C[Right];
				if (ThisM < M[Left][Right])
				{
					M[Left][Right] = ThisM;
					LastChange[Left][Right] = i;
				}
			}
		}
}
int main()
{
	int i;
	int a[10][10];
	int b[10][10];
	long c[10] = { 0,5,3,5,6,2,6,2,4,7 };
	OptMatrix(c, 9, a, b);
	printf("最小次数为：\n");
	printf("%d", b[1][6]);
	return 0;
}
