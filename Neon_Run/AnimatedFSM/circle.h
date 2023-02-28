#pragma once

class Circle {
public:
    Circle() = default;

    Circle(float t_x, float t_y, float t_radius);

    float getX();

    float getY();

    void updateX(float px, float offset);

    void updateY(float py);

    float getRadius();

    void setRadius(float r);

private:
    float m_x;
    float m_y;
    float m_radius;
};