#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    if(argc != 3) return 1;
    int a = atoi(argv[1]);
    int b = atoi(argv[2]);
    int sum = a + b;
    printf("sum = %d\n", sum);    
    return 0;
}
