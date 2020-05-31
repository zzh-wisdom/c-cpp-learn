#include<iostream>
using namespace std;

void print_num(int x) {
    cout<<x<<endl;
}
int main(){
    int m = [](int x) { return [](int y) { return y * 2; }(x)+6; }(5);
    std::cout << "m:" << m << std::endl;            //输出m:16

    std::cout << "n:" << [](int x, int y) { return x + y; }(5, 4) << std::endl;            //输出n:9
    
    auto gFunc = [](int x) -> function<int(int)> { return [=](int y) { return x + y; }; };//还可以返回表达式
    auto lFunc = gFunc(4);
    std::cout << lFunc(5) << std::endl; //输出：9

    auto hFunc = [](const function<int(int)>& f, int z) { return f(z) + 1; };
    auto re = hFunc(gFunc(7), 8);
    cout << re << endl;  //输出 16

    int a = 111, b = 222;
    auto func = [=, &b]()mutable { a = 22; b = 333; std::cout << "a:" << a << " b:" << b << std::endl; };
    func(); // a:22 b:333
    std::cout << "a:" << a << " b:" << b << std::endl;// a:111 b:333
    
    a = 333;
    auto func2 = [=, &a] { a = 444; std::cout << "a:" << a << " b:" << b << std::endl; };
    func2();// a:444 b:333

    auto func3 = [](int x) ->function<int(int)> { return [=](int y) { return x + y; }; };
    std::function<void(int x)> f_display_42 = [&](int x) {print_num(func3(x)(-2)); };
    f_display_42(44);
}