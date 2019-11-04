#include "RenderCircle.hpp"
#include <cmath>
#include "EditorGLCanvas.hpp"
#include <fstream>

using namespace std;

#define PI 3.14159265

wxDECLARE_APP(EditorApp);

RenderCircle::RenderCircle(float p_x, float p_y, float p_z, float p_radius, int p_resolution) : RenderObject("gl_fragment_ball_shader.glsl", "gl_vertex_ball_shader.glsl")
{
    center.set_position(p_x, p_y, p_z);
    set_size(p_radius, false);
    set_resolution(p_resolution);
}

void RenderCircle::set_position(float p_x, float p_y, float p_z, bool p_recalculate)
{
    center.set_position(p_x, p_y, p_z);
    if (p_recalculate)
    {
        recalculate_vertices();
    }
}


void RenderCircle::set_resolution(int p_resolution, bool p_recalculate)
{
    resolution = p_resolution;
    if (p_recalculate)
    {
        recalculate_vertices();
    }
}

void RenderCircle::set_size(float p_radius, bool p_recalculate)
{
    radius = p_radius;
    if (p_recalculate)
    {
        recalculate_vertices();
    }
}

void RenderCircle::recalculate_vertices()
{
    vertices.clear();
    for (int i = 0; i<resolution; i++)
    {
        float angle =  2*PI*((float)i/(float)resolution);
        //printf("ANGLE = %f\n", angle/PI);
        float x = sin(angle)*radius;
        float y = cos(angle)*radius;
        vertices.push_back(x+center.x);
        vertices.push_back(y+center.y);
        vertices.push_back(center.z);
        if (i > 0)
        {
            vertices.push_back(center.x);
            vertices.push_back(center.y);
            vertices.push_back(center.z);

            vertices.push_back(x+center.x);
            vertices.push_back(y+center.y);
            vertices.push_back(center.z);
        }
    }
    vertices.push_back(center.x);
    vertices.push_back(center.y);
    vertices.push_back(center.z);
    vertices.push_back(vertices[0]);
    vertices.push_back(vertices[1]);
    vertices.push_back(vertices[2]);
    
    vertex_array = new float[vertices.size()];
    for (unsigned int i=0; i<vertices.size(); i++)
    {
        vertex_array[i] = vertices[i];
        //printf("%f\n", vertex_array[i]);
    }
    if (vbo > 0)
    {
        glDeleteBuffers(1, &vbo);
        vbo = 0;
    }
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices.size(), vertex_array, GL_STATIC_DRAW);
    
    if (vao > 0)
    {
        glDeleteVertexArrays(1, &vao);
        vao = 0;
    }
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

}

void RenderCircle::draw(EditorFrame* p_frame)
{
    //printf("RATIO = %f\n", ratio);
    //glColor4f(color->r, color->g, color->b, color->a);
    glUseProgram(get_shader());
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, vertices.size());
    //printf("VBO %u\n", vbo);
    //printf("VAO %u\n", vao);
}

Vertex & RenderCircle::get_position()
{
    return center;
}

float RenderCircle::get_size()
{
    return radius;
}

RenderCircle::~RenderCircle()
{
}

