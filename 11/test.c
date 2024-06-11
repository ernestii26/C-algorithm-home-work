#include <stdio.h>
#include <stdlib.h>
#define int long long
#define mx 1000005
#define max(a, b) (a > b ? a : b)
typedef struct node
{
    int fi;
    int se;
    int th;
    struct node *nxt;
    struct node *prev;
}node;
typedef struct queue
{
    node* head;
    node* tail;
    int size;
}queue;

node* newnode(int v, int l, int th)
{
    node* tmp = (node*)malloc(sizeof(node));
    tmp -> nxt = NULL;
    tmp -> prev = NULL;
    tmp -> fi = v;tmp -> se = l;tmp -> th = th;
    return tmp;
}
void push(queue *q , node* tmp)
{
    if(q -> size == 0)
    {
        q -> head = q -> tail = tmp;
        q -> size += 1;
        return;
    }   
    tmp -> prev = q -> tail;
    q -> tail -> nxt = tmp;
    q -> tail  = tmp;
    q -> size += 1;
    return;
}
node* front(queue* q)
{
    return q -> head;
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
node* pop_back(queue *q)
{
    if(q -> size == 0)
        return NULL;
    node* v = q -> tail;
    q -> tail = q -> tail -> prev;
    q -> size -= 1;
    return v;
}
queue dungeon[mx];
int parent[mx];
int cur;
int deepnow;
int deepsum;
int deepl[mx];
int deepid[mx];
queue maxdeep[mx];
queue treasure;
void down()
{
    node* tmp = front(&dungeon[cur]);
    if(tmp == NULL)
    {
        printf("-1\n");
        return;
    }
    cur = tmp -> fi;
    deepnow++;
    deepsum += tmp -> se;
    deepl[deepnow] = deepl[deepnow - 1] + tmp -> se;
    deepid[deepnow] = cur;
    printf("%lld\n",cur);
}
void up()
{
    if(cur == 0)
    {
        printf("-1\n");
        return;
    }
    node* tmp;
    if(maxdeep[parent[cur]].head -> fi == cur)
        pop(&maxdeep[parent[cur]]);
    if(treasure.size != 0 &&  treasure.tail -> fi == deepnow)
    {
        tmp = pop_back(&treasure);
        if(treasure.size != 0 && treasure.tail -> fi >= deepnow)
            treasure.tail -> fi = deepnow - 1;
    }
    cur = parent[cur];
    tmp = pop(&dungeon[cur]);
    deepsum -= tmp -> se;
    deepnow--;
    printf("%lld\n", cur);
    time += 1;
}
int plan(int t)
{
    int l = 0, r = deepnow, ans = -1;
    while(l <= r)
    {
        int m = (l + r) >> 1;
        if(deepsum - deepl[m] > t)
        {
            ans = m;
            l = m + 1;
        }
        else
            r = m - 1;
    }
    return ans + 1;
}
int guess()
{
    printf("%lld\n", front(&maxdeep[cur]) -> se);
}
void initmax(int t)
{
    if(dungeon[t].size == 0)
    {
        push(&maxdeep[t], newnode(0, 0, 0));
        return;
    }
    node* tmp = front(&dungeon[t]);
    for(int i = 0; i < dungeon[t].size; i++)
    {
        initmax(tmp -> fi);
        while(maxdeep[t].size && maxdeep[t].tail -> se < maxdeep[tmp -> fi].head -> se + tmp -> se)
            pop_back(&maxdeep[t]);
        push(&maxdeep[t], newnode(tmp -> fi, maxdeep[tmp -> fi].head -> se + tmp -> se, 0));
        tmp = tmp -> nxt;
    }
    push(&maxdeep[t], newnode(0, 0, 0));
}

void discover(int v)
{
    node* tmp = front(&treasure);
    if(plan(v) != 0)
        tmp = newnode(deepnow , deepid[plan(v) - 1] , -1);
    else
        tmp = newnode(deepnow , v - deepsum, 0);
    push(&treasure, tmp);
    if(treasure.size > deepnow)
    {
        tmp = pop(&treasure);
        if(tmp -> th == -1)
            printf("value lost at %lld\n", tmp -> se);
        else
            printf("value remaining is %lld\n", tmp -> se);
    }
    return;
}
int main()
{
    int n, m, q;
    scanf("%lld%lld%lld", &n, &m, &q);
    for(int i = 0; i < n; i++)
        dungeon[i].size = 0, dungeon[i].head = NULL;
    for(int i = 0; i < m; i++)
    {
        int u, v, l;
        scanf("%lld%lld%lld", &u, &v, &l);
        node* tmp = newnode(v, l, 0);
        push(&dungeon[u], tmp);
        parent[v] = u;
    }
    initmax(0);
    while(q--)
    {
        //printf("*%d\n", q);
        int opt;
        scanf("%lld", &opt);
        if(opt == 1)
        {
            down();
        }
        else if(opt == 2)
        {
            up();
        }
        else if(opt == 3)
        {
            int v;scanf("%lld", &v);
            printf("%lld\n", deepid[plan(v)]);
        }
        else if(opt == 4)
        {
            guess();
        }
        else if(opt == 5)
        {
            int v;scanf("%lld", &v);
            discover(v);
        }
        else if(opt == 6)
        {
            int v, l;scanf("%lld%lld",&v, &l);
            //deep[cur] = max(deep[cur], deep[v] + l);
            node* tmp = newnode(v, l, 0);
            push(&dungeon[cur], tmp);
            parent[v] = cur;
            initmax(v);
            while(maxdeep[cur].size && maxdeep[cur].tail -> se < maxdeep[tmp -> fi].head -> se + tmp -> se)
                pop_back(&maxdeep[cur]);
            push(&maxdeep[cur], newnode(tmp -> fi, maxdeep[tmp -> fi].head -> se + tmp -> se, 0));
            push(&maxdeep[cur], newnode(0, 0, 0));
        }
    }
}