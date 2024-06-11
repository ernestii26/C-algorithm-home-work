#include <stdio.h>
int *t;
void f(int *x, int *y)
{
    x = y;
}
int main()
{
    printf("$");
    int a = 2;
    int *y;
    y = &a;
    f(t, y);
    printf("%d", *t);
}