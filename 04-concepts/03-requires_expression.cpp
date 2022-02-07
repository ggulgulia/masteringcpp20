#include <iostream>
#include <type_traits>
#include <concepts>

template<typename T>
concept NumericType = requires(T param)
{
    std::is_integral_v<T> || std::is_floating_point_v<T>;
    !std::is_same_v<bool, T>;
    std::is_convertible_v<decltype(param +1), T>;
};

template<typename T>
concept PointerType = requires
{
     std::is_pointer_v<T>;
};
template<NumericType T>
requires (!std::is_pointer_v<T> && requires (T param)
{
    std::is_integral_v<T> || std::is_floating_point_v<T>;
    !std::is_same_v<bool, T>;
    std::is_convertible_v<decltype(param +1), T>;
})
T add_one(const T val)
{
    return val + 1;
}



template<typename T>
requires requires
{
    std::is_pointer_v<T>;
}
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