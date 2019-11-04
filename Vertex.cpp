#include "Vertex.hpp"


Vertex::Vertex(float p_x, float p_y, float p_z)
{
    x = p_x;
    y = p_y;
    z = p_z;
}

void Vertex::set_position(float p_x, float p_y, float p_z)
{
    x = p_x;
    y = p_y;
    z = p_z;
}
