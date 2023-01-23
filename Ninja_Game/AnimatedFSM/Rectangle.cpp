#include "Rectangle.h"

Rectangle::Rectangle(float t_x, float t_y, float t_width, float t_height) : m_x(t_x), m_y(t_y), m_width(t_width), m_height(t_height)
{

}

float Rectangle::getX()
{
    return m_x;
}

float Rectangle::getY()
{
    return m_y;
}

float Rectangle::getWidth()
{
    return m_width;
}

float Rectangle::getHeight()
{
    return m_height;
}

void Rectangle::updateX(float px, float offset)
{
    m_x = px - offset;
}

void Rectangle::updateY(float py)
{
    m_y = py;

}

void Rectangle::setWidth(float w)
{
    m_width = w;

}

void Rectangle::setHeight(float h)
{
    m_height = h;
}