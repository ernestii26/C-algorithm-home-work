#include <stdio.h>
#include <limits.h>
#define mx 1000005
#define swap(a, b) a^=b^=a^=b
int size;
int a[mx];
void increase(int i, int key)
{
    a[i] = key;
    while(i > 1 && a[i >> 1] < a[i])
    {
        swap(a[i >> 1], a[i]);
        i >>= 1;
    }
}
void insert(int key)
{
    size++;
    a[size] = INT_MIN;
    increase(size, key);
}
int main()
{
    int n, tmp;
    scanf("%d", &n);
    for(int i = 1; i <= n; i++)
    {
        scanf("%d", &tmp);
        insert(tmp); 
    }
    for(int i = 1; i <= n; i++)
        printf("%d ", a[i]);
}