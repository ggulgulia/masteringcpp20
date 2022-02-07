#include  "ReturnObject.hpp"

static int ctr{1};

class SuspendAlways{
    public:
        constexpr bool await_ready(){
            std::cout << "await_ready\n";
            return false;
        }
        
        constexpr void await_suspend(std::coroutine_handle<> h) const noexcept {
        }
        
        constexpr void await_resume() const noexcept {
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
    std::cout << ctr++ << ". from main, coroutine is currently suspended\n";
    handle();
}