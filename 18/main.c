#include <stdio.h>
#define mx 1000005
#define swap(a, b) (a ^= b ^= a ^= b)
int p[mx];
int rank[mx];
int find(int x)
{
    if(x != p[x])
        p[x] = find(p[x]);
    return p[x];  
}
void unions(int x, int y)
{
    x = find(x), y = find(y);
    if(x != y)
    {
        if(rank[x] > rank[y])
            p[y] = x;
        else
        {
            p[x] = y;
            if(rank[x] == rank[y])
                rank[y] += 1;
        }
            //swap(x, y);
    }
}
void printpath(int x)
{
    //printf("!%d\n", x);
    int k = x;
    while(p[k] != k)
        printf("%d ", k), k = p[k];
    printf("%d\n", k);
}
int main()
{
    int n, m, x, y;
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= n; i++)
        p[i] = i;
    //printf("#%d %d\n", n, m);
    while(m--)
    {
        char c[2];
        scanf("%s", c);
        //printf("%c\n", c[0]);
        if(c[0] == 'F')
            scanf("%d", &x), find(x);
        else if(c[0] == 'U')
            scanf("%d%d", &x, &y), unions(x, y);
        else
        {
           
            scanf("%d", &x), printpath(x);
        }
    }
}