#include <stdio.h>
#include <limits.h>
#define mx 1000005
#define swap(a, b) a^=b^=a^=b
int b, t = 0;
int partition(int a[], int l, int r)
{
    int pivot = a[l];
    int i = l + 1, j = r;
    while(i < j)
    {
        while(i <= r && a[i] <= pivot)
            i++;
        while(j>= l && a[j] > pivot)
            j--;
        if(i >= j)
            break;
        swap(a[i], a[j]), t++;
        if(b == t)
            return -1;
    }
    if(l < j && a[l] > a[j])
        swap(a[l], a[j]), t++;
    return j;
}
void quicksort(int a[], int l, int r)
{
    if(l >= r)
        return;
    int m = partition(a, l, r);
    if(b == t)
        return;
    quicksort(a, l, m - 1);
    if(b == t)
        return;
    quicksort(a, m + 1, r);
}

int main()
{
    int n, tmp;
    scanf("%d%d", &n, &b);
    int a[n + 1];
    for(int i = 1; i <= n; i++)
    {
        scanf("%d", &a[i]);
        
    }
    quicksort(a, 1, n);
    printf("The array is ");
    for(int i = 1; i <= n; i++)
        printf("%d ", a[i]);
    printf("after %d swaps.\n", t);
}