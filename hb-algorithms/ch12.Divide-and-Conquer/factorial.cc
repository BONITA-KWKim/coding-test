#include <iostream>

typedef unsigned long long ULONG;

ULONG factorial(int);

ULONG factorial(int n) {
    if(0 == n) return 1;
    else return n*factorial(n-1);
}

int main(void) {
    int n = 10;
    std::cout << n << "th factorial: " << factorial(n) << std::endl;
    
    return 0;
}