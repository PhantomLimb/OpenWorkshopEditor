#ifndef EDITOR_GL_CONTEXT_HPP
#define EDITOR_GL_CONTEXT_HPP

#include <wx/wx.h>
#include <wx/glcanvas.h>

class EditorGLContext : public wxGLContext
{
public:
    EditorGLContext(wxGLCanvas * canvas, wxGLContextAttrs * p_attributes = NULL);
    void init_opengl();
    bool done_init;
};

#endif // EDITOR_GL_CONTEXT_HPP