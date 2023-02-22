#include "circle.h"
#include "cmath"

Circle::Circle(float t_x, float t_y, float t_radius) : m_x(t_x), m_y(t_y), m_radius(t_radius)
{

}

float Circle::getX()
{
    return m_x;
}

float Circle::getY()
{
    return m_y;
}

void Circle::updateX(float px, float offset)
{
    m_x = px - offset;
}

void Circle::updateY(float py)
{
    m_y = py;
}

float Circle::getRadius()
{
    return m_radius;
}

void Circle::setRadius(float r)
{
    m_radius = r;
}