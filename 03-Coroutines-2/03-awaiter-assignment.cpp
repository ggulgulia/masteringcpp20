#include "ReturnObject.hpp"

int ctr{0};
/*

class Suspend{

    TODO: fill out the implementation
    1. A private boolean variable
    2. A constructor to initialize the bool variable
    3. provide the necessary interface for the Suspend awaiter
    4. use the bool attirbute in this awaiter appropriately
};

*/

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