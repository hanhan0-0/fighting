#pragma once
#ifndef hash_h
#define hash_h
struct HashTbl;
typedef struct HashTbl* HashTable;
enum Key { legitimate, Empty, dele };
struct HashEntry//单个内存的内容
{
	int num;
	enum Key info;
};
typedef struct HashEntry Cell;
struct HashTbl//散列表
{
	int TableSize;
	Cell* TheCell;
};
#endif
