#include <cstdio>

int fibonacci(int n) {
    if(0 == n || 1 == n) return n;
    else if (2 == n) return 1;

    return fibonacci(n-1) + fibonacci(n-2);
}

int main(void) {
    int n;
    scanf("%d", &n);

    printf("%d\n", fibonacci(n));

    return 0;
}