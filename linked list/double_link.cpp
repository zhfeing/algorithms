#define DLINK
#include"myhead.h"
void create_DLINK(DLink root, int amount)
{
	if (amount > 0)
	{
		int i;
		DLink p, p_s = root;
		for (i = 0; i < amount; i++, p_s = p)
		{
			p = CREATE_DNODE;
			check_malloc(p);
			p->value = i;
			p_s->fwd = p;
			p->bwd = p_s;
		}
		p_s->fwd = NULL;
		root->bwd = p_s;
		root->fwd->bwd = NULL;
	}
}
void insert_DNODE(DLink root, Data value)
{
	DLink prev, next, newDNode;
	for (prev = root; (next = prev->fwd) != NULL; prev = next)
	{
		if (next->value > value)
			break;
		else if (next->value == value)
			return;
	}
	newDNode = CREATE_DNODE;
	check_malloc(newDNode);
	newDNode->value = value;

	newDNode->fwd = next;
	prev->fwd = newDNode;
	if (prev != root)
		newDNode->bwd = prev;
	else newDNode->bwd = NULL;
	if (next != NULL)
		next->bwd = newDNode;
	else root->bwd = newDNode;
	return;
}
void print_out_DLINK(DLink root)
{
	while (root != NULL)
	{
		printf("%d\n", root->value);
		root = root->fwd;
	}
}
void destroy_DLINK(DLink root)
{
	DLink save = root;
	while ((save = root->fwd) != NULL)
	{
		free(root);
		root = save;
	}
}
int  count_amount(DLink root)
{
	int count = 0;
	while ((root = root->fwd) != NULL)
		count++;
	return count;
}