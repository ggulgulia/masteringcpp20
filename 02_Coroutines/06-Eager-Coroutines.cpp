#include <iostream>
#include <coroutine>

/**
 * @brief example to demonstrate an Eagerly started coroutine
 * 
 */

struct EagerTask {
        struct promise_type {

            std::suspend_never initial_suspend() { return {}; }
            
            EagerTask get_return_object() {return {std::coroutine_handle<promise_type>::from_promise(*this)}; }
            std::suspend_always final_suspend() noexcept { return {}; }
            void unhandled_exception() {}
        };
      
      std::coroutine_handle<promise_type> h_; 
      EagerTask(std::coroutine_handle<promise_type> h):h_{h}{ } 
      operator std::coroutine_handle<promise_type>() const { return h_; }
      
};


EagerTask eager_coroutine()
{
    std::cout << "1. lazy_coroutine started\n";
    co_await std::suspend_always{};
    std::cout << "2. lazy_coroutine finished\n";
}

using Task = std::coroutine_handle<EagerTask::promise_type>;

int main(){

    Task task = eager_coroutine();
    std::cout << "control returned to main function\n";
    task();
}
