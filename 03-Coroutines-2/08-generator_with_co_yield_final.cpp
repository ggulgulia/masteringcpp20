#include "ReturnObject_co_yield.hpp"

template<typename T>
struct ReturnObject{
   struct promise_type{
            /* promise_type() = default; */
            std::suspend_never initial_suspend() {return {}; }
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

ReturnObject<int> DataAccessCoro(){
    
    for(int i{0}; ; ++i){
        co_yield i;
    }

}

int main(){
    std::coroutine_handle<ReturnObject<int>::promise_type> handle =  DataAccessCoro();
    int max_nums{20};
   
    ReturnObject<int>::promise_type& promise = handle.promise();
    for(int i{0}; i<=max_nums; ++i){
        std::cout << promise.get_value() << ", ";
        handle();
    }
}