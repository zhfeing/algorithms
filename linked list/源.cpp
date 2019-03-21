#define SLINK
#include"myhead.h"
#define MAXSIZE 50
int main()
{
	SLink root = CREATE_SNODE;
	root->link = NULL;
	check_malloc(root);
	int data[MAXSIZE];
	int n = 0;
	printf("ENTER NUMBERS WITH \";\" IN THE END\n");
	fflush(stdin);
	while (1 == scanf("%d", &data[n++]) && n < MAXSIZE)
		insert_SNODE(root, data[n - 1]);
	fflush(stdin);
	reverse_SINK(root);
	print_out_SLINK(root);
	printf("THE AMOUNT OF THE LINKS IS %d\n", get_lenth(root));
	destroy_SLINK(root);
	return 0;
}
inline void check_malloc(void *point)
{
	if (NULL == point)
		exit(EXIT_FAILURE);
}