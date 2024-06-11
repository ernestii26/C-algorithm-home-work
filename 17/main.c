#include <stdio.h>
#include <stdlib.h>
#define mx 1003
int *g[mx];
int dk[mx];
int time = 1;
int vis[mx];
int tin[mx], tout[mx], parent[mx];
void dfs(int u)
{
    tin[u] = time++;
    vis[u] = 1;
    for(int i = 0; i < dk[u]; i++)
    {
        if(!vis[g[u][i]])
            parent[g[u][i]] = u, dfs(g[u][i]);
    }
    tout[u] = time++; 
}
int main()
{
    int n;
    scanf("%d", &n);
    for(int i = 1; i <= n; i++)
    {
        scanf("%d", &dk[i]);
        g[i] = (int*)calloc(dk[i], sizeof(int));
        for(int j = 0; j < dk[i]; j++)
            scanf("%d", &g[i][j]);
    }
    for(int i = 1; i <= n; i++)
        if(!vis[i])
            dfs(i);
    for(int i = 1; i <= n; i++)
    {
        printf("%d ", i);
        for(int j = 0; j < dk[i]; j++)
        {
            //printf("%d ", F[i][j]);
            int tmp = g[i][j];
            if(tin[i] < tin[tmp] && tout[i] > tout[tmp] && parent[tmp] == i)
                printf("T");
            else if(tin[i] < tin[tmp] && tout[i] > tout[tmp])
                printf("F");
            else if(tin[i] > tin[tmp] && tout[i] < tout[tmp])
                printf("B");
            else
                printf("C");
        }
        printf("\n");
    }
}