#include <stdio.h>
void insert(int a[], int m, int *b)
{
    int data = a[m];
    int i = m - 1;
    while (i > 0 && a[i] > data && *b != 0)
    {
        a[i + 1] = a[i];
        i = i - 1;
        *b = *b - 1;
    }
    a[i + 1] = data;
}
void insertion_sort(int a[], int n, int *b)
{
    for(int i = 1; i <= n; i++)
    {
//        printf("*%d\n", *b);
        insert(a, i, b);
    }
}
int main()
{
    int n, b;
    scanf("%d%d", &n, &b);
    int a[n + 5];
    for(int i = 1; i <= n; i++)
    {
        scanf("%d", &a[i]);
    }
    int nb = b;
    insertion_sort(a, n, &nb);
    printf("The array is ");
    for(int i = 1; i <= n; i++)
    {
        printf("%d ", a[i]);
    }
    printf("after %d back-moves.\n", b - nb);
}
