#include <iostream> 
#include <thread> 
using namespace std;  

void th_function()  
{  
    std::cout << "hello thread." << std::endl;  
}  

int main(int argc, char *argv[])  
{
    std::thread t(th_function);  
    t.join();  
    return 0;  
}