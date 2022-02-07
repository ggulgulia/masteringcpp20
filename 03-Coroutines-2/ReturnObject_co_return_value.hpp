#ifndef RETURN_OBJECT_H
#define RETURN_OBJECT_H

#include <coroutine>
#include <iostream>

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
            
            T return_value(T value_){
                std::cout << "ReturnObject::promise_type::return_value()\n";
                value = value_;
                return value;

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


#endif //RETURN_OBJECT_H