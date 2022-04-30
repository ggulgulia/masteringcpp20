#include <iostream>
#include <coroutine>

#ifndef RETURN_OBJECT_H
#define RETURN_OBJECT_H

struct ReturnObject {
        struct promise_type {
            int val_{11};
            ReturnObject get_return_object() {
                return {std::coroutine_handle<promise_type>::from_promise(*this)}; 
            }
        std::suspend_never initial_suspend() { return {}; }
        std::suspend_never final_suspend() noexcept { return {}; }
        void unhandled_exception() {}
        void return_void(){}
      };
      
      std::coroutine_handle<promise_type> h_; 
      ReturnObject(std::coroutine_handle<promise_type> h):h_{h}{ } 
      operator std::coroutine_handle<promise_type>() const { return h_; } 
};

#endif //RETURN_OBJECT_H
