#include "Color.hpp"

Color::Color(float p_r, float p_g, float p_b, float p_a)
{
    set(p_r, p_g, p_b, p_a);
}

Color::Color(Color & p_color)
{
    set(p_color);
}

void Color::set(float p_r, float p_g, float p_b, float p_a)
{
    r = p_r;
    g = p_g;
    b = p_b;
    a = p_a;
}

void Color::set(Color & p_color)
{
    r = p_color.r;
    g = p_color.g;
    b = p_color.b;
    a = p_color.a;
}


Color::~Color()
{
}

