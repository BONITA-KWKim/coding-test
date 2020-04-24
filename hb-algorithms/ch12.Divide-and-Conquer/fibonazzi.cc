#include <iostream>

typedef unsigned long ULONG;

typedef struct tagMatrix2x2 {
    ULONG data[2][2];
} Matrix2x2;

int fibonazzi(int);
Matrix2x2 Matrix2x2_Power(Matrix2x2, int);
Matrix2x2 Matrix2x2_Muptiply(Matrix2x2, Matrix2x2);

int fibonazzi(int n) {
    Matrix2x2 A;

    /* init matrix */
    A.data[0][0] = 1; A.data[0][1] = 1;
    A.data[1][0] = 1; A.data[1][1] = 0;

    /* get ^n result */
    A = Matrix2x2_Power(A, n);

    return A.data[0][1];
}

Matrix2x2 Matrix2x2_Power(Matrix2x2 A, int n) {
    if(1 < n) {
        A = Matrix2x2_Power(A, n/2);
        A = Matrix2x2_Muptiply(A, A);

        if(1 & n) {
            Matrix2x2 B;

            B.data[0][0] = 1; B.data[0][1] = 1;
            B.data[1][0] = 1; B.data[1][1] = 0;

            A = Matrix2x2_Muptiply(A, B);
        }
    }

    return A;
}

Matrix2x2 Matrix2x2_Muptiply(Matrix2x2 A, Matrix2x2 B) {
    Matrix2x2 C;

    C.data[0][0] = A.data[0][0] * B.data[0][0] + A.data[0][1] * B.data[1][0];
    C.data[0][1] = A.data[0][0] * B.data[1][0] + A.data[0][1] * B.data[1][1];
    C.data[1][0] = A.data[1][0] * B.data[0][0] + A.data[1][1] * B.data[1][0];
    C.data[1][1] = A.data[1][0] * B.data[1][0] + A.data[1][1] * B.data[1][1];

    return C;
}


int main(void) {
    int n = 46;

    std::cout << n << "th fibonazzi value: " << fibonazzi(n) << std::endl;

    return 0;
}