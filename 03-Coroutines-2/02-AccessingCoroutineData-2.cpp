#include <coroutine>
#include <iostream>

static unsigned ctr{1};

//coroutine's reutrn object
struct ReturnObject {
    struct promise_type {
        ReturnObject get_return_object() {
            return ReturnObject{std::coroutine_handle<promise_type>::from_promise(*this)};
        }

        std::suspend_never initial_suspend() {return {};}
        std::suspend_always final_suspend() noexcept {return {};}
        void unhandled_exception() {}

        int num{19};
    };
      
    std::coroutine_handle<promise_type> h_;

    ReturnObject(std::coroutine_handle<promise_type> h):h_{h}{
        std::cout << ctr++ <<". called ReturnObject ctor\n";
    }

    //implicit conversion operator
    operator std::coroutine_handle<promise_type>() const { return h_; }
    };


//coroutine
ReturnObject foo(){
    std::cout << ctr++ << ". hello from foo\n";
    co_await std::suspend_always{};
    std::cout <<  ctr++ << ". hello from foo again\n";
} 

//main
int main(){
    std::coroutine_handle<ReturnObject::promise_type> handle =  foo();
    auto promise = handle.promise();
    std::cout << "promise::num: " << promise.num << "\n";
    handle();
}