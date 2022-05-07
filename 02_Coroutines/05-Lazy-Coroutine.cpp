#include <iostream>
#include <coroutine>

struct LazyTask {
        struct promise_type {
            int val_;
            LazyTask get_return_object() {
                return {std::coroutine_handle<promise_type>::from_promise(*this)}; 
            }

            std::suspend_always initial_suspend() { return {}; }

            std::suspend_always final_suspend() noexcept { return {}; }
            void unhandled_exception() {}
        };
      
      std::coroutine_handle<promise_type> h_; 
      LazyTask(std::coroutine_handle<promise_type> h):h_{h}{ } 
      operator std::coroutine_handle<promise_type>() const { return h_; }
      
      void resume(){
          if(!h_.done()){
              h_();
          }
      }
};


LazyTask lazy_coroutine()
{
    std::cout << "1. lazy_coroutine started\n";
    co_await std::suspend_always{};
    std::cout << "2. lazy_coroutine finished\n";
}


int main(){

    LazyTask task = lazy_coroutine();
    task.resume();
    /task.resume();
}
