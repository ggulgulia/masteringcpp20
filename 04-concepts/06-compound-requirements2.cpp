#include "06-Shapes.hpp"
#include "06-ShapeUtils.hpp"



int main(){

    Square square{};
    Shape& shape = square;

    draw_shape(shape);
    print_shape(shape);

    Rectangle rectange{};
    draw_shape(rectange);
    print_shape(rectange);

    Circle circle{};
    print_shape(circle);
    draw_shape(circle);

    return 0;

}