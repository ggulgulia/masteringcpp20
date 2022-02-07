#include "ReturnObject-generic.hpp"
#include <memory>

template<typename PromiseType>
class SuspendNever{
    std::shared_ptr<PromiseType> prom;
    public:
        SuspendNever() = default;
        bool await_ready() const noexcept{
            return false;
        }

        bool await_suspend(std::coroutine_handle<PromiseType> h)  noexcept{
            prom.reset(&h.promise());
            return false;
        }

        std::shared_ptr<PromiseType> await_resume() noexcept{
            return prom;
        }
};




ReturnObject<int> generator(){
    
    std::shared_ptr<ReturnObject<int>::promise_type> promise  = co_await SuspendNever<ReturnObject<int>::promise_type>{};
    for(int i{0}; ; ++i){
        promise->set_value(i);
        co_await std::suspend_always{};
    }

}

int main(){
    std::coroutine_handle<ReturnObject<int>::promise_type> handle =  generator();
    int max_nums{100};
    
    ReturnObject<int>::promise_type& promise = handle.promise();
    for(int i{0}; i<=max_nums; ++i){
        std::cout << promise.get_value() << ", ";
        handle();
    }

}