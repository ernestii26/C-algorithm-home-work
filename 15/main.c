#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define mx 1000005
#define max(a, b) (a > b ? a : b)
typedef struct node
{
    int v;
    struct node* prev;
}node;
typedef struct vector
{
    node *head, *tail;
    int size;
}vector;
node* newnode(int v)
{
    node* tmp = (node*)malloc(sizeof(node));
    tmp -> v = v;
    return tmp;
}
vector* push(vector* g, node* tmp)
{
    g -> size++;
    if(g -> size == 0)
    {
        g -> head = g -> tail = tmp;
        return g;
    }
    tmp -> prev = g -> tail;
    g -> tail = tmp;
    return g;
}
vector* pop(vector* g)
{
    g -> tail  = g -> tail -> prev;
    g -> size--;
    return g;
}
vector g[mx];
vector gt[mx];
vector r[mx];
int vis[mx], tout[mx];
int stamp = 0;
int rk[mx];
void dfs(int v)
{
    vis[v] = 1;
    node *tmp = g[v].tail;
    for(int i = 0; i < g[v].size; i++)
    {
        if(!vis[tmp -> v]) dfs(tmp -> v);
        tmp = tmp -> prev;
    }
    rk[stamp++] = v;
}
int color[mx], t = 1;
void dfs2(int v)
{
    vis[v] = 1;
    color[v] = t;
    node *tmp = gt[v].tail;
    for(int i = 0; i < gt[v].size; i++)
    {
        if(!vis[tmp -> v]) dfs2(tmp -> v);
        tmp = tmp -> prev;
    }
}
int deg[mx];
void dfs3(int v, int now)
{
    vis[v] = 1;
    node *tmp = r[v].tail;
    for(int i = 0; i < r[v].size; i++)
    {
        if(!vis[tmp -> v])
        {
            dfs3(tmp -> v, now);
        }
        tmp = tmp -> prev;
    }
}
node *q, *qtail;
int qsize = 0;
void pushq(int v)
{
    node* tmp = newnode(v);
    if(qsize == 0)
        qtail = tmp, q = tmp;
    else
        qtail -> prev = tmp, qtail = tmp;
    qsize++; 
}
node* popq()
{
    node* tmp = q;
    q = q -> prev;
    qsize--;
    return tmp;
}

int read() {
  int x = 0, w = 1;
  char ch = 0;
  while (ch < '0' || ch > '9') 
  {  
        if (ch == '-') w = -1;      
        ch = getchar();               
  }
  while (ch >= '0' && ch <= '9')
  {  
        x = x * 10 + (ch - '0');
        ch = getchar();  
  }
  return x * w;  
}

int main()
{
    int n, m, mode;
    n = read();
    m = read();
    mode = read();
    for(int i = 0; i < m; i++)
    {
        int u, v;
        u = read();
        v = read();
        push(&g[u], newnode(v));
        push(&gt[v], newnode(u));
    }
    for(int i = 1; i <= n; i++)
        if(!vis[i]) dfs(i);
    memset(vis, 0, sizeof(vis));
    int ans1 = 0;
    for(int i = stamp - 1; i > -1; i--)
    {
        if(!vis[rk[i]]) dfs2(rk[i]), ans1++, t++;
    }
    for(int i = 1; i <= n; i++)
    {
        node *tmp = g[i].tail;
        for(int j = 0; j < g[i].size; j++)
        {
            if(color[i] != color[tmp -> v])
                push(&r[color[i]], newnode(color[tmp -> v])), deg[color[tmp -> v]]++;
            tmp = tmp -> prev;
        }
    }
    pushq(color[rk[stamp - 1]]);
    while(qsize == 1)
    {
        node* vr = popq();
        node *tmp =  r[vr -> v].tail;
        for(int j = 0; j < r[vr -> v].size; j++)
        {
            deg[tmp -> v]--;
            if(deg[tmp -> v] == 0)
            {
                pushq(tmp -> v);
            }
            tmp = tmp -> prev;
        }
    }
    printf("%d\n", ans1);
    if(mode == 2)
        printf("%d\n", qsize == 0);
}