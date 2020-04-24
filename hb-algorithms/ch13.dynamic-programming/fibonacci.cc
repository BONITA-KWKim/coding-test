#include <cstdio>
#include <cstdlib>
#include <cstring>

typedef unsigned long ULONG;

ULONG fibonacci(int);

ULONG fibonacci(int n) {
    if(0 == n || 1 == n) 
        return n;

    int i = 0;
    ULONG result = 0;
    ULONG *fibonacci_table;

    fibonacci_table = (ULONG *)malloc(sizeof(ULONG)*(n+1));

    fibonacci_table[0] = 0;
    fibonacci_table[1] = 1;

    for(i = 2; n >= i; ++i) {
        fibonacci_table[i] = fibonacci_table[i-1] + fibonacci_table[i-2];
    }

    result = fibonacci_table[n];

    free(fibonacci_table);

    return result;
}

int main(void) {
    int n = 46;
    ULONG result = fibonacci(n);

    printf("fibonacci(%d): %lu", n, result);

    return 0;
}