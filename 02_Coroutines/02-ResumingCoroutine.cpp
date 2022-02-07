#include <iostream>
#include <coroutine>

struct ReturnObject{
   struct promise_type{
    //promise_type() = default;  /* implicitly generated by compiler */
    std::suspend_never initial_suspend() {return {}; }
    std::suspend_never final_suspend() noexcept {return {}; }
    ReturnObject get_return_object() {
      std::coroutine_handle<> handle{std::coroutine_handle<promise_type>::from_promise(*this)};
      return ReturnObject{handle}; 
    } 
    void unhandled_exception(){}
  };

  std::coroutine_handle<void> handle;
  ReturnObject(std::coroutine_handle<void> handle_): handle{handle_}
  {

  }

  //implict conversion operator
  operator std::coroutine_handle<>(){return handle;}
};

ReturnObject foo(){
    std::cout << "1. Hello from foo\n";
    co_await std::suspend_always{};
    std::cout << "2. Hello again from foo\n";
    co_await std::suspend_always{};
    std::cout << "3. Hello again from foo\n";
}

int main(){
  auto handle = static_cast<std::coroutine_handle<>>(foo());

  while(!handle.done()){
    handle.resume(); //handle();
  }
}