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

        bool await_suspend(std::coroutine_handle<ReturnObject::promise_type> h) noexcept{
            std::cout << ctr++ << ". SuspendAlways::await_suspend()\n";
            prom = h.promise();
            return true;
        }

        float await_resume() noexcept{
            std::cout << ctr++ << ". SuspendAlways::await_resume()\n";
            std::jthread thr{[this]
                {auto val = this->prom.get_value();
                std::cout <<ctr++ << ". prom captured in thread: "
                            << std::this_thread::get_id() <<"\n";
                std::cout << ctr++ <<  ". current value within ReturnObject::promise_type: " << prom.get_value() <<"\n";
                prom.set_value(val*5);}};

            thr.join();
            return prom.get_value();
        }
};



ReturnObject DataAccessCoro(){
    std::cout  << ctr++ << ". Hello from DataAccessCoro\n";
    float res = co_await SuspendAlways{};
    std::cout << ctr++ << ". result after co-awaiting SuspendAlways: " << res << "\n";
}

int main(){
    std::coroutine_handle<ReturnObject::promise_type> handle =  DataAccessCoro();
    std::cout << ctr++ << ". From main, coroutine is suspended\n";
    handle();
}