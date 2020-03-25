#ifndef __STACK_HH__
#define __STACK_HH__

#include <iostream>

template<class T>
class ListElement {
public:
    ListElement(){}
    ~ListElement(){}
    
    void test();
private:
    ListElement *next;
    T data;
};

#endif //__STACK_HH__
