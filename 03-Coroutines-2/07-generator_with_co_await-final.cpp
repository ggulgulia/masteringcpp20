#include "ReturnObject-generic.hpp"
#include <memory>


template<typename PromiseType>
class SuspendNever{
    std::shared_ptr<PromiseType> prom{nullptr};
    public:
        SuspendNever() = default;
        bool await_ready() const noexcept{
            return false;
        }

        bool await_suspend(std::coroutine_handle<PromiseType>& h)  noexcept{
            prom.reset(&h.promise());
            return false;
        }

        std::shared_ptr<PromiseType> await_resume() noexcept{
            return prom;
        }
};


ReturnObject<int> integer_generator(){
    auto promise  = co_await SuspendNever<ReturnObject<int>::promise_type>{};
    for(int i=0; /*i<= infinity*/ ; ++i ){
        promise->set_value(i);
        co_await std::suspend_always{};
    }

}

int main(){
    std::coroutine_handle<ReturnObject<int>::promise_type> handle =  integer_generator();
    
    for(int i=0; i<=20; ++i){
        ReturnObject<int>::promise_type promise = handle.promise();
        std::cout << promise.get_value() << ", ";
        handle();
    }
    
}