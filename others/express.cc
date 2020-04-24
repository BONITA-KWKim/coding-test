#include <iostream>
#include <cstring>

int main(void) {
    int city_count = 0;
    int truck_cap = 0;

    std::cin >> city_count >> truck_cap;

    int invoice_count = 0;

    std::cin >> invoice_count;

    int (*invoice)[invoice_count] = NULL;
    invoice = (int (*)[invoice_count])malloc(invoice_count*sizeof(int)*3);
    memset(invoice, 0x00, invoice_count * sizeof(int)*3);
    for(int i = 0; invoice_count > i; ++i) {
        std::cin >> (*invoice+i)[0] >> (*invoice+i)[1] >> (*invoice+i)[2];
    }
}