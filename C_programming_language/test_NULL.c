#include <stdio.h>

void foo(char *s)
{
    s = NULL;
}


int main()
{
    char *s = "a";
    foo(s);
    if(!s)
        printf("hello world!!!\n");
    else
        printf("dangerous!!!\n");
    return 0;
}
