// promise example
#include <iostream>       // std::cout
#include <functional>     // std::ref
#include <thread>         // std::thread
#include <future>         // std::promise, std::future

void print_int (std::future<int>& fut) {
    for(int i=0;i<1;i++) { //获取超过一次也会报错
        int x = fut.get();
        std::cout << "value: " << x << '\n';
    }
}

int main ()
{
  std::promise<int> prom;                      // create promise

  std::future<int> fut = prom.get_future();    // engagement with future

  std::thread th1 (print_int, std::ref(fut));  // send future to new thread

  prom.set_value (10);                         // fulfill promise
                                               // (synchronizes with getting the future)
    //prom.set_value (10);  //future_error: The state of the promise has already been set.
    //prom.set_value (2); 
  th1.join();
  return 0;
}
