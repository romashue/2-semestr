#pragma once
#include "FigureBase.h"

namespace figures {

    class Triangle : public Figure {
    public:
        Triangle(float x, float y, double width, double height, Color color) :
                    Figure(x, y, width, height, color) {}

        // переопределение метода родителя
        void getAria() override {
            std::cout << "Triangle Aria: " << m_width * m_height * 0.5 << std::endl;
        }
    };

    class Rectangle : public Figure {
    public:
        Rectangle(float x, float y, double width, double height, Color color) :
                    Figure(x, y, width, height, color) {}

        // переопределение метода родителя
        void getAria() override {
            std::cout << "Rectangle Aria: " << m_width * m_height << std::endl;
        }
    };

    class Circle : public Figure {
    public:
        Circle(float x, float y, double width, double height, Color color) :
                    Figure(x, y, width, height, color) {}

        // переопределение метода родителя
        void getAria() override {
            std::cout << "Circle Aria: " << m_width * 2 * 3.14159 << std::endl;
        }
    };
}
