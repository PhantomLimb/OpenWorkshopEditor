#ifndef RENDER_CIRCLE_HPP
#define RENDER_CIRCLE_HPP

#include <glew.h>
#include <wx/wx.h>
#include <wx/glcanvas.h>
#include "EditorFrame.hpp"
#include <vector>
#include "Color.hpp"
#include "Vertex.hpp"
#include "RenderObject.hpp"

class RenderCircle : public RenderObject
{
public:
    RenderCircle(float p_x=0, float p_y=0, float p_z=0, float p_radius=0.25, int p_resolution=16);
    ~RenderCircle();
    void draw();
    void set_size(float p_radius, bool p_recalculate=true);
    float get_size();
    void set_resolution(int p_resolution, bool p_recalculate=true);
    void set_position(float p_x, float p_y, float p_z,bool p_recalculate = true);
    void set_position(Vertex p_coords, bool p_recalculate = true);
    Vertex & get_position();
    void recalculate_vertices();
private:
    std::vector<float> vertices;
    Vertex center;
    float radius;
    GLuint vao;
    GLuint vbo;
    float * vertex_array;
    int resolution;
};

#endif // RENDER_CIRCLE_HPP
