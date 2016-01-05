#include <stdio.h>
#include <stdlib.h>

int main()
{
    #ifndef _OJ_
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    #endif
    int x;
    scanf("%d", &x);
    printf("x = %d\n", x);
    return 0;
}
