#include <stdio.h>
#include <stdlib.h>
#define int long long

signed main(){
    int k, n, m, q;
    int d = 52;
    scanf("%lld%lld%lld%lld", &k, &n, &m, &q);
    char text[k + 1][n + 10];
    char pattern[k + 1][m + 10];
    int tindex[k + 1][n + 10];
    int pindex[k + 1][m + 10];
    for(int i = 0; i < k; i++){
        scanf("%s", text[i]);
    }
    for(int i = 0; i < k; i++){
        scanf("%s", pattern[i]);
    }
    int t[n + 6], p[m + 6];
    for(int i = 0; i <= n; i++){
        t[i] = 0;
    }
    for(int i = 0; i <= m; i++){
        p[i] = 0;
    }
    for(int i = 0; i < k; i++){
        for(int j = 0; j < n; j++){
            if(text[i][j] >= 97){
                tindex[i][j] = text[i][j] - 71;
            }else{
                tindex[i][j] = text[i][j] - 65;
            }
        }
        for(int j = 0; j < m; j++){
            if(pattern[i][j] >= 97){
                pindex[i][j] = pattern[i][j] - 71;
            }else{
                pindex[i][j] = pattern[i][j] - 65;
            }
        }
    }
    for(int i = 1; i <= n; i++){
        for(int j = 0; j < k; j++){
            t[i] = (((d % q) * (t[i] % q)) % q+ (tindex[j][i - 1] % q)) % q;
        }
    }
    for(int i = 1; i <= m; i++){
        for(int j = 0; j < k; j++){
            p[i] = (((d % q) * (p[i] % q)) % q + (pindex[j][i - 1] % q)) % q;
        }
    }
    int pi[m + 10];
    pi[1] = 0;
    int kk = 0;
    for(int i = 2; i <= m; i++){
        while(kk > 0 && p[k + 1] != p[i]){
            kk = pi[kk];
        }
        if(p[kk + 1] == p[i]){
            kk++;
        }
        pi[i] = kk;
    }
    int qq = 0;
    kk = 0;
    int index = 0;
    int answer[n + 10];
    int hind = 0;
    int hindex[n + 10];
    for(int i = 1; i <= n; i++){
        while(qq < n && qq > 0 && p[qq + 1] != t[i]){
            qq = pi[qq];
        }
        if(qq < n && p[qq + 1] == t[i]){
            qq++;
        }
        if(qq == m){
            int aaa = 0;
            int ff2 = 0;
            index++;
            answer[index] = i - m;
            qq = pi[qq];
            for(int p = 0; p < k; p++){
                for(int j = i - m; j < i; j++){
                    if(text[p][j] != pattern[p][ff2]){
                        hind++;
                        hindex[hind] = i - m;
                        aaa = 1;
                        break;
                    }
                    ff2++;
                    if(ff2 > m - 1){
                        break;
                    }
                }
                if(aaa == 1){
                    break;
                }
            }
        }
    }
    for(int i = 1; i <= n; i++){
        printf("%lld ", t[i]);
    }
    printf("\n");
    for(int i = 1; i <= m; i++){
        printf("%lld ", p[i]);
    }
    printf("\n");
    if(index == 0){
        printf("-1\n");
    }else{
        for(int i = 1; i <= index; i++){
            printf("%lld ", answer[i]);
        }
        printf("\n");
    }
    if(hind == 0){
        printf("-1\n");
    }else{
        for(int i = 1; i <= hind; i++){
            printf("%lld ", hindex[i]);
        }
        printf("\n");
    }
}