#include <iostream>
#include <type_traits>
#include <concepts>

template <typename T>
concept NumericType = requires (T param)
{
    std::is_integral_v<T> || std::is_floating_point_v<T>;
    !std::is_same_v<bool, T>;
    std::is_arithmetic_v<decltype(param+1)>;
};


template <typename T>
concept PointerType = requires(T param)
{
    std::is_pointer_v<T>;
    param == nullptr;
};

template<typename T>
requires NumericType<T>
T add_one(const T val)
{
    return val + 1;
}



template<typename T>
requires PointerType<T>
auto add_one(const T val)
{

    return *(val) +1;
}


int main(){
    int one{1};
    int two{2};

    int* pTwo = &two;

    //std::cout <<"add_one(one): " << add_one(one) << "\n";
    //std::cout << "add_one(two): " << add_one(two) << "\n";
    //std::cout << "add_one(&two): " << add_one(&two) << "\n";
    //std::cout << "add_one(pTwo): " << add_one(pTwo) << "\n";

    std::cout << std::boolalpha;
    std::cout << "std::is_arithmetic_v<int*>: " << std::is_arithmetic_v<int*> << "\n";
    std::cout << "std::is_same_v<bool, float*>: " << std::is_same_v<bool, float*> << "\n";

    return 0;

}