#include "ReturnObject.hpp"

static int ctr{1};

struct SuspendAlways{
    bool await_ready() const noexcept{
        std::cout << ctr++ << ". SuspendAlways::await_ready()\n";
        return false;
    }
    void await_suspend(std::coroutine_handle<> h) const noexcept{
        std::cout << ctr++ << ". SuspendAlways::await_suspend()\n";
    }
    void await_resume() const noexcept{
        std::cout << ctr++ << ". SuspendAlways::await_resume()\n";
    }
};

//coroutine
ReturnObject DataAccessCoro(){
    std::cout  << ctr++ << ". Hello from DataAccessCoro\n";
    co_await SuspendAlways{};
    std::cout  << ctr++ << ". Hello again from DataAccessCoro\n";
}


int main(){
    std::coroutine_handle<ReturnObject::promise_type> handle =  DataAccessCoro();
    std::cout << ctr++ << ". From main, coroutine is suspended\n";
    handle();
}