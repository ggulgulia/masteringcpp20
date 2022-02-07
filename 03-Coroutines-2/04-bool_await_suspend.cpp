#include "ReturnObject.hpp"

int ctr{1};

class SuspendAlways{

    public:
        bool await_ready() const noexcept{
            std::cout << ctr++ << ". SuspendAlways::await_ready()\n";
            return false;
        }

        bool await_suspend(std::coroutine_handle<> h) const noexcept{
            std::cout << ctr++ << ". SuspendAlways::await_suspend()\n";
            return true;
        }

        void await_resume() const noexcept{
            std::cout << ctr++ << ". SuspendAlways::await_resume()\n";
        }
};

class SuspendNever{

    public:
        bool await_ready() const noexcept{
            std::cout << ctr++ << ". SuspendNever::await_ready()\n";
            /* if await_ready returns true, the execution returns to await_resume 
             * and the the control passes back from there to the coroutine
             *
             * but if await_ready retruns false, as in the case of suspend_always
             * the control passes to await_suspend and from there the control depends
             * on the return value of await_suspend
             */
            //return true;
            return false;
        }

        bool await_suspend(std::coroutine_handle<> h) const noexcept{
            std::cout << ctr++ << ". SuspendNever::await_suspend()\n";
            return false;
        }

        void await_resume() const noexcept{
            std::cout << ctr++ << ". SuspendNever::await_resume()\n";
        }
};




ReturnObject DataAccessCoro(){
    std::cout  << ctr++ << ". Hello from DataAccessCoro\n";
    co_await SuspendAlways{};
    //co_await SuspendNever{};
    std::cout  << ctr++ << ". Hello again from DataAccessCoro\n";
}

int main(){
    std::coroutine_handle<ReturnObject::promise_type> handle =  DataAccessCoro();
    std::cout << ctr++ << ". From main, coroutine is suspended\n";
    handle();
}