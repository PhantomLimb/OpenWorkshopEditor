#ifndef COLOR_HPP
#define COLOR_HPP

class Color
{
public:
    Color(float p_r=0, float p_g=0, float p_b=0, float p_a=1.0);
    Color(Color & p_color);
    ~Color();
    void set(float p_r, float p_g, float p_b, float p_a=1.0);
    void set(Color & p_color);
    float r;
    float g;
    float b;
    float a;
};

#endif // COLOR_HPP
