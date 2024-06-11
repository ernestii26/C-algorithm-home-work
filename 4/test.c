#include <stdio.h>
#include <stdlib.h>
#define MAX 1e18 + 1
#define int long long

typedef struct node{
    struct node* nxt;
    struct node *prev;
    struct node* below;
    int val;
}node;

typedef struct list{
    int top;
    node* head[100];
}list;
list l;
node* newnode()
{
    node* i;
    i = (node*)malloc(sizeof(node));
    i -> nxt = NULL; i -> below = NULL;
    i -> val = MAX;
    return i;
}

int coinflip(int k, int i)
{
    int p = 1;
    for(int j = 0; j < i - 1; j++)
    {
        p*=2;
    }
    return k/p%2;
}

void slowget(int data)
{
    if(l.head[0] == NULL || l.head[0] -> nxt -> val < data)
    {
        printf("-1\n");
        return;
    }
    node *s = l.head[0] -> nxt;
    printf("%lld ", s -> val);
    while(s -> nxt != NULL && s -> nxt -> val >= data)
        s = s -> nxt, printf("%lld ", s -> val);
    printf("\n");
    return;
}

void fastget(int data)
{
    if(l.head[0] -> nxt == NULL || l.head[0] -> nxt -> val < data)
    {
        printf("-1\n");
        return;
    }
    node* s = l.head[l.top];
    for(int i = l.top; i > 0; i--)
    {
        if(s -> val != MAX)
            printf("%lld ", s -> val);
        while(s -> nxt != NULL && s -> nxt -> val >= data)
            s = s -> nxt, printf("%lld ", s -> val);
        s = s -> below;
    }
    if(s -> val != MAX)
        printf("%lld ", s -> val);
    while(s -> nxt != NULL && s -> nxt -> val >= data)
        s = s -> nxt, printf("%lld ", s -> val);
    printf("\n");
    return;
}
void link(node *a, node *b)
{
    if(b == NULL)
    {
        a -> nxt = NULL;
        return;
    }
    if(a -> nxt != NULL)
        a -> nxt -> prev = b;
    b -> nxt = a -> nxt;
    a -> nxt = b;
    b -> prev = a;
}
void insert(int data)
{
    node* s = l.head[l.top];
    node* update[100];
    for(int i = l.top;i > 0; i--)
    {
        while(s -> nxt != NULL && s -> nxt -> val >= data)
            s = s -> nxt;
        update[i] = s;
        s = s -> below;
    }
    while(s -> nxt != NULL && s -> nxt -> val >= data)
        s = s -> nxt;
    node* tmp = newnode();
    tmp -> val = data;
    link(s, tmp);
    int i = 1;
    node *abovetmp;
    while(coinflip(data, i))
    {
        if(i > (l.top))
        {
            l.top += 1;
            l.head[l.top] = newnode();
            l.head[l. top] -> below = l.head[l.top - 1];
            update[i] = l.head[l.top];
        }
        abovetmp = newnode();
        abovetmp -> val = data;
        abovetmp -> below = tmp;
        link(update[i], abovetmp);
        tmp = abovetmp; 
        i++;
    }
    return;
}
void init()
{
    l.top = 0;
    l.head[0] = newnode();
}
//*
void rem(int data)
{
    node* s = l.head[l.top];
    for(int i = l.top;i > 0; i--)
    {
        while(s -> nxt != NULL && s -> nxt -> val >= data)
            s = s -> nxt;
        if(s -> val == data)
            break;
        s = s -> below;
    }
    while(s -> nxt != NULL && s -> nxt -> val >= data)
        s = s -> nxt;
    while(s -> below != NULL)
    {
        link(s -> prev, s -> nxt);
        free(s);
        s = s -> below;
    }
    link(s -> prev, s -> nxt);
    while(l.top > 0 && l.head[l.top] -> nxt == NULL)
    {
        free(l.head[l.top]);
        l.top -= 1;
    }
}
signed main()
{
    int m;
    scanf("%lld", &m);
    int t, k;
    list l;
    init();
    while(m--)
    {
        scanf("%lld%lld", &t, &k);
        if(t == 3)
            insert(k);
        else if(t == 2)
            fastget(k);
        else if(t == 1)
            slowget(k);
        else
            rem(k);
    }
}
