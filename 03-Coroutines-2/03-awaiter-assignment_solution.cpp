#include "ReturnObject.hpp"

int ctr{0};
class suspend_never{
    bool await_ready() {return !isSuspended;}
    void await_suspend(std::coroutine_handle<>){ }
    void await_resume(){}
};


ReturnObject DataAccessCoro(){
    std::cout  << ctr++ << ". Hello from DataAccessCoro\n";
    co_await Suspend{true};
    std::cout  << ctr++ << ". Hello again from DataAccessCoro\n";
}

int main(){
    std::coroutine_handle<ReturnObject::promise_type> handle =  DataAccessCoro();
    std::cout << ctr++ << ". From main, coroutine is suspended\n";
    handle();
}