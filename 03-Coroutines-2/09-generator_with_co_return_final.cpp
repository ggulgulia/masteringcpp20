#include <coroutine>
#include <iostream>

template<typename T>
struct ReturnObject{
   struct promise_type{
            /* promise_type() = default; */
            std::suspend_always initial_suspend() {return {}; }
            std::suspend_never final_suspend() noexcept {return {}; }
            ReturnObject get_return_object() {
                std::coroutine_handle<promise_type> handle = std::coroutine_handle<promise_type>::from_promise(*this);
                return ReturnObject{handle};
            }
            void unhandled_exception(){}

            std::suspend_always yield_value(T value_){
                value = value_;
                return std::suspend_always{};
            }

            //void return_void(){
            //    std::cout << "ReturnObject::promise_type::return_void()\n";
//
            //}

            int return_value(const T val){
                std::cout << "returnging value: " << val << "\n";
                return val;
            }
            
            T get_value() const noexcept {return value;}
            void set_value(T val) noexcept {value = val;}
        private:
            T value{};
        
  }; //promsie_type

  std::coroutine_handle<promise_type> handle;
  ReturnObject(std::coroutine_handle<promise_type> handle_): handle{handle_}
  {     /*empty ctor body*/    }

  //implict conversion operator
  operator std::coroutine_handle<promise_type>(){return handle;}
};

ReturnObject<int> return_coro(const std::string& msg){
    
    std::cout << "saying: " << msg  << " from return_coro";
    co_return 44;

}

int main(){
    std::coroutine_handle<ReturnObject<int>::promise_type> handle =  return_coro("hello");
    std::cout << "from main, resuming coroutine\n";
    int value = handle.resume();
    std::cout << value << "\n";
    
}