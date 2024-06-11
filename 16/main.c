#include <stdio.h>
#include <string.h>
#define mx 5000006
char s[mx],  c[mx];int f[mx], t[mx], o[mx];
signed main()
{
    scanf("%s%s", &s[1], &c[1]);
    c[0] = '$', s[0] = '$';
    int cl = strlen(c) - 1, sl = strlen(s) - 1;
    f[0] = -1, f[1] = 0;
    for(int i = 2; i <= cl; i++)
    {
        int w = f[i - 1];
        while(w >= 0 && c[w + 1] != c[i])
            w = f[w]; 
        f[i] = w + 1;
    }
    int w = 0;
    for(int i = 1; i <= sl; i++)
    {
        while(w >= 0 && c[w + 1] != s[i])
            w = f[w];
        w += 1;
        t[w] += 1;
        if(w == cl)
            w = f[w];
    }
    o[0] = 0;
    for(int i = 1; i <= cl; i++)
        o[i] = o[f[i]] + 1;
    for(int i = cl; i >= 1; i--)
        t[f[i]] += t[i];
    for(int i = 1; i <= cl; i++)
            printf("%lld\n", o[i] * t[i]);
}