//5.3 计算线性探测、平方探测、以及双散列插入的长随机序列所需要的冲突次数
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include "hash.h"
bool isPrime(int n) //判断是否素数
{
	if (n < 2) { //排除负数
		return false;
	}
	else if (n > 2) {

		for (int i = 2; i < n; i++) {
			if (n % i == 0) {
				return false;
			}
		}
	}
	return true;
}
int nextPrime(long n) //返回一个大于n的素数
{
	if (n < 2) {
		return 2;
	}
	while (!isPrime(++n)) {
	}
	return n;
}

HashTable InitializeTable(int TableSize)//初始化
{
	HashTable H;
	int i;
	H = (HashTable)malloc(sizeof(struct HashTbl));
	if (H == NULL)
		printf("Error");
	else
	{
		H->TableSize = nextPrime(TableSize);//求大于TableSize的下一个素数
		H->TheCell = (Cell*)malloc(sizeof(Cell) * H->TableSize);
		if (H->TheCell == NULL)
			printf("Error");
		else
		{
			for (i = 0; i < H->TableSize; ++i)
			{
				H->TheCell[i].info = Empty;
			}
		}
	}
	return H;
}
int Hash(int num, HashTable H)//散列函数
{
	return num % (H->TableSize);
}
int insertflict(int a, int* num, int size, HashTable H)//冲突计算
{
	int p1;
	int p2;
	int sum;
	if (a == 0)//线性探测
	{
		sum = 0;
		for (int i = 0; i < size; i++)
		{
			p2 = Hash(num[i], H);
			p1 = 0;
			while (H->TheCell[p2].info != Empty && H->TheCell[p2].num != num[i])//sum冲突累计求和
			{
				sum++;
				p2 += ++p1;
				if (p2 >= H->TableSize)
					p2 -= H->TableSize;
			}
			if (H->TheCell[p2].info != legitimate)
			{
				H->TheCell[p2].info = legitimate;
				H->TheCell[p2].num = num[i];
			}
		}
		return sum;
	}
	else if (a == 1)//平方探测
	{
		sum = 0;
		for (int i = 0; i < size; i++)
		{
			p2 = Hash(num[i], H);
			p1 = 0;
			while (H->TheCell[p2].info != Empty && H->TheCell[p2].num != num[i])//sum冲突累计求和
			{
				sum++;
				p2 += 2 * ++p1 - 1;
				if (p2 >= H->TableSize)
					p2 -= H->TableSize;
			}
			if (H->TheCell[p2].info != legitimate)
			{
				H->TheCell[p2].info = legitimate;
				H->TheCell[p2].num = num[i];
			}
		}
		return sum;
	}
	else if (a == 2)//双散列
	{
		sum = 0;
		for (int i = 0; i < size; i++)
		{
			p2 = Hash(num[i], H);
			p1 = 0;
			while (H->TheCell[p2].info != Empty && H->TheCell[p2].num != num[i])//sum冲突累计求和
			{
				sum++;
				p2 += p2 * ++p1;
				if (p2 >= H->TableSize)
				{
					int c;
					c= p2 / H->TableSize;
					p2 = p2-c*H->TableSize;
				}
			}
			if (H->TheCell[p2].info != legitimate)
			{
				H->TheCell[p2].info = legitimate;
				H->TheCell[p2].num = num[i];
			}
		}
		return sum;
	}
	else
	{
		printf("function is nothing!");
		return -1;
	}
}
void delete(HashTable H)
{
	for (int i = 0; i < H->TableSize; ++i)
	{
		H->TheCell[i].info = Empty;
		H->TheCell[i].num = -1;
	}
}
int main()
{
	HashTable T;
	int TableSize = 18;
	T = InitializeTable(TableSize);
	int a[13] = { 3, 6, 20, 24,27,29,31,34,65,78,82 ,88,92};
	int c;
	c = insertflict(0, a, 13, T);
	printf("线性探测冲突次数：%d\n", c);
	delete(T);
	c = insertflict(1, a, 13, T);
	printf("平方探测冲突次数:%d\n", c);
	delete(T);
	c = insertflict(2, a, 13, T);
	printf("双散列探测冲突次数：%d\n", c);

	return 0;
}
