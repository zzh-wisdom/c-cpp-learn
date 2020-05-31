#include<iostream>
using namespace std;
int main()
{
    int a = 123;
    auto f = [a]()mutable { cout << ++a <<endl; }; // 不会报错
    cout << a << endl; // 输出：123
    ++a;
    f(); // 输出：124
    cout << a << endl; // 输出：124
}