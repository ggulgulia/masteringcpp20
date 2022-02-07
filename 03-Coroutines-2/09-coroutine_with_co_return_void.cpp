#include "ReturnObject_co_return_void.hpp"



ReturnObject<int> return_coro(const std::string& msg){
    
    std::cout << "saying: " << msg  << " from return_coro\n";
    co_return ;

}

int main(){
    std::coroutine_handle<ReturnObject<int>::promise_type> handle =  return_coro("hello");
    std::cout << "from main, resuming coroutine\n";
    //handle();
    
}