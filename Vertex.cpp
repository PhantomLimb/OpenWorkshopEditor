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

Vertex & Vertex::operator= (const Vertex & p_vertex)
{
    x = p_vertex.x;
    y = p_vertex.y;
    z = p_vertex.z;
    return *this;
}

Vertex Vertex::operator- (const Vertex & p_operand)
{
    Vertex return_value;
    return_value.x= x-p_operand.x;
    return_value.y= y-p_operand.y;
    return_value.z= z-p_operand.z;
    return return_value;
}

Vertex Vertex::operator+ (const Vertex & p_operand)
{
    Vertex return_value;
    return_value.x= x+p_operand.x;
    return_value.y= y+p_operand.y;
    return_value.z= z+p_operand.z;
    return return_value;
}
