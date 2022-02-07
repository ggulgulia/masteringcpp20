#include <concepts>
#include <coroutine>
#include <exception>
#include <iostream>

int ctr{0};

struct suspend_always{
    bool await_ready() {return false;}
    void await_suspend(std::coroutine_handle<>){}
    void await_resume(){}
};

//same as in section 5
struct ReturnObject {
        struct promise_type {
            unsigned value_{0};
            ReturnObject get_return_object() {
                return {std::coroutine_handle<promise_type>::from_promise(*this)}; 
            }
        std::suspend_never initial_suspend() { return {}; }
        std::suspend_never final_suspend() noexcept { return {}; }
        void unhandled_exception() {}
      };
      
      std::coroutine_handle<> h_; 
      ReturnObject(std::coroutine_handle<> h):h_{h}{ } 
      operator std::coroutine_handle<>() const { return h_; } 
    };

ReturnObject foo(){
    std::cout << ++ctr << ". first hello from coroutine\n";
    co_await suspend_always{};  //note this
    std::cout << ++ctr << ". second hello from coroutine\n";
} 

int main(){
    std::coroutine_handle<> h =  foo();
    std::cout << ++ctr << ". in main\n";
    h();
    std::cout << ++ctr << ". in main again\n";
}