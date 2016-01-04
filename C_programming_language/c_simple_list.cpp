#include <stdio.h>
#include <stdlib.h>

struct simple_list
{
	simple_list *next;
	int s;
};

int main()
{
	simple_list *sl = (simple_list*)malloc(sizeof(struct simple_list));
	int a[3] = {1,2,3};
	
	simple_list *node1 = (simple_list*)malloc(sizeof(struct simple_list));
	node1->s = a[0];

	simple_list *node2 = (simple_list*)malloc(sizeof(struct simple_list));
	node2->s = a[1];

	simple_list *node3 = (simple_list*)malloc(sizeof(struct simple_list));
	node3->s = a[2];
	node3->next = NULL;

	sl->next = node1;
	node1->next = node2;
	node2->next = node3;

	simple_list *next;
	sl = sl->next;
	for(; sl; sl=next)
	{
		printf("%d\n", sl->s);
		next = sl->next;		
	}

	return 0;
}
