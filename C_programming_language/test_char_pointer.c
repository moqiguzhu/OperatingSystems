#include <stdio.h>

int main()
{
    char *s1 = "Hello";
    char *s2 = "world!!!!";
    printf("address of s1 %p\n", s1);
    printf("address of s2 %p\n", s2);
    s1 = s2;
    printf("address of s1 %p\n", s1);
    return 0;
}
