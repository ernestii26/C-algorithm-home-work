#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define int long long
int rank(char c)
{
    if(c == '(')
        return -1;
    if(c == '+' || c == '-')
        return 1;
    return 5;
}
typedef struct node
{
    int val;
    struct node* nxt;
}node;
node* head;
int size = 0;
void push(int val)
{
    node* new = (node*)malloc(sizeof(node));
    new -> val = val;
    new -> nxt = head;
    head = new;
    size++;
}
void pop()
{
    if(size == 0)
        return;
    node* prev = head;
    head = head -> nxt;
    free(prev);
    size--;
}
int post[4500], ps = 0;
int w[4500];
void intopo(char c[4500], char t[4500])
{
    int lc = strlen(c);
    for(int i = 0; i < lc; i++)
    {
        int tmp = 0, k = 0;
        while(c[i] - '0' >= 0 && c[i] - '0' < 10 && i < lc)
            k = 1, tmp = tmp * 10 + (c[i] - '0'), i++;//printf("%c", c[i]);
        if(k)
            w[ps] = 1, post[ps++] = tmp;
        //printf("%c %lld\n", c[i], i);
        if(i < lc){
            if(c[i] == '(')
                push(c[i]);
            else if(c[i] == ')')
            {
                while(size != 0 && head -> val != '(')
                    post[ps++] = head -> val, pop();//printf("%c", s[size - 1]), size--;
                pop();
            }
            else
            {
                while(size != 0 && rank(head -> val) >= rank(c[i]))
                    post[ps++] = head -> val, pop();//printf("%c", s[size - 1]), size--;
                push(c[i]);
            }
        }
    }
    while(size != 0)
        post[ps++] = head -> val, pop();//printf("%c", s[size - 1]), size--;
}
int eval()
{
    for(int i = 0; i < ps; i++)
    {
        if(w[i])
            push(post[i]);
        else
        {
            int n2 = head -> val;
            pop();
            int n1 = head -> val;
            pop();
            //printf("%d %d\n", n1, n2);
            switch(post[i])
            {
                case '+':
                    push(n1 + n2);
                    break;
                case '-':
                    push(n1 - n2);
                    break;
                case '*':
                    push(n1 * n2);
                    break;
                case '/':
                    push(n1 / n2);
                    break;
                case '%':
                    push(n1 % n2);
                    break;
            }
        }
    }
    return head -> val;
}
signed main()
{
    int ti = 3;
    while(ti--)
    {

        node now;
        head = &now;
        char c[4500], t[4500];
        size = 0;
        memset(w, 0, sizeof(w));
        ps = 0;
        scanf("%s", c),intopo(c, t);
        //*
        //printf("%lld\n", ps);
        for(int i = 0; i < ps; i++)
        {
            if(w[i])
                printf("%lld", post[i]);
            else
                printf("%c", (char)post[i]); 
        }
        //*/
        printf("=%lld\n",eval());
        pop();
    }
}