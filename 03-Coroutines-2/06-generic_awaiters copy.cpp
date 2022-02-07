#include "ReturnObject-generic.hpp"
#include <type_traits>
#include <concepts>


int ctr{1};;

template<typename T>
concept PromType = requires(typename T::promise_type promise_object){
    {promise_object.get_return_object()};
    {promise_object.initial_suspend()};
    {promise_object.final_suspend()};
    {promise_object.unhandled_exception()};
    
};

template<PromType PromiseType>
class SuspendAlways{
    PromiseType prom;
    public:
        SuspendAlways() = default;
        bool await_ready() const noexcept{
            std::cout << ctr++ << ". SuspendAlways::await_ready()\n";
            return false;
        }

        bool await_suspend(std::coroutine_handle<PromiseType> h)  noexcept{
            std::cout << ctr++ << ". SuspendAlways::await_suspend()\n";
            prom = h.promise();
            std::thread thread{[this]{auto val = this->prom.get_value();
                                       for(int i=1; i<=10; ++i){
                                           val += static_cast<decltype(val)>(i);
                                           std::cout << val << "\n";
                                       }
                                       this->prom.set_value(val);}};
            return true;
        }

        auto await_resume() const noexcept{
            std::cout << ctr++ << ". SuspendAlways::await_resume()\n";
            return prom.get_value();
        }
};



ReturnObject<int> DataAccessCoro(){
    std::cout  << ctr++ << ". Hello from DataAccessCoro\n";
    auto res  = co_await SuspendAlways<ReturnObject<int>::promise_type>{};
    std::cout << ctr++ << ". res from co_await SuspendAlways{}: " << res <<"\n";
    std::cout << ctr++ << ". Hello again from DataAccessCoro\n";
}

int main(){
    std::coroutine_handle<ReturnObject<int>::promise_type> handle =  DataAccessCoro();
    std::cout << ctr++ << ". From main, coroutine is suspended\n";
    handle();
}