#ifndef RENDER_OBJECT_HPP
#define RENDER_OBJECT_HPP

#include <glew.h>
#include <wx/wx.h>
#include <wx/glcanvas.h>
#include <fstream>
#include "Color.hpp"

class RenderObject
{
public:
    RenderObject(char * p_fs_path, char * p_vs_path);
    ~RenderObject();
    void load_shader(char * p_fs_path, char * p_vs_path);
    GLuint get_shader();
    void set_color(Color & p_color);
    virtual void draw()=0;
private:
    GLuint shader_program;
    Color color;
};

#endif // RENDER_OBJECT_HPP
