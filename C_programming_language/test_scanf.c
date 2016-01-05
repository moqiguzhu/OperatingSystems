#include <stdio.h>
#include <math.h>

int main()
{
    int n, m;
    scanf("%d", &n);
    scanf("%d", &m);

    printf("n = %d\n", n);
    printf("m = %d\n", m);

    long long max = (long long)pow(2, 32);
    printf("%lld\n", max);

    return 0;
}
