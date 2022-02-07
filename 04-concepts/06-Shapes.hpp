#ifndef SHAPES_H
#define SHAPES_H

#include <iostream>

class Shape{

    private:
        virtual std::ostream& print(std::ostream& os) const=0;
    
    public:
        virtual void draw() const noexcept = 0;
        
        friend std::ostream& operator<<(std::ostream& os, const Shape& sh) noexcept{
            sh.print(os);
            return os;
        }
};

class Square : public Shape{

    private:
        std::ostream& print(std::ostream& os) const{
            os << "this is a square\n";
            return os;
        }
    public:
        void draw() const noexcept override{
            std::cout << "drawing Square\n";
        }
};

//second user/client of the library
class Rectangle{
    public:
     void draw() const noexcept{
         std::cout << "drawing a rectatngle\n";
     }

    friend std::ostream& operator<<(std::ostream& os, Rectangle rectangle) noexcept{
        os << "this is a rectangle\n";
        return os;
    }
};

//third client/user of the library
class Circle{
    public:
        void draw() const noexcept {
            std::cout << "drawing a circle\n";
        }
        friend std::ostream& operator<<(std::ostream& os, Circle circle) noexcept{
            os << "this is a circle\n";
            return os;
        }
};

#endif //SHAPES_H