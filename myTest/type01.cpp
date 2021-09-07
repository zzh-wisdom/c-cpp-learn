#include <stdio.h>
#include<iostream>
using namespace std;

int main() {
	char c;
	unsigned char uc;
	unsigned short us;
	c = 128; // implicit conversion from 'int' to 'char' changes value from 128 to -128 [-Wconstant-conversion]
	uc = 128;
	us = c + uc;
	printf("0x%x\n", us);  // 0x0
	us = (unsigned char)c + uc;
	printf("0x%x\n", us); // 0x100
	us = c + (char)uc;
	printf("0x%x\n", us); //0xff00

    int i = 2147483648;
    unsigned int ui = 2147483648;
    printf("%lu %lu\n", sizeof(int), sizeof(unsigned int));
    long long int lli;
    lli = i + ui;
    printf("0x%llx\n", lli);
    lli = (unsigned int)i + ui;
    printf("0x%llx\n", lli);
    lli = i + (int)ui;
    printf("0x%llx\n", lli);

    printf("0x%x 0x%x\n", (unsigned int)i, (int)ui);
    i = 0xffff0000;
    ui = 0xffff0000;
    lli = i + ui;
    printf("0x%llx\n", lli);
    lli = (unsigned int)i + ui;
    printf("0x%llx\n", lli);
    lli = i + (int)ui;
    printf("0x%llx\n", lli);
    printf("0x%x 0x%x\n", (unsigned int)i, (int)ui);
    printf("0x%x 0x%x\n", (unsigned int)i, (int)ui);


    int a=-1;
    unsigned int b=2;
    printf("%d\n", a+b>a ? 1 : 0);
    printf("%d\n", a+b>b ? 1 : 0);
    printf("%x\n", a+b);
    printf("%d %d\n", a, b);
    printf("%u %u\n", a, b);

    a=-7;
    printf("%d\n", a+b);
    printf("%u\n", a+b);
    cout << a+b << endl;
    
    // 输出解释参考： <https://blog.csdn.net/weixin_34110749/article/details/93621087>
    cout << typeid(a+b).name() << endl;
    cout << typeid(a).name() << endl;
    cout << typeid(b).name() << endl;

	return 0;
}
