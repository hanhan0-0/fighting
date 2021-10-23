//合并两个左式堆H1和H2
#include <stdio.h>
#include <stdlib.h>
#include"priorityqueue.h"
#define insert(x,H)(H=insert1((x),H))
int i = 0;
int Max(PQ T1, PQ T2)
{
	if (T1 == NULL && T2 == NULL)
		return -1;
	else if (T1 == NULL)
		return T2->height;
	else if (T2 == NULL)
		return T1->height;
	else
	{
		if (T2->height > T1->height)
			return T2->height;
		else
			return T1->height;
	}
}
PQ intial(int num)
{
	PQ H;
	H = malloc(sizeof(struct Treenode));
	H->num = num;
	H->left = NULL;
	H->right = NULL;
	H->Npl = 0;
	H->height = 0;
	return H;
}
PQ swapchild(PQ H)
{
	PQ H1;
	H1 = H->left;
	H->left = H->right;
	H->right = H1;
	return H;
}
PQ merge1(PQ H1,PQ H2)
{
	if (H1->left == NULL)
		H1->left = H2;
	else
	{
		H1->right = merge(H1->right, H2);
		if (H1->left->Npl < H1->right->Npl)
			H1=swapchild(H1);
		H1->Npl = H1->right->Npl + 1;
		
	}
	H1->height = Max(H1->left, H1->right) + 1;
	return H1;
}
PQ merge(PQ H1, PQ H2)
{
	if (H1 == NULL)
		return H2;
	else if (H2 == NULL)
		return H1;
	else if (H1->num < H2->num)
		return merge1(H1, H2);
	else
		return merge1(H2, H1);
}
PQ insert1(int num, PQ H1)
{
	PQ H;
	H = intial(num);
	return merge(H, H1);
}
void printTree(int h, const PQ T)
{

	if (T == NULL)
		return;
	if (T->left != NULL && T->right != NULL)
	{
		T->left->height = Max(T->left, T->right);
		T->right->height = Max(T->left, T->right);
	}
	int m = h - T->height;
	while (m != 0)
	{
		m = m - 1;
		printf(" ");
	}
	printf("%d\n", T->num);
	printTree(h, T->left);;
	printTree(h, T->right);
}
PQ creat1()
{
	PQ H1;
	H1 = intial(2);
	insert(11, H1);
	insert(5, H1);
	insert(8, H1);
	H1=swapchild(H1);
	insert(12, H1);
	insert(17, H1);
	insert(15, H1->right->left);
	H1->right->height = Max(H1->right->left, H1->right->right) + 1;
	insert(18, H1->left->right);
	H1->left->height = Max(H1->left->left, H1->left->right) + 1;
	H1->height= Max(H1->left, H1->right) + 1;
	return H1;
}
PQ creat2()
{
	PQ H1;
	H1 = intial(4);
	insert(9, H1);
	insert(6, H1);
	insert(11, H1);
	H1 = swapchild(H1);
	insert(18, H1);
	insert(10, H1);
	insert(21, H1->right->left);
	H1->right->height = Max(H1->right->left, H1->right->right) + 1;
	insert(31, H1->left->left);
	H1->left->height = Max(H1->left->left, H1->left->right) + 1;
	H1->height = Max(H1->left, H1->right) + 1;
	return H1;
}
int main()
{
	PQ H1,H2,H3;
	printf("H1为：\n");
	H1 = creat1();
	H2 = creat2();
	printTree(H1->height, H1);
	printf("H2为：\n");
	printTree(H2->height, H2);
	printf("将H1、H2合并为：\n");
	H3 = merge(H1, H2);
	printTree(H1->height, H3);
	return 0;
}

