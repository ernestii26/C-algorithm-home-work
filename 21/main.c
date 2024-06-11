#include <stdio.h>
#include <stdlib.h>
#define int long long
typedef struct node
{
    int color, key, bh, h;
    struct node *lf, *rt, *p;
}node;
node* newnode(int color, int key)
{
    node *tmp = (node*)malloc(sizeof(node));
    tmp -> color = color;
    tmp -> key = key;
    tmp -> bh = 0;
    tmp -> h = 0;
    tmp -> lf = NULL;
    tmp -> rt = NULL;
    tmp -> p = NULL;
    return tmp;
}
node *root = NULL;
void insert(node* now, node *tmp)
{
    if(root == NULL)
    {
        root = tmp;
        return;
    }
    if(tmp -> key > now -> key)
    {
        if(now -> rt == NULL)
        {
            now -> rt = tmp, tmp -> p = now;
            // tmp -> bh = now -> bh + now -> color;
            // tmp -> h = now -> h + 1;
        }
        else
            insert(now -> rt, tmp);
    }
    else
    {
        if(now -> lf == NULL)
        {
            now -> lf = tmp, tmp -> p = now;
            // tmp -> bh = now -> bh + now -> color;
            // tmp -> h = now -> h + 1;
        }
        else
            insert(now -> lf, tmp);
    }
}
node *search(node *now, int x)
{
    // printf("%lld %lld\n", now -> key, x);
    if(now -> key == x)
        return now;
    if(x > now -> key)
        return search(now -> rt, x);
    return search(now -> lf, x);
}
void leftrotate(node *x)
{
    node* y = x -> rt;
    x -> rt = y -> lf;
    if(y -> lf != NULL)
        y -> lf -> p = x;
    y -> p = x -> p;
    if(x -> p == NULL)
        root = y;
    else if(x == x -> p -> lf)
        x -> p -> lf = y;
    else
        x -> p -> rt = y;
    y -> lf = x;
    x -> p = y;
}
int bh(node *now, int x)
{
    // printf("%lld %lld\n", now -> key, now -> color);
    if(now -> key == x)
        return 0;
    if(x > now -> key)
        return bh(now -> rt, x) + now -> color;
    return bh(now -> lf, x) + now -> color;
}
int h(node *now, int x)
{
    if(now -> key == x)
        return 0;
    if(x > now -> key)
        return h(now -> rt, x) + 1;
    return h(now -> lf, x) + 1;
}
void rightrotate(node *y)
{
    node *x = y -> lf;
    y -> lf = x -> rt;
    if(x -> rt != NULL)
        x -> rt -> p = y;
    x -> p = y -> p;
    if(y -> p == NULL)
        root = x;
    else if(y == y -> p -> lf)
        y -> p -> lf = x;
    else
        y -> p -> rt = x;
    x -> rt = y;
    y -> p = x;
}
signed main()
{
    int n;
    scanf("%lld", &n);
    // printf("%lld\n", n);
    
    for(int i = 0; i < n; i++)
    {
        char color[2];
        int key;
        scanf("%s%lld", color, &key);
        // printf("%s %lld\n", color, key);
        node *tmp = newnode((color[0] == 'B'), key);
        insert(root, tmp);
    }
    // printf("*%lld\n", root -> key);
    int m;
    scanf("%lld", &m);
    // printf("%lld\n", m);
    while(m--)
    {
        char c[2];
        int k;
        scanf("%s%lld", c, &k);
        // printf("%s\n", c);
        if(c[0] == 'L')
            leftrotate(search(root, k));
        else if(c[0] == 'R')
            rightrotate(search(root, k));
        else
        {
            // printf("%d\n", 1);
            node *tmp = search(root, k);
            // printf("%lld\n", bh(root, k));
            printf("%lld %lld %lld %lld\n",(tmp -> lf == NULL ? -1 : tmp -> lf -> key) ,(tmp -> rt == NULL ? -1 : tmp -> rt -> key), bh(root, k), h(root, k));
        }
    }
}