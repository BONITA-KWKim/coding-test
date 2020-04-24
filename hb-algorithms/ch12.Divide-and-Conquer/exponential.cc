#include <cstdio>
#include <cstdlib>

typedef unsigned long long ULONG;

ULONG power(int, int);

ULONG power(int base, int exp) {
    if(1 == exp) return base;
    else if (0 == base) return 1;

    if(0 == (exp%2)) {
        ULONG new_base = power(base, (exp/2));
        return new_base * new_base;
    } else {
        ULONG new_base = power(base, ((exp-1)/2));
        return new_base * new_base * base;
    }
}

int main(void) {
    int base = 2;
    int exponent = 30;
    printf("%d^%d=%llu\n", base, exponent, power(base, exponent));
    return 0;
}