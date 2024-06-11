#include <stdio.h>
#include <string.h>
#define mx 5000006
char s[mx];
char c[mx];
int main()
{
    scanf("%s%s", s, c);
    int sl = strlen(s), cl = strlen(c);
    for(int i = 0; i < cl; i++)
    {
        if(sl - i < 0)
            printf("0\n");
        else
            printf("%d\n", (sl - i) * (i + 1));
    }
}