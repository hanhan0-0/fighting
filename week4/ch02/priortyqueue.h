#pragma once
#ifndef quene_h
#define quene_h
struct Treenode;
typedef struct Treenode* PQ;
struct queue;
typedef struct queue* Q;
struct Treenode
{
	int num;
	PQ right;
	PQ left;
	int Npl;
	int height;
};
PQ merge(PQ H1, PQ H2);
#endif

