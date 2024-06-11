#include <stdio.h>
#include <stdbool.h>

#define MAX_LEN 1000005
#define D 52
#define ll long long

ll DPower[MAX_LEN];

void buildPowerArr(int q, int k)
{
    DPower[0] = 1;
    for (int i = 1; i < k; i++)
    {
        DPower[i] = (DPower[i - 1] * (ll)D) % (ll)q;
    }
    
}


void rabinKarp(int numRows, int numCols, char arr[][numCols + 1], ll sum[], int q)
{
    for (int c = 0; c < numCols; c++)
    {
        ll s = 0;
        for (int r = 0; r < numRows; r++)
        {
            // printf("r: %d, c: %d\n", r, c);
            // printf("%c: %d\n", arr[r][c], arr[r][c]);
            if (arr[r][c] <= 'Z')
            {
                s += (DPower[numRows - 1 - r] * ((ll)(arr[r][c] - 'A') % q)) % q;
                // printf("1. %lld.\n", DPower[numRows - 1 - r] * ((ll)(arr[r][c] - 'A') % q) % q);
            }   
            else
            {
                s += (DPower[numRows - 1 - r] * ((ll)(arr[r][c] - 'A' - 6) % q)) % q;
                // printf("2. %lld.\n", (DPower[numRows - 1 - r] * ((ll)(arr[r][c] - 'A' - 6) % q)) % q);
            }
        }


        sum[c] = s;
    }



}

void printSumArr(int size, ll sum[])
{
    for (int i = 0; i < size; i++)
        printf("%lld ", sum[i]);
    printf("\n");
    // printf("print end\n");
}

void printStrings(int numStrs, int len, char strs[][len + 1])
{
    for (int i = 0; i < numStrs; i++)
        printf("%s\n", strs[i]);
}

void printPower(int k)
{
    for (int i = 0; i < k; i++)
        printf("%lld ", DPower[i]);
    printf("\n");
}


int pi[MAX_LEN] = {0};

void computePrefix(ll P2[], int pi[], int m)
{
    pi[0] = 0;
    int k = 0;
    for (int q = 2; q <= m; q++)
    {
        while (k > 0 && P2[k] != P2[q - 1])
            k = pi[k - 1];
        if (P2[k] == P2[q - 1])
            k++;
        pi[q - 1] = k;
    }

}

void printPrefix(int m)
{
    for (int i = 0; i < m; i++)
        printf("%d ", pi[i]);
    printf("\n");
}

void KMPMatch(ll T2[], ll P2[], int n, int m, int possibleAns[], int* hitCount)
{
    int q = 0;
    int k = 0;

    for (int i = 1; i <= n; i++)
    {
        // printf("i: %d, q: %d\n", i, q);
        while (q > 0 && P2[q] != T2[i - 1])
        {
            // printf("i: %d, q: %d\n", i, q);
            q = pi[q - 1];
        }

        if (P2[q] == T2[i - 1])
            q++;

        if (q == m)
        {
            possibleAns[*hitCount] = i - m;   
            // printf("possibleAns[%d]: %d\n", *hitCount, possibleAns[*hitCount]);
            *hitCount = *hitCount + 1;
            q = pi[q - 1];
            
        }

    }



}

int main()
{
    int k = 0, n = 0, m = 0;
    ll q;
    scanf("%d%d%d%lld", &k, &n, &m, &q);

    char T[k][n + 1];
    char P[k][m + 1];

    ll T2[n];
    ll P2[m];

    for (int i = 0; i < k; i++)
    {
        scanf("%s\n", T[i]);
    }

    for (int i = 0; i < k; i++)
    {
        scanf("%s\n", P[i]);
    }

    buildPowerArr(q, k);
    // printStrings(k, n, T);

    rabinKarp(k, n, T, T2, q);
    rabinKarp(k, m, P, P2, q);

    // printf("----------\n");
    printSumArr(n, T2);
    printSumArr(m, P2);

    computePrefix(P2, pi, m);
    // printf("prefix:\n");
    // printPrefix(m);
    // printf("----------\n");



    static int possibleAns[MAX_LEN];
    int hitCount = 0;
    // printf("fuck tsai");
    KMPMatch(T2, P2, n, m, possibleAns, &hitCount);

    if (hitCount == 0)
        printf("-1");
    else
        for (int i = 0; i < hitCount; i++)
            printf("%d ", possibleAns[i]);

    printf("\n");




    q = 1000000009;



    buildPowerArr(q, k);
    rabinKarp(k, n, T, T2, q);
    rabinKarp(k, m, P, P2, q);

    // printf("----------\n");

    computePrefix(P2, pi, m);
    int hitCount2 = 0;
    static int possibleAns2[MAX_LEN];
    KMPMatch(T2, P2, n, m, possibleAns2, &hitCount2);

    int sHitShift[MAX_LEN];
    int sHitSize = 0;
    int idx1 = 0, idx2 = 0;
    // printf("hitCount: %d, hitCount2: %d\n", hitCount, hitCount2);
    // printf("%d %d\n", possibleAns[0], possibleAns2[0]);



    while (idx1 < hitCount && idx2 < hitCount2)
    {
        if (possibleAns[idx1] == possibleAns2[idx2])
        {
            idx1++;
            idx2++;
        }
        else if (possibleAns[idx1] < possibleAns2[idx2])
        {
            sHitShift[sHitSize++] = possibleAns[idx1];
            idx1++;
        }
        else
            idx2++;
    }

    while (idx1 < hitCount)
    {
        sHitShift[sHitSize] = possibleAns[idx1];
        sHitSize++;
        idx1++;
    }

    if (sHitSize == 0)
        printf("-1");
    else
        for (int i = 0; i < sHitSize; i++)
            printf("%d ", sHitShift[i]);

    printf("\n");

    return 0;
}