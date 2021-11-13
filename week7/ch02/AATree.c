//关于AATree的相关操作
#include"stdlib.h"
#include"stdio.h"
typedef struct AANode* AATree;
typedef struct AANode* Position;
Position NullNode = NULL; /* Needs more initialization */
struct AANode
{
	int num;
	AATree	Left;
	AATree	Right;
	int	Level;
};
AATree Initialize(void)
{
	if (NullNode == NULL)
	{
		NullNode = malloc(sizeof(struct AANode)); 
		if (NullNode == NULL)
			printf("Out of space!!!"); 
		NullNode->Left = NullNode->Right = NullNode;
		NullNode->Level = 0;
	}
    return NullNode;
}
Position SingleRotateWithLeft(Position T)//左左
{
	Position P;
	P = T->Left;
	T->Left = P->Right;
	P->Right = T;
	return P;

}
Position SingleRotateWithRight(Position T)//右右
{
	Position P;
	P = T->Right;
	T->Right = P->Left;
	P->Left = T;
	return P;
}
AATree Skew(AATree T)
{
	if (T->Left->Level == T->Level)
		T = SingleRotateWithLeft(T); 
	return T;
}
AATree Split(AATree T)
{
	if(T->Right->Right->Level == T->Level)
	{
		T = SingleRotateWithRight(T);
		T->Level++;
	}
	return T;
}
AATree Insert(int Item, AATree T)
{
	if (T == NullNode)
	{
		T = malloc(sizeof(struct AANode));
		if (T == NULL)
			printf("Out of space!!!");
		else
		{
			T->num = Item;
			T->Level = 1;
			T->Left = T->Right = NullNode;
		}
		return T;
	}
	else if (Item < T->num)
		T->Left = Insert(Item, T->Left);
	else if (Item > T->num)
		T->Right = Insert(Item, T->Right);
	T = Skew(T);
	T = Split(T);
	return T;
}
AATree Remove(int Item, AATree T)
{
	static Position DeletePtr, LastPtr;
	if (T != NullNode)
	{
		LastPtr = T;
		if (Item < T->num)
			T->Left = Remove(Item, T->Left);
		else
		{
			DeletePtr = T;
			T->Right = Remove(Item, T->Right);
		}
	}
	if (T == LastPtr)
	{
		if (DeletePtr != NullNode && Item == DeletePtr->num)
		{
			DeletePtr->num = T->num;
			DeletePtr = NullNode;
			T = T->Right;
			free(LastPtr);
		}
	}
	else if (T->Left->Level < T->Level - 1 || T->Right->Level < T->Level - 1)
	{
		if (T->Right->Level > --T->Level)
			T->Right->Level = T->Level;
		T = Skew(T);
		T->Right = Skew(T->Right);
		T->Right->Right = Skew(T->Right->Right);
		T = Split(T);
		T->Right = Split(T->Right);
	}
	return T;
}
void PrintTree(Position T)
{
	if (T != NullNode)
	{
		PrintTree(T->Left);
		printf("%d ", T->num);
		PrintTree(T->Right);
	}
}
int main()
{
	AATree T;
	T = Initialize();
	T = Insert(10, T);
	T = Insert(85, T);
	T = Insert(15, T);
	T = Insert(70, T);
	T = Insert(20, T);
	T = Insert(60, T);
	T = Insert(30, T);
	T = Insert(50, T);
	T = Insert(65, T);
	T = Insert(80, T);
	T = Insert(90, T);
	T = Insert(40, T);
	T = Insert(5, T);
	T = Insert(55, T);
	T = Insert(35, T);
	printf("AA树的中序遍历为：\n");
	PrintTree(T);
	Remove(60,T);
	printf("\n");
	printf("AA树删掉60节点后为：\n");
	PrintTree(T);
	return 0;
}
