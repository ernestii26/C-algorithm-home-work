#include <stdio.h>
#define mx 200005
typedef struct node
{
    int val;
    struct node *prev, *nxt; 
}node;
node* head[mx];
node* cur[mx];
int len[mx];
void add(int i, int u)
{
    cur[i] = (node*)malloc(sizeof(node));
    cur[i]->val = u;
    if(len[i] == 0)
        head[i] = cur[i]->prev = cur[i];
    cur[i] = cur[i]->nxt;len[i]++;
}
void rmo(int i)
{
    cur[i] = cur[i]->prev;
    free(cur[i]->nxt);
}

int main()
{
    //freopen("input.txt", "r", stdin);
    int n, m;
    scanf("%d%d", &n, &m);
    while(m--)
    {
        int f;
        scanf("%d", &f);
        if(f == 1)
        {
            int i, u;
            scanf("%d%d", &i, &u);
            add(i, u);
            //printf("*%d\n", len[i]);
        }
        else if(f == 2)
        {
            int i;
            scanf("%d", &i);
            rmo(i);
        }
        else if(f == 3)
        {
            int i, j;
            scanf("%d%d", &i, &j);
            move(i, j);
        }
        else
        {
            int i, j;
            scanf("%d%d", &i, &j);
            merge(i, j);
        }
    }

}