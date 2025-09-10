#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    enum day{mon,tue,wed};

    int stack = tue;

    printf("%d\n", stack);
    if(stack == 1) printf("true\n");

    return 0;
}