#include "ReturnObject.hpp"
#include <thread>


int ctr{1};

class SuspendAlways{
    private:
        ReturnObject::promise_type prom;
    public:
        bool await_ready() const noexcept{
            std::cout << ctr++ << ". SuspendAlways::await_ready()\n";
            return false;
        }

        bool await_suspend(std::coroutine_handle<ReturnObject::promise_type> h)  noexcept{
            std::cout << ctr++ << ". SuspendAlways::await_suspend()\n";
            prom = h.promise();
            return true;
        }

        float await_resume() const noexcept{
            std::cout << ctr++ << ". SuspendAlways::await_resume()\n";
            return prom.get_value();
        }
};



ReturnObject DataAccessCoro(){
    std::cout  << ctr++ << ". Hello from DataAccessCoro\n";
    float res = co_await SuspendAlways{};
    std::cout << ctr++ << ". result of co_await SuspendAlways{}: " << res << "\n";
    std::cout << ctr++ << ". Hello again from DataAccessCoro\n";
}

int main(){
    std::coroutine_handle<ReturnObject::promise_type> handle =  DataAccessCoro();
    std::cout << ctr++ << ". From main, coroutine is suspended\n";
    handle();
}