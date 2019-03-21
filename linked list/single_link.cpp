#define SLINK
#include"myhead.h"
void create_SLINK(SLink root, int amount)
{
	if (amount > 0)
	{
		int i;
		SLink p, p_s = root;
		for (i = 0; i < amount; i++, p_s = p)
		{
			p = CREATE_SNODE;
			check_malloc(p);
			p->value = i;
			p_s->link = p;
		}
		p_s->link = NULL;
	}
}
void insert_SNODE(SLink root, Data value)
{
	SLink prev, next, newSNode;
	for (prev = root; (next = prev->link) != NULL; prev = next)
	{
		if (next->value > value)
			break;
		else if (next->value == value)
			return;
	}
	newSNode = CREATE_SNODE;
	check_malloc(newSNode);
	newSNode->value = value;
	prev->link = newSNode;
	newSNode->link = next;
}
void print_out_SLINK(SLink root)
{
	root = root->link;
	while (root != NULL)
	{
		printf("%d\n", root->value);
		root = root->link;
	}
}
void destroy_SLINK(SLink root)
{
	SLink save = root;
	while ((save = root->link) != NULL)
	{
		free(root);
		root = save;
	}
}
int  get_lenth(SLink root)
{
	SLink p = root;
	int count = 0;
	while ((p = p->link) != NULL)
		count++;
	root->value = count;
	return count;
}
void reverse_SINK(SLink root)
{
	SLink p;
	if ((p = root->link) != NULL)
	{
		SLink q;
		SLink save = NULL;
		while ((q = p->link) != NULL)
		{
			p->link = save;
			save = p;
			p = q;
		}
		root->link = p;
	}
}