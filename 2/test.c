#include <stdio.h>
#include <stdlib.h>
#define mx 100005
typedef struct Node
{
    int data;
    struct Node* next;
    struct Node* prev;
}node;
node* head[mx];
node* cur[mx];
int len[mx];
void add(int i, int u)
{
    cur[i] -> data = u;
    cur[i] -> next = (node*)malloc(sizeof(node));
    node* pre = cur[i];
    cur[i] = cur[i]->next;
    cur[i]->prev = pre;
    len[i]++;
}
//*
void rmo(int i)
{
    len[i]--;
    cur[i] = cur[i]->prev;
    free(cur[i]->next);
}
void move(int i, int j)
{
    node* tmp = &head[i];
    for(int k = 0; k < len[i]; k++)
    {
        add(j, tmp->data);
        tmp = tmp->next;
        if(k != 0)
            free(tmp->prev);
    }
    len[i] = 0;
    cur[i] = &head[i];
}
//*
void merge(int i, int j)
{
    int tmp[mx], tmplen = 0;
    while(len[i] != 0 && len[j] != 0)
    {
        if(len[i] != 0)
        {
            tmp[tmplen] = cur[i]->prev->data;//a[i][len[i] - 1];
            rmo(i);
            tmplen++;
        }
        if(len[j] != 0)
        {
            tmp[tmplen] = cur[j]->prev->data;
            rmo(j);tmplen++;
        }
    }
    while(len[i] != 0)
    {
        tmp[tmplen] = cur[i]->prev->data;//a[i][len[i] - 1];
        rmo(i);
        tmplen++;
    }
    while(len[j] != 0)
    {
        tmp[tmplen] = cur[j]->prev->data;
        rmo(j);tmplen++;
    }
    for(int k = tmplen - 1; k > -1; k--)
    {
        add(j, tmp[k]);
    }
    len[i] = 0;
}
//*/

int main()
{
    freopen("input.txt", "r", stdin);
    for(int i = 0; i < mx; i++)
    {
        cur[i] = &head[i];
    }
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
    for(int i = 1; i <= n; i++)
    {
        printf("%d", len[i]);
        for(int j = len[i] - 1; j > -1; j--)
        {
            cur[i] = cur[i]->prev;
            printf(" %d", cur[i]->data);
        }
        printf("\n");
    }
}