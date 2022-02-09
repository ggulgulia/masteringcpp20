#include "07-Shape.hpp"
#include <iostream>

template<typename Q>
concept ShapeConstraint = requires
{
    typename Shape<Q>;
};
template<typename U>
requires ShapeConstraint<U>
Shape<U> create_shape(U length)
{
    std::cout << "creating shape with : " << length << "\n";
    return Shape<U>{length};
}

template<typename V>
requires ShapeConstraint<V>
void move_shape(Shape<V>& shape, V distance){
    //...
}

int main(){

    Shape<float> sf{2.15};
    create_shape(5);
    create_shape(3.14159);
    create_shape("3.141");
    //create_shape(std::vector<int>{0,0,0});
    
}