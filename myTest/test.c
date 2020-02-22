#include<stdio.h>

int main() {
    int *a,*b;
    int x = 2, y = 3;
    a = &x;
    b = &y;
    printf("*a:%d *b:%d\n", *a, *b);
    return 0;
}