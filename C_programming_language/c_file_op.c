#include <stdio.h>

int main()
{
	FILE *fp;

	fp = fopen("/tmp/test.txt", "w+");
	fputc(97, fp);
	fprintf(fp, "\n");
	fprintf(fp, "THis is testing for fprintf...\n");
	fputs("This is testing for fputs...\n", fp);
	
	fclose(fp);
	fp = fopen("/tmp/test.txt", "r");
	int i = fgetc(fp);
	printf("%d\n", i);

	char buff[255];
	fgets(buff, 255, fp);
	printf("2: %s\n", buff);

	fscanf(fp, "%s", buff);
	printf("3: %s\n", buff);
	
	fgets(buff, 255, fp);
	printf("4: %s\n", buff);

	fclose(fp);

	return 0;
}
