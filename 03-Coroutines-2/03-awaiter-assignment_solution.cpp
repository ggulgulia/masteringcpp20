#include "ReturnObject.hpp"

int ctr{0};

class Suspend{
    private:
        bool isSuspended_;
    public:
        Suspend(const bool isSuspended):isSuspended_{isSuspended}
        {       }
    bool await_ready() {return !isSuspended_;}
    void await_suspend(std::coroutine_handle<>){}
    void await_resume(){}
        
};

ReturnObject DataAccessCoro(){
    std::cout  << ctr++ << ". Hello from DataAccessCoro\n";
    co_await Suspend{true};
    std::cout  << ctr++ << ". Hello again from DataAccessCoro\n";
}

int main(){
    std::coroutine_handle<ReturnObject::promise_type> handle =  DataAccessCoro();
    std::cout << ctr++ << ". From main, coroutine is suspended\n";
    handle();
}
