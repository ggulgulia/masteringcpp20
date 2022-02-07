#include <iostream>
#include <type_traits>
#include <concepts>
#include <vector>

template <typename T>
concept NumericType = requires (T param)
{
    requires std::is_integral_v<T> || std::is_floating_point_v<T>;
    requires !std::is_same_v<bool, T>;
    requires std::is_arithmetic_v<decltype(param+1)>;
    //{parm + 1} -> std::same_as<decltype(param)>;
    {param + 1} -> std::convertible_to<decltype(param)>;
    {std::cout << param + 1} -> std::same_as<std::ostream&>;
};


template <typename T>
concept PointerType = requires(T param)
{
    requires std::is_pointer_v<T>;
    {param == nullptr} -> std::same_as<bool>;
    {param == nullptr} -> std::convertible_to<bool>;
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

    return add_one(*val);
}


int main(){

    int one{1};
    int two{2};

    int* pTwo = &two;

    std::cout <<"add_one(one): " << add_one(one) << "\n";
    std::cout << "add_one(two): " << add_one(two) << "\n";
    std::cout << "add_one(&two): " << add_one(&two) << "\n";
    std::cout << "add_one(pTwo): " << add_one(pTwo) << "\n";

    return 0;

}