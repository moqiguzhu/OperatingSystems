#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct node
{
    char val[8];
} node;


// the only thing we should remember about strcpy is that we should assure that we have enough space to accept the coming content
int main()
{
    // c1 and c2 will point into the same address
    char *c1 = "hello";
    char *c2 = "world";
    c1 = c2;

    // test1
    char s1[10] = "hello";
    char s2[10] = "world";
    int len1 = strlen(s1);
    int len2 = strlen(s2);
    printf("len1 = %d  len2 = %d\n", len1, len2);
    strcpy(s1,s2);
    printf("s1 = %s  s2 = %s\n", s1, s2); 


    // test2
    char s3[10];
    char s4[10];
    strcpy(s3,s2);
    // following line will produce stack smashed(core dumped)
//  strcpy(s2, "WORLDsgdajhgsdjhgasjdgjsahdgjsagdjgsajdgjsad");
    strcpy(s2, "WORLD");
    strcpy(s4, s2);
    printf("s3 = %s  s4 = %s\n", s3, s4);

    // test3
    node *nodes = malloc(sizeof(node) * 2);
    strcpy(nodes[0].val, s1);
    strcpy(s1, "HELLO");
    strcpy(nodes[1].val, s1);
    printf("nodes[0].val = %s  nodes[1].val = %s\n", nodes[0].val, nodes[1].val);
    return 0;
}
