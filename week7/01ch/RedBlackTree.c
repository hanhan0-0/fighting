//关于红黑树插入过程
#include"stdlib.h"
#include"stdio.h"
typedef enum ColorType {Red,Black}ColorType;
typedef struct RedBlackNode* RedBlackTree;
typedef struct RedBlackNode* Position;
static Position X, P, GP, GGP;
struct RedBlackNode
{
	int num;
	RedBlackTree Left;
	RedBlackTree Right;
	ColorType Color;
};
Position NullNode = NULL;
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
RedBlackTree Initialize()
{
	RedBlackTree T;
	if (NullNode == NULL)
	{
		NullNode = malloc(sizeof(struct RedBlackNode)); 
		if (NullNode == NULL)
			printf("Out of space!!!");
		NullNode->Left = NullNode->Right = NullNode;
		NullNode->Color = Black;
		NullNode->num = 100;
	} /* Create the header node */
	T = malloc(sizeof(struct RedBlackNode)); 
	if( T == NULL)
	    printf("Out of space!!!");
	T->num = 1;
	T->Left = T->Right = NullNode;
	T->Color = Black;
	return T;
}
static Position Rotate(int Item, Position Parent)
{
	if (Item < Parent->num)
		return Parent->Left = Item < Parent->Left->num ? SingleRotateWithLeft(Parent->Left) : SingleRotateWithRight(Parent->Left);
	else
		return Parent->Right = Item < Parent->Right->num ? SingleRotateWithLeft(Parent->Right) : SingleRotateWithRight(Parent->Right);
}
static void HandleReorient(int Item, RedBlackTree T)
{
	X->Color = Red; /* Do the color flip */
	X->Left->Color = Black;
	X->Right->Color = Black;
	if (P->Color == Red) /* Have to rotate */
	{
		GP->Color = Red;
		if ((Item < GP->num) != (Item < P->num))
			P = Rotate(Item, GP); /* Start double rotation */
		X = Rotate(Item, GGP );
		X->Color = Black;
	}
	T->Right->Color = Black; /* Make root black */
}
RedBlackTree Insert(int Item, RedBlackTree T)
{
	X = P = GP = T;
	NullNode->num = Item;
	while (X->num != Item) 
	{
		GGP = GP; GP = P; P = X;
		if (Item < X->num)
			X = X->Left;
		else
			X = X->Right;
		if (X->Left->Color == Red && X->Right->Color == Red)
			HandleReorient(Item, T);
	}
	if (X != NullNode)
		return NullNode;
	X = malloc(sizeof(struct RedBlackNode));
	if (X == NULL)
		printf("Out of space!!");
	X->num = Item;
	X->Left = X->Right = NullNode;
	if (Item < P->num)
		P->Left = X;
	else
		P->Right = X;
	HandleReorient(Item, T);
	return T;
}
static void DoPrint(RedBlackTree T)
{
	if (T != NullNode)
	{
		DoPrint(T->Left);
		printf("%d ",T->num);
		DoPrint( T->Right );
	}
}	
void PrintTree(RedBlackTree T) 
{
	DoPrint(T->Right);
}

int main()
{
	RedBlackTree T;
	T = Initialize();
	T = Insert(10,T);
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
	PrintTree(T);

	return 0;
}
