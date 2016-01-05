#include <stdio.h>
#include <string.h>

int main()
{
    char *s1 = "hello";
    char *s2 = "world";
    printf("hello > world? %d\n", strcmp(s1,s2));
    return 0;
}
