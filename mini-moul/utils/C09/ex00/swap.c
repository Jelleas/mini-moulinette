#include <stdio.h>

void ft_swap(int *a, int *b);

int main(void)
{
    int a = 0;
    int b = 42;
    ft_swap(&a, &b);
    printf("%d", a);
}