

#include <coroutine>



int foo(){
  co_await 10;
  //co_yield 10;
  //co_return 10;
}

int main(){
    foo();
}