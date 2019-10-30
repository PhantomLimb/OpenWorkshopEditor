#ifndef EDITOR_GL_CANVAS_HPP
#define EDITOR_GL_CANVAS_HPP

#include <wx/wx.h>
#include <wx/glcanvas.h>
#include "EditorApp.hpp"

wxDECLARE_APP(EditorApp);

class EditorGLCanvas : public wxGLCanvas
{
public:
    struct Color 
    {
        float r;
        float g;
        float b;
        float a;
        Color(float p_r = 1.0, float p_g = 1.0, float p_b = 1.0, float p_a = 1.0);
    };
    Color bg_color;
    EditorGLCanvas(wxWindow *parent, int *attribList = NULL);
private:
    void OnPaint(wxPaintEvent & event);
    void init_opengl();
    bool done_init;
    void render(wxIdleEvent & event);
    
    wxDECLARE_EVENT_TABLE();
};

#endif // EDITOR_GL_CANVAS_HPP
