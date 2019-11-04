#ifndef VERTEX_HPP
#define VERTEX_HPP

class Vertex
{
public:
    Vertex(float p_x=0, float p_y=0, float p_z=0);
    float x;
    float y;
    float z;
    void set_position(float p_x, float p_y, float p_z);
};
    
#endif // VERTEX_HPP
