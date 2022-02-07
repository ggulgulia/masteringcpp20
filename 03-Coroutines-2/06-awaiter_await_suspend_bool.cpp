#include <concepts>
#include <coroutine>
#include <exception>
#include <iostream>

int ctr{0};

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

struct suspend_never{
    bool await_ready() {
        std::cout << ++ctr << ". suspend_always::await_ready\n";
        return false; //tell the runtime sys that we're not yet ready to resume
                      //execution goes to this->await_suspend
    }
    
    //void await_suspend(std::coroutine_handle<>){}

    bool await_suspend(std::coroutine_handle<>){
        std::cout << ++ctr << ". suspend_always::await_suspend\n";
        //do some tasks
        // ...
        //...
        return false; //execution goes to await_resume
    }

    void await_resume(){
        std::cout << ++ctr << ". suspend_always::await_resume\n";
        //execution reutrns to the coroutine foo
    }
};


ReturnObject foo(){
    std::cout << ++ctr << ". first hello from coroutine\n";
    co_await suspend_never{};  //note this
    std::cout << ++ctr << ". second hello from coroutine\n";
} 

int main(){
    std::coroutine_handle<> h =  foo();
}