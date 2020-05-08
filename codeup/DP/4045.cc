#include <cstdio>
#include <cstdlib>

int main(void) {
    int N, M;
    scanf("%d %d", &N, &M);

    //int *room;
    //room = (int *)malloc(sizeof(int) * M);

    int result = 1;
    for(int i = 1; M > i; ++i) {
        int tmp = N - (i + 1);
        if(0 <= tmp) {
            result += (tmp / (i + 1));
            result += (tmp % (i + 1));
        }
        printf("%d: %d %d; rst: %d\n", tmp, (tmp / (i + 1)), (tmp % (i + 1)), result);
    }

    printf("%d\n", result);

    return 0;
}