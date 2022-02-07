#include <coroutine>
#include <iostream>

struct ReturnObject{
   struct promise_type{
            std::suspend_never initial_suspend() {return {}; }
            std::suspend_never final_suspend() noexcept {return {}; }
            ReturnObject get_return_object() {
                std::coroutine_handle<promise_type> handle = std::coroutine_handle<promise_type>::from_promise(*this);
                return ReturnObject{handle};
            } 
            void unhandled_exception(){}
            double get_value() const noexcept {return value;}
            void set_value( double val) noexcept {value = val;}
        private:
            double value{3.14};
        
  }; //promsie_type

  std::coroutine_handle<promise_type> handle;
  ReturnObject(std::coroutine_handle<promise_type> handle_): handle{handle_}
  {

  }

  //implict conversion operator
  operator std::coroutine_handle<promise_type>(){return handle;}
};


//coroutine
ReturnObject DataAccessCoro(){
    std::cout  << ". hello from DataAccessCoro\n";
    co_await std::suspend_always{};
    std::cout  << ". hello from DataAccessCoro\n";
    co_await std::suspend_always{};
    std::cout  << ". hello from DataAccessCoro\n";
    co_await std::suspend_always{};
}

double caller(){
    std::coroutine_handle<ReturnObject::promise_type> handle =  DataAccessCoro();
    ReturnObject::promise_type prom = handle.promise();
    int i{1};
    while(!handle.done()){
        prom.set_value(static_cast<double>(++i));
        handle();
    }
    double result = prom.get_value();
    return result;
}

//main
int main(){
    double val = caller();

    std::cout << "value from coroutine: " << val << std::endl;
}