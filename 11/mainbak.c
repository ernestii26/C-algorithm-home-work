#include <stdio.h>
#include <stdlib.h>
#define mx 1000005
#define max(a, b) (a > b ? a : b)
typedef struct node
{
    int val;
    int l;
    int id;
    struct node *nxt;
}node;
typedef struct queue
{
    node* head;
    node* tail;
    int size;
}queue;

int cur;
int parent[mx];
queue deep[mx];
queue dungeon[mx];
queue treasure;

node* newnode(int v, int l)
{
    node* tmp = (node*)malloc(sizeof(node));
    tmp -> nxt = NULL;
    tmp -> val = v;
    tmp -> l = l;
    return tmp;
}
node* front(queue* q)
{
    return q -> head;
}
void push(queue *q , node* tmp)
{
    if(q -> size == 0)
    {
        q -> head = q -> tail = tmp;
        q -> size += 1;
        return;
    }   
    q -> tail -> nxt = tmp;
    q -> tail  = tmp;
    q -> size += 1;
    return;
}
node* pop(queue *q)
{
    if(q -> size == 0)
        return NULL;
    node* v = q -> head;
    q -> head = q -> head -> nxt;
    q -> size -= 1;
    return v;
}

int dis[mx];
int dun[mx];
int pl, sumdis;//pl離0有多遠

void down()
{
    node* v = front(&dungeon[cur]);
    if(v == NULL)
    {
        printf("-1\n");
        return;
    }
    cur = v -> val;

    pl += 1;
    dis[pl] = dis[pl - 1] + v -> l;
    sumdis += v -> l;
    dun[pl] = cur;

    printf("%d\n", cur);
    return;
}
void up()
{
    if(cur == 0)
    {
        printf("-1\n");
        return;
    }
    node* tmp = pop(&dungeon[parent[cur]]);
    pl--;
    //printf("!%d\n", cur);
    sumdis -= tmp -> l;
    if(deep[parent[cur]].head -> val == cur)
        pop(&deep[parent[cur]]);
    cur = parent[cur];
    // int tmp = 0;
    // node* i = dungeon[cur].head;
    // while(i != NULL)
    // {
    //     //printf("!%d\n", i -> val);
    //     tmp  = max(tmp, deep[i -> val] + i -> l);
    //     i = i -> nxt;
    // }
    // deep[cur] = tmp;
    printf("%d\n", cur);
}

int plan(int t)
{
    int l = 0, r = pl;
    // printf("!%d\n", pl);
    // for(int i = 0; i <= pl; i++)
    // {
    //     printf("%d%c",sumdis - dis[i], " \n"[i == pl]);
    // }
    int ans = -1;
    while(l <= r)
    {
        int m = (l + r) >> 1;
        //printf("*%d\n", m);
        if((sumdis - dis[m]) > t)
        {
            ans = m;
            l = m + 1;
        }
        else
            r = m - 1;
    }
    ans++;
    //printf("#%d %d\n", ans, t);
    return ans;
}
void guess()
{
    // node* tmp = deep[cur].head;
    // printf("%d\n", tmp -> l);
    // for(int i = 0; i < deep[cur].size; i++)
    // {
    //     printf("%d%c", tmp -> l, " \n"[i == deep[cur].size - 1]);
    //     tmp = tmp -> nxt;
    // }
    printf("%d\n", deep[cur].head -> l);
}
int now;
int nnow[mx];
void discover(int v)
{
    nnow[cur] = now;
    int pv = plan(v);
    //printf("!%d %d\n", pv, dun[pv]);
    node* tmp = newnode(v - (sumdis - dis[pv]),pl + now);
    if(pv == 0)
        tmp -> id = -1;
    else
        tmp -> id = dun[pv - 1];
    push(&treasure, tmp);
    if(treasure.head -> l == now)
    {
        //printf("!%d\n", treasure.head -> l);
        tmp = pop(&treasure);
        if(tmp -> id != -1)
            printf("value lost at %d\n", tmp -> id);
        else
            printf("value remaining is %d\n", tmp -> val);
    }
    now++;
}
void initdeep(int t)
{
    if(dungeon[t].size == 0)
    {
        push(&deep[t], newnode(0, 0));
        return;
    }
    node* tmp = dungeon[t].head;
    for(int i = 0; i < dungeon[t].size; i++)
    {
        initdeep(tmp -> val);
        while(deep[t].size != 0 && deep[t].tail -> l < deep[tmp -> val].head -> l + tmp -> l)
            pop(&deep[t]);
        push(&deep[t], newnode(tmp -> val, deep[tmp -> val].head -> l + tmp -> l));
        //deep[t] = max(deep[t], deep[tmp -> val] + tmp -> l);
        tmp = tmp -> nxt;
    }
    push(&deep[t], newnode(0, 0));
}
int main()
{
    int n, m, q;
    scanf("%d%d%d", &n, &m, &q);
    for(int i = 0; i < n; i++)
        dungeon[i].size = 0, dungeon[i].head = NULL;
    for(int i = 0; i < m; i++)
    {
        int u, v, l;
        scanf("%d%d%d", &u, &v, &l);
        node* tmp = newnode(v, l);
        push(&dungeon[u], tmp);
        parent[v] = u;
    }
    initdeep(0);
    while(q--)
    {
        //printf("*%d\n", q);
        int opt;
        scanf("%d", &opt);
        //printf("%d\n", opt);
        if(opt == 1)
        {
            down();
            now--;
        }
        else if(opt == 2)
        {
            up();
            //now++;
        }
        else if(opt == 3)
        {
            int v;scanf("%d", &v);
            printf("%d\n", dun[plan(v)]);
        }
        else if(opt == 4)
        {
            guess();
        }
        else if(opt == 5)
        {
            int v;scanf("%d", &v);
            discover(v);
        }
        //*
        else if(opt == 6)
        {
            int v, l;scanf("%d%d",&v, &l);
            //deep[cur] = max(deep[cur], deep[v] + l);
            node* tmp = newnode(v, l);
            push(&dungeon[cur], tmp);
            parent[v] = cur;
            initdeep(v);
            while(deep[cur].size != 0 && deep[cur].tail -> l < deep[tmp -> val].head -> l + tmp -> l)
                pop(&deep[cur]);
            push(&deep[cur], newnode(tmp -> val, deep[tmp -> val].head -> l + tmp -> l));
            push(&deep[cur], newnode(0, 0));
        }
        //*/
    }
}