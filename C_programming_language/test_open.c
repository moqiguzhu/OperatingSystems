#include <stdio.h>
#include <fcntl.h>

int main()
{
	int fd = open("foo", O_CREAT);
	printf("%d\n", fd);
}
