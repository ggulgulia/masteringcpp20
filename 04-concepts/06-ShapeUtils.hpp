#ifndef SHAPE_UTILS_H
#define SHAPE_UTILS_H

#include <iostream>
#include <concepts>

template<typename shape_type>
concept ShapeInterface = requires(shape_type shape)
{
    {shape.draw()} noexcept -> std::same_as<void>;
    {std::cout << shape} noexcept -> std::convertible_to<std::ostream&>;
};

//some user/client of the library
template<typename shape_type>
void draw_shape(const shape_type& sh) requires ShapeInterface<shape_type>
{
    sh.draw();
}

template<typename shape_type>
void print_shape(const shape_type& sh) requires ShapeInterface<shape_type>
{
    std::cout << sh;
}

#endif //SHAPE_UTILS_H