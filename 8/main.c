#include <stdio.h>
#include <stdlib.h>
typedef struct Node
{
    int data;
    struct Node *nxt;
}node;
int read() {
  int x = 0;
  char ch = 0;
  int w = 1;
  while (ch < '0' || ch > '9')
  {  
        if (ch == '-') w = -1;   
        ch = getchar();           
  }
  while (ch >= '0' && ch <= '9') 
  {  
        x = x * 10 + (ch - '0'); 
        ch = getchar();  
  }
  return w*x;
}
node* newnode()
{
    node *tmp = (node*)malloc(sizeof(node));
    tmp -> nxt = NULL;
    return tmp;
}
int main()
{
    int n, tmp;
    n = read();
    node **l = (node**)malloc(sizeof(node*) * (n + 1));
    for(int i = 1; i <= n; i++)
        l[i] = newnode();
    for(int i = 1; i <= n; i++)
    {
        l[i]->data = read();
        tmp = read();
        if(tmp != 0)
            l[i] -> nxt = l[tmp];
    }
    node *hare = l[1], *tortoise = l[1];
    while(hare != NULL)
    {
        printf("%d ", hare -> data);
        if(hare -> nxt == NULL)
            return 0;
        hare = hare->nxt->nxt;
        tortoise = tortoise -> nxt;
        if(hare == tortoise)
        {
            printf("%d ", hare -> data);
            return 0;
        }
    }

}