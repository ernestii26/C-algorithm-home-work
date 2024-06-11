#include <stdio.h>
int Getminidx(int a[], int l, int r)
{
    int m = l;
    for(int i = l + 1; i < r; i++)
    {
        if(a[m] > a[i])
            m = i;
    }
    return m;
}
void swap(int* a, int* b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}
void Selsort(int a[], int n, int b)
{
    int count = 0;
    for(int i = 0; i < n; i++)
    {
        int m = Getminidx(a, i, n);
        if(i != m)
        {
            swap(&a[i], &a[m]);
            count++;
            if(count == b)
                break;
        }
    }
    printf("The array is ");
    for(int i = 0; i < n; i++)
    {
        printf("%d ", a[i]);
    }
    printf("after %d swaps.\n", count);
    return;
}
int main()
{
    //freopen("input.txt", "r", stdin);
    int n, b;
    scanf("%d%d", &n, &b);
    int a[n];
    for(int i = 0; i < n; i++)
    {
        scanf("%d", &a[i]);
    }
    Selsort(a, n, b);
}