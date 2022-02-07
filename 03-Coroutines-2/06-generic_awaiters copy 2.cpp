#include "ReturnObject-generic.hpp"
#include <thread>

int ctr{1};

template<typename PromiseType>
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
            prom.set_value(3.141);
            std::thread thread{[this](){auto value = this->prom.get_value();
                                        for(int i=1; i<=10; ++i){
                                            value += static_cast<decltype(value)>(i);
                                        }
                                        this->prom.set_value(value);
                                        }};
            thread.join();
            return true;
        }

        auto await_resume() const noexcept{
            std::cout << ctr++ << ". SuspendAlways::await_resume()\n";
            return prom.get_value();
        }
};



ReturnObject<float> DataAccessCoro(){
    std::cout  << ctr++ << ". Hello from DataAccessCoro\n";
    auto res  = co_await SuspendAlways<ReturnObject<float>::promise_type>{};
    std::cout << ctr++ << ". res from co_await SuspendAlways{}: " << res <<"\n";
    std::cout << ctr++ << ". Hello again from DataAccessCoro\n";
}

int main(){
    std::coroutine_handle<ReturnObject<float>::promise_type> handle =  DataAccessCoro();
    std::cout << ctr++ << ". From main, coroutine is suspended\n";
    handle();
}