#include <stdio.h>
#define swap(a, b) (a^=b^=a^=b)
int main()
{
    int a[10] = {9, 8, 6, 5, 4, 3, 3, 3, 2, 1};
                //0, 1, 2, 3, 4, 5, 6, 7, 8, 9
    int l = 1, r = 10, t = 2;
    while(l <  r)
    {
        int m = (l + r) >> 1;
        if(a[m] >= t)
            l = m + 1;
        else
            r = m;
        printf("%d %d\n", l, r);
    }
    printf("%d\n", r);
    int c = 2, b = 3;
    swap(b, c);
    printf("%d %d", c, b);
}