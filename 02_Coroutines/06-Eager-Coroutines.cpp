#include <iostream>
#include <coroutine>

/**
 * @brief example to demonstrate an Eagerly started coroutine
 * 
 */

struct EagerTask {
        struct promise_type {
            int val_;
            EagerTask get_return_object() {
                return {std::coroutine_handle<promise_type>::from_promise(*this)}; 
            }

            std::suspend_never initial_suspend() { return {}; }

            std::suspend_always final_suspend() noexcept { return {}; }
            void unhandled_exception() {}
        };
      
      std::coroutine_handle<promise_type> h_; 
      EagerTask(std::coroutine_handle<promise_type> h):h_{h}{ } 
      operator std::coroutine_handle<promise_type>() const { return h_; }
      
      void resume(){
          if(!h_.done()){
              h_();
          }
      }
};


EagerTask lazy_coroutine()
{
    std::cout << "1. lazy_coroutine started\n";
    co_await std::suspend_always{};
    std::cout << "2. lazy_coroutine finished\n";
}


int main(){

    EagerTask task = lazy_coroutine();
    task.resume();

}
