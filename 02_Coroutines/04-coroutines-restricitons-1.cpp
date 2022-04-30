#include "ReturnObject.hpp"


//1. coroutine with varidaic arguments
//ReturnObject foo(...) {co_await std::suspend_never{};}

//2. coroutines with constexper 
//constexpr ReturnObject coro_with_constexpr(){ co_await std::suspend_never{}; }

//3. coroutine with consteval
//consteval ReturnObject coro_with_consteval(){ co_await std::suspend_never{};}

//4. coroutine with auto return type
// auto foo() {co_await std::suspend_never{};}


//5. coroutines in constructors and destructors
/*
struct Bar{
    //Bar(){co_await std::suspend_never{};}
    //~Bar(){co_await std::suspend_never{};}
}
*/


int main(){

    //6. coroutine within main function
    //co_await std::suspend_never{};
    
    return 0;
}
