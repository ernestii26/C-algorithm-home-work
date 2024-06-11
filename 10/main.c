#include <stdio.h>
#include <stdlib.h>
#define mx 1000005
int read() {
  int x = 0;
  char ch = 0;
  while (ch < '0' || ch > '9')
  {  
        ch = getchar();           
  }
  while (ch >= '0' && ch <= '9') 
  {  
        x = x * 10 + (ch - '0'); 
        ch = getchar();  
  }
  return x;
}
typedef struct node
{
    int key;//pr
    int val;
    int deg;
    struct node* sib;//to right sibling
    struct node* child;//to left-most child
}node;
typedef struct heap
{
    node* head;
    int size;
}heap;
node* newnode()
{
    node* tmp = (node*)malloc(sizeof(node));
    tmp -> sib = NULL, tmp -> deg = 1;
    return tmp;
}
//heap printer[mx];
node* binomerge(heap* h1, heap* h2)
{
    node* x = h1 -> head;
    node* y = h2 -> head;
    node* h = newnode();
    node* cur = h;
    while(x != NULL && y != NULL)
    {
        if(y -> deg < x -> deg)
            cur -> sib = y, y = y -> sib, cur = cur -> sib;
        else
            cur -> sib = x, x = x -> sib, cur = cur -> sib;
    }
    if(x != NULL)
        cur -> sib = x, x = x -> sib, cur = cur -> sib;
    if(y != NULL)
        cur -> sib = y, y = y -> sib, cur = cur -> sib;
    cur = h -> sib;
    free(h);
    return cur;
}
heap* binounion(heap* h1, heap* h2)
{
    heap* h = (heap*)malloc(sizeof(heap));
    h -> size = h1 -> size + h2 -> size;
    h -> head = binomerge(h1, h2);
    if(h -> head == NULL)
        return h;
    node* prev = NULL;
    node* x = h -> head;
    node* nxt = x -> sib;
    while(nxt != NULL)
    {
        if(x -> deg != nxt -> deg || (nxt -> sib != NULL && nxt -> sib -> deg == x -> deg))
        {
            prev = x;
            x = nxt;
        }
        else
        {
            if(x -> key >= nxt -> key)
            {
                x -> sib  = nxt -> sib;
                nxt -> sib = x -> child;
                x -> child = nxt; 
                x -> deg += nxt -> deg;
            }
            else
            {
                if(prev == NULL)
                    h -> head = nxt;
                else
                {
                    prev -> sib = nxt;
                }
                x -> sib = nxt -> child;
                nxt -> child = x; 
                nxt -> deg += x -> deg;
                x = nxt;
            }
        }
        nxt = x -> sib;
    }
    return h;
}
node* reverse1(node* h)
{
    node* cur = h;
    node* prev = NULL;
    while(cur != NULL)
    {
        node* sib = cur -> sib;
        cur -> sib = prev;
        prev = cur;
        cur = sib;
    }
    h = prev;
    return h;
}
heap* binoinsert(heap* h, node* x)
{
    heap* hh = (heap*)malloc(sizeof(heap));
    hh -> head = x;
    hh -> size = 1;
    h = binounion(h, hh);
    return h;
}
void print(node* h)
{
    node* o = h;
    while(o != NULL)
        printf("%d ", o -> key), o = o -> sib;
    printf("\n");
    o = h;
    while(o != NULL)
        print(o -> child), o = o -> sib;
}
heap* binoremv(heap* h)
{ 
    
    node* tmp = h -> head;
    if(h -> size == 0)
    {
        printf("no documents in queue\n");
        return h;
    }
    int max = -1;
    while(tmp != NULL)
    {
        if(tmp -> key > max)
            max = tmp -> key;
        tmp = tmp -> sib;
    }
    tmp = h -> head;
    if(h -> head -> key == max)
        h -> head = h -> head -> sib;
    else
    {
        while(tmp -> sib -> key != max)
            tmp = tmp -> sib;
        node* tt = tmp -> sib;
        tmp -> sib = tmp -> sib -> sib;
        tmp = tt;
    }
    heap* hh = (heap*)malloc(sizeof(heap));
    hh -> head = reverse1(tmp -> child);
    h -> size -= 1;
    h = binounion(h, hh);
    printf("%d printed\n", tmp -> val);
    return h;
}
int main()
{
    int n, m;
    scanf("%d%d", &n, &m);
    heap* printer[n + 3];
    for(int i = 1; i <= n; i++)
        printer[i] = (heap*)malloc(sizeof(heap)), printer[i] -> head = NULL, printer[i] -> size = 0;
    while(m--)
    {
        int opt, a, b, c;
        opt = read();
        if(opt == 1)
        {
            a = read(), b = read(), c = read();
            node* tmp = newnode();
            tmp -> key = b, tmp -> val = a;
           
            printer[c] = binoinsert(printer[c], tmp);
            printf("%d jobs waiting on printer %d\n",printer[c] -> size, c);
        }
        else if(opt == 2)
        {
            a = read();
            printer[a] = binoremv(printer[a]);
        }
        else
        {
            a = read(), b = read();
            printer[b] = binounion(printer[a], printer[b]);
            printer[a] -> size = 0; printer[a] -> head = NULL;
            printf("%d jobs waiting on printer %d after moving\n",printer[b] -> size, b);
        }
    }
}