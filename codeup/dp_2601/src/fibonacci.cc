#include "fibonacci.hh"

int f[MAX_FIBONACCI_INPUT] = {0, 1, [2 ... (MAX_FIBONACCI_INPUT-1)] = -1};

int fibonacci(int n) {
	if (0 > n) {
		// error
		return -1;
	} else if (0 == n) {
		return f[0];
	} else if (1 == n) {
		return f[1];
	} else if (1 < n) {
		if (0 > f[n-1]) {
			f[n-1] = fibonacci(n-1);
		}
		f[n] = f[n-1] + f[n-2];

		return f[n];
	}
}
