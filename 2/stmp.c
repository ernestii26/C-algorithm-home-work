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
    head[i]->prev = cur[j]->prev;
    //printf("%d\n", cur[j]->data);
    free(cur[j]);    
    cur[j] = cur[i];
    cur[i] = head[i] = (node*)malloc(sizeof(node));
    len[j] += len[i];
    len[i] = 0;
}
//*
void merge(int i, int j)
{
    node* tmp;
    tmp = cur[i] -> prev;
    rmo(i);
    while(len[i] != 0 && len[j] != 0)
    {
        if(len[j] != 0)
        {
            tmp -> prev = cur[j] -> prev;
            tmp -> prev -> next = tmp;
            tmp = tmp -> prev;
            rmo(j);
        }
        if(len[i] != 0)
        {
            tmp -> prev = cur[i] -> prev;
            tmp -> prev -> next = tmp;
            tmp = tmp -> prev;
            rmo(i);
        }
    }
    if(len[j] != 0)
    {
        tmp -> prev = cur[j] -> prev;
        tmp -> prev -> next = tmp;
        tmp = tmp -> head[j];
        free(cur[j]);
    }
    
}
//*/

int main()
{
    freopen("input.txt", "r", stdin);
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
            cur[i] = cur[i]->prev;
            printf(" %d", cur[i]->data);
        }
        printf("\n");
    }
}