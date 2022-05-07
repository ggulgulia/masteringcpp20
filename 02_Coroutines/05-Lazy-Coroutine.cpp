#include <iostream>
#include <coroutine>

/**
 * @brief example to demonstrate an Lazily started coroutine
 * 
 */

struct LazyTask {
        struct promise_type {
            
            std::suspend_always initial_suspend() { return {}; }
            
            LazyTask get_return_object() {return {std::coroutine_handle<promise_type>::from_promise(*this)};}
            std::suspend_always final_suspend() noexcept { return {}; }
            void unhandled_exception() {}
        };
      

        std::coroutine_handle<promise_type> h_; 
        LazyTask(std::coroutine_handle<promise_type> h):h_{h}{ } 
        operator std::coroutine_handle<promise_type>() { return h_; }
};


LazyTask lazy_coroutine()
{
    std::cout << "1. lazy_coroutine started\n";
    co_await std::suspend_always{};
    std::cout << "2. lazy_coroutine finished\n";
}

using Task = std::coroutine_handle<LazyTask::promise_type>;

int main(){

    Task task = lazy_coroutine();
    std::cout << "control returned to main function\n";
    task();
    task();

}
