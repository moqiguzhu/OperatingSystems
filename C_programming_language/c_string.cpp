#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main()
{
	char str1[12] = "Hello";
	char str2[12] = "World";
	char str3[12];
	int len;

	strcpy(str3, str1);
	printf("strcpy(str3, str1): %s\n", str3);

	strcat(str1, str2);
	printf("strcat(str1, str2): %s\n", str1);

	len = strlen(str1);
	printf("strlen(str1) : %d\n", len);

	char *s1 = "Hello";
	char *s2 = "World";
	printf("s1 = %s \n", s1);
	printf("the length of s1 is : %d\n", strlen(s1));

	char *s3 = (char *)malloc(sizeof(char) *( strlen(s1) + strlen(s2)));
	strcat(s3,s1);
	strcat(s3,s2);
	printf("strcat(s1,s2) = %s \n", s3);

	return 0;
}
