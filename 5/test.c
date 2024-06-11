#include <stdio.h>
#include <stdlib.h>
#define mx 1000005
#define swap(a, b) (a^=b^=a^=b)

long long p[mx];
int rank[mx];//rank[i] i的rank
int who[mx];//i排名的label
int added[mx];
int len, add = 0;

long long *q[mx];
int op[mx], k[mx];
long long a[mx], b[mx];

long long read() {
  long long x = 0;
  char ch = 0;
  while (ch < '0' || ch > '9')
  {  
        ch = getchar();           
  }
  while (ch >= '0' && ch <= '9') 
  {  
        x = x * 10 + (ch - '0'); 
        ch = getchar();  
  }
  return x;
}

int readInt() {
  int x = 0;
  char ch = 0;
  while (ch < '0' || ch > '9')
  {  
        ch = getchar();           
  }
  while (ch >= '0' && ch <= '9') 
  {  
        x = x * 10 + (ch - '0'); 
        ch = getchar();  
  }
  return x;
}


void push(int i)//用到p之前都要push
{
    p[i] += (add - added[i]) * (len - rank[i]);
    added[i] = add;
}
void attack(int i)
{
    if(rank[i] == 1)
        return;
    int tmp = who[rank[i] - 1];
    push(i), push(tmp);
    k[i]++;
    q[i][k[i]] = q[i][k[i] - 1] + p[tmp] - p[i];
    p[i] = p[tmp];
    swap(rank[i], rank[tmp]);
    who[rank[i]] = i;who[rank[tmp]] = tmp;
}
void query(int i){
    int l = 1, r = len, ans = len + 1, t = i;
    while(l <= r)
    {
        int m = (l + r) >> 1;
        push(who[m]);
        if(p[who[m]] < t)
        {
            ans = m;
            r = m - 1;
        }
        else
            l = m + 1;
       // printf("%d %d\n", l, r);
    }
    //printf("!%d\n", ans);
    push(who[ans - 1]);
    if(ans != 1 && p[who[ans - 1]] >= i)
        printf("%d %d\n", ans - 1, who[ans - 1]);
    else
        printf("0 0\n");
    //printf("%d")
}

int last(int i, int j)
{
    //printf("%d %d %d\n",i, j, q[i][k[i] - 1]);
    if(j > k[i])
        j = k[i];
    printf("%lld\n", q[i][k[i]] - q[i][k[i] - j]);
}

signed main()
{
    int n, t, m;
    //scanf("%d%d%d", &n, &t, &m);
    n = readInt(), t = readInt(), m = readInt();
    len = n;
    for(int i = 1; i <= n; i++)
    {
        p[i] = read();
        rank[i] = i;who[i] = i;
    }
    for(int i = 0; i < t; i++)
    {
        op[i] = read();
        if(op[i] == 1)
        {
            a[i] = read();
            k[a[i]] += 1;
        }
        else if(op[i] == 3)
        {
            a[i] = read();
        }
        else if(op[i] == 4)
        {
            a[i] = read(), b[i] = read();
        }
    }
    for(int i = 1; i <= n; i++ )
        q[i] = (long long*)(malloc(sizeof(long long) * (k[i] + 1))), q[i][0] = 0, k[i] = 0;
    for(int i = 0; i < t; i++)
    {
        if(op[i] == 1)
            attack(a[i]);
        else if(op[i] == 2)
            add++;
        else if(op[i] == 3)
            query(a[i]);
        else
            last(a[i], b[i]);
    }
    printf("\n");
    for(int i = 1; i <= n; i++)
    {
        printf("%d ", k[i]);
        for(int j = 1; j <= k[i]; j++)
        {
            printf("%lld ", q[i][j] - q[i][j - 1]);
        }
        printf("\n");
    }
}

//## _ok

