#include<iostream>
using namespace std;

class A{
    public:
    int level;
    char *ptr;
};

class B{
    public:
    char *p;
    int last;
    A array[2];
};

int main() {
    B* b = new B;
    cout << b<<endl;
    printf("b->p:%p\nb->last:%d\nb->array[0].level:%d\nb->array[0].ptr:%p\n", b->p,b->last,b->array[0].level,b->array[0].ptr);
    return 0;
}