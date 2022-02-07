#include "ReturnObject_co_yield.hpp"
#include <memory>



ReturnObject<int> generator(){
    for(int i{0}; ; ++i){
        co_yield i;
    }
}

ReturnObject<int> odd_number_generator(){
    for(int i{1}; ; i +=2){
        co_yield i;
    }
}

ReturnObject<int> even_number_generator(){
    for(int i{0}; ; i +=2){
        co_yield i;
    }
}

int main(){
    std::coroutine_handle<ReturnObject<int>::promise_type> handle =  even_number_generator();
    int max_nums{100};

    ReturnObject<int>::promise_type& promise = handle.promise();
    for(int i=0; i<=max_nums; ++i){
        std::cout << promise.get_value() << ", ";
        handle();
    }
    
}