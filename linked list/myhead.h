#pragma once
#define _INC_MYHEAD

#include<stdio.h>
#include<stdlib.h>

inline void check_malloc(void *point);

#ifdef DLINK

typedef struct tagDNode DNode, *DLink;
typedef int Data;

struct tagDNode
{
	DLink fwd;
	DLink bwd;
	Data value;
};

#define SIZE_D (sizeof(DNode))
#define CREATE_DNODE ((DLink)malloc(SIZE_D))

void create_DLINK(DLink root, int amount);
void insert_DNODE(DLink root, Data value);
void print_out_DLINK(DLink root);
void destroy_DLINK(DLink root);
#endif

#ifdef SLINK

typedef struct tagSNode SNode, *SLink;
typedef int Data;

struct tagSNode
{
	SLink link;
	Data value;
};

#define SIZE_S (sizeof(SNode))
#define CREATE_SNODE ((SLink)malloc(SIZE_S))

void create_SLINK(SLink root, int amount);
void insert_SNODE(SLink root, Data value);
void print_out_SLINK(SLink root);
void destroy_SLINK(SLink root);
int  get_lenth(SLink root);
void reverse_SINK(SLink root);

#endif