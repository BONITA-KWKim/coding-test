#include <cstdio>

#define M 100
#define N 100

int map[M][N];

long long int num_path(int m, int n) {
    if(0 == map[m][n])
        return 0;
    if(0 == m && 0 == n) 
        return 1;

    return ((0 < m) ? num_path(m-1, n):0)+ ((0 < n) ? num_path(m, n-1):0);
}

int main(void) {
    int m, n, i, j;

    scanf("%d %d", &m, &n);
    for(i = 0; m > i; ++i) {
        for(j = 0; n > j; ++j) {
            scanf("%d", &map[i][j]);
        }
    }

    printf("%lld\n", num_path(m-1, n-1));

    return 0;
}