/*
This file deomnstrates the solution to create an awaiter with void and non-void specializaton. 
This solution although relies heavily on template metaprogramming, but can be made readable using
the concepts features in C++20
*/

#include <coroutine>
#include <iostream>

struct ReturnObj {
        struct promise_type {
            int val_{11};
            ReturnObj get_return_object() {
                return {std::coroutine_handle<promise_type>::from_promise(*this)}; 
            }
        std::suspend_never initial_suspend() { 
            std::cout << "initial_suspend\n";
            return {}; 
        }
        std::suspend_never final_suspend() noexcept { return {}; }
        void unhandled_exception() {}
      };
      
      std::coroutine_handle<promise_type> h_; 
      ReturnObj(std::coroutine_handle<promise_type> h):h_{h}{ } 
      operator std::coroutine_handle<promise_type>() const { return h_; } 
};

template<typename...Ts> struct Suspend;

template<typename PromiseType>
struct Suspend<PromiseType>{
    bool shouldSuspend;
    PromiseType prom_;
    Suspend(bool shouldSuspend_): shouldSuspend{shouldSuspend_}{ }
    bool await_ready() const noexcept { 
        std::cout << "suspend_never::await_ready\n";
        return !shouldSuspend;
    }

    bool await_suspend(std::coroutine_handle<PromiseType> h)noexcept{
        std::cout << "suspend_never::await_suspend\n";
        prom_ = h.promise(); 
        return shouldSuspend;
    }

    auto await_resume() const noexcept {
        std::cout << "suspend_never::await_resume\n";
        return prom_.val_;
    }
};

template<>
struct Suspend<>{
    bool shouldSuspend;
    Suspend(bool shouldSuspend_): shouldSuspend{shouldSuspend_}{ }                                         //2.a
    bool await_ready() const noexcept { 
        std::cout << "suspend_never::await_ready\n";
        return !shouldSuspend;
    }

    void await_suspend(std::coroutine_handle<> h)noexcept{
        std::cout << "suspend_never::await_suspend\n";
    }

    void await_resume() const noexcept {
        std::cout << "suspend_never::await_resume\n";
    }
};


ReturnObj test_coroutine1(){
    std::cout << "test_coroutine initial call\n";
    co_await Suspend<>{false};
    std::cout << "From coroutine \n";
}

ReturnObj test_coroutine2(){
    std::cout << "test_coroutine2 initial call\n";
    auto res = co_await Suspend<ReturnObj::promise_type>{false};
    std::cout << "From coroutine " << res << "\n";
    
}

int main(){
    std::coroutine_handle<ReturnObj::promise_type> h1 =  test_coroutine1();
    ReturnObj::promise_type prom = h1.promise();
    std::cout << "From main: " << prom.val_ <<"\n";

    std::coroutine_handle<ReturnObj::promise_type> h2 =  test_coroutine2();

}
