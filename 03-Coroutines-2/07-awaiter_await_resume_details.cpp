#include <concepts>
#include <coroutine>
#include <exception>
#include <iostream>

int ctr{0};


struct ReturnObject {
        struct promise_type {
            ReturnObject get_return_object() {
                return {std::coroutine_handle<promise_type>::from_promise(*this)}; 
            }
            std::suspend_never initial_suspend() { return {}; }
            std::suspend_never final_suspend() noexcept { return {}; }
            void unhandled_exception() {}

            //NOTE new public method set/get_value in promise's interface
            void set_value(const float val){value_ = val;}
            float get_value()const noexcept{return value_;}

            //a private variable 
            private:
                float value_{3.14159};
      };
      
      std::coroutine_handle<promise_type> h_; 
      ReturnObject(std::coroutine_handle<promise_type> h):h_{h}{ } 
      operator std::coroutine_handle<>() const { return h_; } 
    };

struct suspend_never{
    float value{0.0f};
    bool await_ready() {
        std::cout << ++ctr << ". suspend_always::await_ready\n";
        return false; //tell the runtime sys that we're not yet ready to resume
                      //execution goes to this->await_suspend
    }
    
    //void await_suspend(std::coroutine_handle<>){}

    bool await_suspend(std::coroutine_handle<ReturnObject::promise_type> handle){
        std::cout << ++ctr << ". suspend_always::await_suspend\n";

        auto promise = handle.promise();
        value = promise.get_value();
        
        return false; 
        //execution goes to await_resume
    }

    float await_resume(){
        std::cout << ++ctr << ". suspend_always::await_resume\n";
        return value;

         //execution reutrns to the coroutine foo
    }
};


ReturnObject foo(){
    std::cout << ++ctr << ". first hello from coroutine\n";
    float value = co_await suspend_never{};  //note this
    std::cout << ++ctr << ". from coroutine\n"
              << "promise_type::value_ : " << value << "\n";
} 

int main(){
    /*std::coroutine_handle<> h =*/  foo();
}