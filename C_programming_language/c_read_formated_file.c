#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node
{
	node *next;
	int ele;
};


int main()
{
	FILE *fp;
	fp = fopen("g", "r");
	
	int len = 1000;
	char line[1000];
	char *pch;

	while(fgets(line, len, fp) != NULL)
	{
		pch = strtok(line, ", '\t'");
		while(pch != NULL)
		{
//			printf("%s ", pch);
			printf("%d ", atoi(pch));
			pch = strtok(NULL, ", ");
		}

	
//		int node_label, adj, weight;
//		sscanf(line, "%d", &node_label);
//		printf("%d\n", node_label);
//
//		sscanf(line, "%d", &node_label);
//		printf("%d\n", node_label);
//
//
//		while(sscanf(line, "%d,%d", &adj, &weight) == 2)
//		{
//			printf("%d %d\n", adj, weight);
//		}
	}

	return 0;
}
