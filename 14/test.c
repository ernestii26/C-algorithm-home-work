#include <stdio.h>
#define int long long 
int val(char c)
{
    if(c < 96)
    {
        return c - 'A';
    }
    else
        return c - 'a' + 26;
}
signed main()
{
    int k, n, m, q, d = 1;
    scanf("%lld%lld%lld%lld", &k, &n, &m, &q);
    char t[k + 5][n + 5];
    char p[k + 5][m + 5];
    int tt[n + 5];
    int pp[n + 5];
    for(int i = 0; i < n + 5; i++)
        tt[i] = pp[i] = 0;
    for(int i = 1; i <= k; i++)
    {
        scanf("%s", t[i]);
    }
    for(int i = 1; i <= k; i++)
    {
        scanf("%s", p[i]);
    }
    for(int i = k; i > 0; i--)
    {
        for(int j = 0; j < n; j++)
        {
            //printf("%c%d\n",t[i][j], val(t[i][j]));
            tt[j + 1] =(tt[j + 1] + val(t[i][j]) * d % q) % q;
        }
        for(int j = 0; j < m; j++)
            pp[j + 1] =(pp[j + 1] + val(p[i][j]) * d % q) % q;
        d = d * 52 % q;
    }
    for(int i = 1; i <= n; i++)
        printf("%lld%c", tt[i], " \n"[i == n]);
    for(int i = 1; i <= m; i++)
        printf("%lld%c", pp[i], " \n"[i == m]);
    int f[m + 3];
    f[0] = -1, f[1] = 0;
    for(int i = 2; i <= m; i++)
    {
        int w = f[i - 1];
        while(w >= 0 && pp[i] != pp[w + 1])
            w = f[w];
        f[i] = w + 1;
    }
    // for(int i = 1; i <= m; i++)
    //     printf("%d%c", f[i], " \n"[i == m]);
    int w = 0;
    int v = 0, s = 0;
    int vs[n], sp[n];
    for(int i = 1; i <= n; i++)
    {
        while(w >= 0 && pp[w + 1] != tt[i])
            w = f[w];
        w += 1;
        if(w == m)
        {
            int ju = 1;
            for(int j = 1; j <= k; j++)
                for(int l = 0; l < m; l++)
                {
                    //printf("%c %c\n", t[j][l + i - m], p[j][l]);
                    if(t[j][l + i - m] != p[j][l])
                        ju = 0;
                }
            //printf("!%d\n", ju);
            vs[v++] = i - m;
            if(!ju)
                sp[s++] = i - m;
            w = f[w];
        }
    }
    if(v == 0)
        printf("-1\n");
    else
    {
        for(int i = 0; i < v; i++)
            printf("%lld%c", vs[i], " \n"[i == v - 1]);
    }
    if(s == 0)
        printf("-1\n");
    else
    {
        for(int i = 0; i < s; i++)
            printf("%lld%c", sp[i], " \n"[i == s - 1]);
    }
}