#include <stdio.h>

int main()
{
	FILE *fp;
	fp = fopen("g", "r");

	int node, adj;
	fscanf(fp, "%d", &node);
	while(fscanf(fp, "%d,%d", &node, &adj) != EOF)
	{
		printf("%d %d\n", node, adj);
	}

	return 0;
}
