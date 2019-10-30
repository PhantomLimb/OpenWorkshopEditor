#ifndef EDITOR_APP_HPP
#define EDITOR_APP_HPP
#include <wx/wx.h>
#include <wx/glcanvas.h>

#include "EditorFrame.hpp"
#include "EditorGLContext.hpp"

#define APP_VERSION "0.1.0"

class EditorApp : public wxApp
{
public:
    virtual bool OnInit();
    int OnExit();
    EditorGLContext * get_gl_context(wxGLCanvas * canvas);
    EditorFrame * editor_frame;
private:
    wxPanel * bottom_panel;
    EditorGLContext * editor_gl_context;
};

#endif