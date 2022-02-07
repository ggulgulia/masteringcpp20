#include <coroutine>
#include <iostream>

static unsigned ctr{1};

//coroutine's reutrn object
struct ReturnObject {
    struct promise_type {
        ReturnObject get_return_object() {
            std::cout << ctr++ <<". called promise_type::get_return_object\n";
            return ReturnObject{std::coroutine_handle<promise_type>::from_promise(*this)};
        }

        std::suspend_never initial_suspend() {
            std::cout << ctr++ <<". called promise_type::initial_suspend\n";
            return {};
        }

        std::suspend_always final_suspend() noexcept {
            std::cout << ctr++ <<". called promise_type::final_suspend\n";
            return {};
        }

        void unhandled_exception() {
            std::cout << ctr++ <<". called promise_type::unhandled_exception\n";
        }
    };
      
    std::coroutine_handle<> h_; 

    ReturnObject(std::coroutine_handle<promise_type> h):h_{h}{
        std::cout << ctr++ <<". called ReturnObject ctor\n";
    }

    //implicit conversion operator
    operator std::coroutine_handle<>() const { return h_; }
    };


//coroutine
ReturnObject foo(){
    std::cout << ctr++ << ". hello from coroutine\n";
    co_await std::suspend_always{};
    std::cout <<  ctr++ << ". hello from coroutine\n"; 
} 

//main
int main(){
    ReturnObject ro =  foo();
    std::cout << ctr++ << ". resuming coroutine from main\n";
    ro.h_(); //operator() same as resume
    std::cout << ctr++ << ". destroying coroutine from main\n";
    ro.h_.destroy();
    std::cout << ctr++ << ". end of main\n";
}