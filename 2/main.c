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
    cur[i] -> next = (node*)malloc(sizeof(node));
    node* pre = cur[i];
    cur[i] = cur[i]->next;
    cur[i] -> data = u;
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
    if(len[i] == 0)
        return;
    cur[j]->next = head[i] -> next;
    head[i]->next->prev = cur[j];
    //cur[j]->next = head[i]

    cur[j] = cur[i];
    cur[i] = head[i];
    //cur[i] = head[i] = (node*)malloc(sizeof(node));
    len[j] += len[i];
    len[i] = 0;
}
//*
void merge(int i, int j)
{
    //printf("%d %d\n", len[i], len[j]);
    int tmplen = len[i] + len[j];
    node *tmp = (node*)malloc(sizeof(node));
    node *ttmp = tmp;
    while(len[i] != 0 && len[j] != 0)
    {
        if(len[i] != 0)
        {
            tmp->prev = cur[i];
            cur[i]->next = tmp;
            len[i]--;
            cur[i] = cur[i]->prev;
            tmp = tmp->prev;
        }
        if(len[j] != 0)
        {
            tmp->prev = cur[j];
            cur[j]->next = tmp;
            len[j]--;
            cur[j] = cur[j]->prev;
            tmp = tmp->prev;
        }
    }
    //printf("%d %d\n", tmp->data, cur[j]->data);
    //printf("%d", len[i]);
    if(len[j] != 0)
    {
        tmp->prev = cur[j];
        cur[j]->next = tmp;
        //tmp = tmp->prev;
    }
    if(len[i] != 0)
    {
        tmp->prev = cur[i];
        cur[i]->next = tmp;
        //tmp = tmp->prev;
        head[j] = head[i];
        head[i] = (node*)malloc(sizeof(node));
    }
    cur[j] = ttmp->prev;
    len[i] = 0;
    len[j] = tmplen;
    cur[i] = head[i];
}
//*/

int main()
{
    //freopen("input.txt", "r", stdin);
    for(int i = 0; i < mx; i++)
    {
        cur[i] -> prev = cur[i] = head[i] =(node*)malloc(sizeof(node));
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
            printf(" %d", cur[i]->data);
            cur[i] = cur[i]->prev;
        }
        printf("\n");
    }
}