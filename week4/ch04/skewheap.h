#pragma once
#ifndef skewheap_h
#define skewheap_h
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
PQ merge1(PQ H1, PQ H2);
PQ merge2(PQ H1, PQ H2);
PQ merge3(PQ H1, PQ H2);
#endif
