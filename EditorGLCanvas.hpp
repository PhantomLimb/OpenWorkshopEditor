#ifndef EDITOR_GL_CANVAS_HPP
#define EDITOR_GL_CANVAS_HPP

#include <wx/wx.h>
#include <wx/glcanvas.h>
#include "EditorApp.hpp"
#include "PreviewBall.hpp"
#include <vector>

using namespace std;

wxDECLARE_APP(EditorApp);

class EditorGLCanvas : public wxGLCanvas
{
public:
    Color bg_color;
    EditorGLCanvas(wxWindow *parent, wxGLAttributes & p_attributes);
    bool get_done_init();
private:
    void OnPaint(wxPaintEvent & event);
    bool done_init;
    void init_opengl();
    void render(wxIdleEvent & event);
    wxDECLARE_EVENT_TABLE();
};

#endif // EDITOR_GL_CANVAS_HPP
