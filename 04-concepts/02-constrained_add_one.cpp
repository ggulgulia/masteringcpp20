#include <iostream>
#include <type_traits>
#include <concepts>

template<typename T>
requires std::is_integral_v<T> || std::is_floating_point_v<T>
T add_one(const T val)
{

    /* assumptions for the generic fucntion add_one:
       1. val and 1 can be added
                    OR 
          val is of floating point or integral type
          
       2. if val is of pointer type, then dereference the pointer and add one to it
    */
    return val + 1;
}

template<typename T>
requires std::is_pointer_v<T>
auto add_one(const T val)
{

    /* assumptions for the generic fucntion add_one:          
       2. if val is of pointer type, then dereference the pointer and add one to it
    */
    return add_one(*val);
}


int main(){
    

    int one{1};
    int two{2};

    double pi{3.141};

    std::cout << "add_one(one): " << add_one(one) << "\n";
    std::cout << "add_one(pi): "  << add_one(pi) << "\n";

    int* pTwo = &two;

    std::cout << "add_one(&pi): " << add_one(&pi) << "\n";
    std::cout << "add_one(pTwo): " << add_one(pTwo) << "\n";

    return 0;

}