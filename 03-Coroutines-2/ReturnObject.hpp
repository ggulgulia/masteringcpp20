#ifndef RETURN_OBJECT_H
#define RETURN_OBJECT_H

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
            double value{6.023};
        
  }; //promsie_type

  std::coroutine_handle<promise_type> handle;
  ReturnObject(std::coroutine_handle<promise_type> handle_): handle{handle_}
  {     /*empty ctor body*/    }

  //implict conversion operator
  operator std::coroutine_handle<promise_type>(){return handle;}
};


#endif //RETURN_OBJECT_H