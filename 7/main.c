#include <stdio.h>

int read() {
  int x = 0, w = 1;
  char ch = 0;
  while (ch < '0' || ch > '9') // ch 不是数字时
  {  
        if (ch == '-') w = -1;        // 判断是否为负
        ch = getchar();               // 继续读入
  }
  while (ch >= '0' && ch <= '9') // ch 是数字时
  {  
        x = x * 10 + (ch - '0');  // 将新读入的数字’加’在 x 的后面
        // x 是 int 类型，char 类型的 ch 和 ’0’ 会被自动转为其对应的
        // ASCII 码，相当于将 ch 转化为对应数字
        // 此处也可以使用 (x<<3)+(x<<1) 的写法来代替 x*10
        ch = getchar();  // 继续读入
  }
  return x * w;  // 数字 * 正负号 = 实际数值
}

int main()
{
    int l = 1, r, m, key, n, p = 1;
    //scanf("%d%d", &n, &key);
    n = read();
    key = read();
    int a[n+3];
    for(int i = 1; i <= n; i++)
    {
        a[i] = read();
    }
    r = n;
    printf("Searching %d in range [%d, %d].\n",key, l, r);
    while(l <= r)
    {
        m=(l+r) >> 1;
        if(a[m] == key)
        {
            p = 0;
            printf("Found at index %d.\n", m);
            break;
        }
        else if( a[m] > key)
            r = m - 1;
        else if(a[m] < key)
            l = m + 1;
        printf("Searching %d in range [%d, %d].\n",key, l, r);
    }
    if(p)
        printf("Not found.\n");
}