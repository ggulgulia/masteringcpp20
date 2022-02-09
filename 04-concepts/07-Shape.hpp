#ifndef TYPE_REQ_SHAPE_H
#define TYPE_REQ_SHAPE_H

#include <type_traits>
#include <concepts>

template<typename T>
concept arithmetic_type = std::integral<T> || std::floating_point<T>;

template<typename T>
requires arithmetic_type<T>
class Shape{
    T length;
    public:
     Shape(T length_): length{length_}
     {  /* empty ctor body */    }

    void draw() const noexcept {}
};

#endif //TYPE_REQ_SHAPE_H