#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

struct machine {
    int id;
    int gas;
};

bool asc(struct machine &a, struct machine &b) {
    return a.id < b.id;
}

int main(void) {
    int i = 0;
    int machine_no = 0;
    std::cin >> machine_no;

    struct machine machines[machine_no];
    memset(machines, 0x00, sizeof(struct machine) * machine_no);

    for(i = 0; machine_no > i; ++i) {
        std::cin >> machines[i].id >> machines[i].gas;
    }

    std::sort(machines, machines+machine_no, asc);

    for(i = 0; machine_no > i; ++i)
        std::cout << machines[i].id << " " << machines[i].gas << std::endl;

    return 0;
}
