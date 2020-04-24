#include <iostream>
#include <algorithm>

struct student {
    int no;
    int marks;
    int grade;
};

bool cmp(const struct student &p1, const struct student &p2){
    return (p1.marks > p2.marks);
}

bool cmp_no(const struct student &p1, const struct student &p2){
    return (p1.no < p2.no);
}

int main(void) {
    int i = 0;
    int student_no = 0;    
    std::cin >> student_no;

    struct student students[student_no];
    for(i = 0; student_no > i; ++i) {
        students[i].no = i;
        std::cin >> students[i].marks;
    }

    std::sort(students, students+student_no, cmp);

    for(i = 0; student_no > i; ++i) {
        students[i].grade = (i + 1);

        for(int j = i; 0 < j; --j) {
            if(students[j-1].marks == students[j].marks) {
                students[i].grade = students[j-1].grade;
            } else {
                break;
            }
        }
    }

    std::sort(students, students+student_no, cmp_no);

    for(i = 0; student_no > i; ++i) {
        std::cout << students[i].marks << " " << students[i].grade << std::endl;
    }
    return 0;
}
