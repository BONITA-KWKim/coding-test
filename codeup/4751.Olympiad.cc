#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

struct participant {
    int nation_no;
    int no;
    int marks;
};

bool desc(struct participant &x, struct participant &y) {
    return x.marks > y.marks;
}

int main(void) {
    int i = 0;
    int max_entry_count = 0;
    int max_nation_no = 0;
    std::cin >> max_entry_count;

    if(3 > max_entry_count || 100 < max_entry_count) {
        return -1;
    }

    struct participant entry[max_entry_count];
    memset(entry, 0x00, sizeof(struct participant) * max_entry_count);

    for(i = 0; max_entry_count > i; ++i) {
        std::cin >> entry[i].nation_no >> entry[i].no >> entry[i].marks;

        if(max_nation_no < entry[i].nation_no) 
            max_nation_no = entry[i].nation_no;
    }

    int medal_counts[max_nation_no];
    memset(medal_counts, 0x00, sizeof(int) * max_nation_no);

    std::sort(entry, entry+max_entry_count, desc);
    /*
    for (int idx = 0; max_entry_count > idx; ++idx) {
        std::cout << entry[idx].nation_no << " " << entry[idx].no << " " << entry[idx].marks << std::endl;
    }
    */
    int count = 0;
    for(i =0; max_entry_count > i; ++i) {
        int nation_index = entry[i].nation_no-1;
        if(2 > medal_counts[nation_index]) {
            std::cout << entry[i].nation_no << " " << entry[i].no << std::endl;
            ++(medal_counts[nation_index]);
            ++count;
        }

        if(count > 2) break;
    }

    return 0;
}
