#include <iostream>
#include <list>
#include <vector>
#include <memory>
#include <queue>
#include <thread>

template <typename Collection, typename T>
concept AddableToCollection = requires(Collection container, T value)
{
    typename Collection::value_type;
    container.push_back(value);
    requires std::same_as<typename Collection::value_type, T>;
    requires std::copyable<T>;
};

template<typename Collection, typename T>
requires AddableToCollection<Collection, T>
void add_to_collection(Collection& container, T value){
    /* assumptions for this function:
    1. type reffered to by Collection has method push_back
    2. type of the value within container is same as value
    3. value is a copyable object https://en.cppreference.com/w/cpp/concepts/copyable
    */
    container.push_back(value);
}


int main(){

    std::vector<int> vec;
    int num1{2};
    //float num2{4.0f};

    add_to_collection(vec, num1);
    add_to_collection(vec, num2);

    std::vector<std::thread> threads;
    std::thread t;
    add_to_collection(threads, std::move(t));
    
}