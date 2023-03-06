#pragma once

class Rectangle {
    public:
        Rectangle() = default;

        Rectangle(float t_x, float t_y, float t_width, float t_height);

        float getX();

        float getY();

        float getWidth();

        float getHeight();

        void updateX(float px, float offset);

        void updateY(float py);

        void setWidth(float w);

        void setHeight(float h);

    private:
        float m_x;
        float m_y;
        float m_width;
        float m_height;
};