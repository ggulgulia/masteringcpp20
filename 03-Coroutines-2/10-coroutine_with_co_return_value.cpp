#include "ReturnObject_co_return_value.hpp"



ReturnObject<int> return_coro(const std::string& msg){
    
    std::cout << "saying: " << msg  << " from return_coro\n";
    co_await std::suspend_always{};
    co_yield 9;
    co_return 44;

}

int main(){
    std::coroutine_handle<ReturnObject<int>::promise_type> handle =  return_coro("hello");
    std::cout << "from main, resuming coroutine\n";
    handle();
    std::cout << handle.promise().get_value() << "\n";
   
    std::cout << handle() << "\n";
    //handle();
    
}