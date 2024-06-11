#include <stdio.h>
#define swap(i, j) (i^=j^=i^=j)
#define mx 2005
#define int long long
int check(int a[], int i)
{
    
    if(1ll * (0ll + a[i - 1] - a[i - 2]) * (0ll + a[i] - a[i - 1]) < 0ll)
        return 1;
    return 0;
}
void permu(int a[], int n, int idx, int* nowm, int ans[mx][25])
{
    static int p[25], vis[25] = {};
    if(idx > 2 && check(p, idx - 1) == 0)
        return; 
    if(idx == n)
    {
        for(int i = 0; i < n; i++)
        {
            ans[*nowm][i] = p[i];
        }
        *nowm = (*nowm) + 1;
        return;
    }
    for(int i = 0; i < n; i++)
    {
        if(i > 0 && a[i] == a[i - 1] && vis[i - 1] == 0)
            continue;
        if(!vis[i])
        {
            vis[i] = 1;
            p[idx] = a[i];
            permu(a, n, idx + 1,  nowm, ans);
            vis[i] = 0;
        }
    }
    return;
}
signed main()
{
    freopen("input.txt","r", stdin);
    int n;
    int ans[mx][25];
    int nowmval = 0;
    int* nowm = &nowmval;
    scanf("%lld", &n);
    //printf("%d", n);
    int a[n];
    //int ans[mx][25];
    for(int i = 0; i < n; i++)
    {
        scanf("%lld", &a[i]);
        //printf("%d", a[i]);
    }
    for(int i = 0; i < n; i++)
    {
        for(int j = i + 1; j < n; j++)
            if(a[j] < a[i])
                swap(a[j], a[i]);

    }
    permu(a, n, 0, nowm, ans);
    printf("%lld\n", *nowm);
    for(int i = 0; i < *nowm; i++)
        for(int j = 0; j < n; j++)
            printf("%lld%c", ans[i][j], " \n"[j == n - 1]);
    return 0;
}