#pragma once
#include <iostream>

enum class Color {
    WHITE,
    BLACK,
    RED,
};

class Figure {
private:
    float m_x, m_y; // координаты фигуры
    Color m_color; // цвет
protected:
    double m_width, m_height; // размер: ширина и высота
public:
    Figure(float x, float y, double width, double height, Color color) : m_x(x), m_y(y),
                m_width(width), m_height(height), m_color(color) {}
    virtual void getAria() = 0;
};
