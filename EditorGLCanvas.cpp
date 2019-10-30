#include "EditorGLCanvas.hpp"
#include "EditorGLContext.hpp"

wxBEGIN_EVENT_TABLE(EditorGLCanvas, wxGLCanvas)
    EVT_IDLE(EditorGLCanvas::render)
    EVT_PAINT(EditorGLCanvas::OnPaint)
wxEND_EVENT_TABLE()

EditorGLCanvas::Color::Color(float p_r, float p_g, float p_b, float p_a)
{
    r = p_r;
    g = p_g;
    b = p_b;
    a = p_a;
}

EditorGLCanvas::EditorGLCanvas(wxWindow *parent, int *attribList)
            : wxGLCanvas(parent, wxID_ANY, attribList,
                        wxDefaultPosition, wxDefaultSize,
                        wxFULL_REPAINT_ON_RESIZE)
{
    bg_color = Color(0.4,0.75,1);
    done_init = false;
}

void EditorGLCanvas::init_opengl()
{
    EditorGLContext * context = wxGetApp().get_gl_context(this);
    SetCurrent(*context);
    //glEnable(GL_CULL_FACE);
    //glEnable(GL_DEPTH_TEST);
    //glEnable(GL_LIGHTING);
    //glEnable(GL_LIGHT0);
    //glEnable(GL_TEXTURE_2D);
    //glEnable(GL_COLOR);
    done_init = true;
}

void EditorGLCanvas::OnPaint(wxPaintEvent & WXUNUSED(event))
{
    wxPaintDC dc(this);
}

void EditorGLCanvas::render(wxIdleEvent & event)
{
    if (!done_init)
    {
        init_opengl();
    }
    wxClientDC dc(this);
    EditorGLContext * context = wxGetApp().get_gl_context(this);
    const wxSize client_size = wxGetApp().editor_frame->GetSize();
    glViewport(0, 0, client_size.x, client_size.y);
    glClearColor(0,0,0,1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glBegin(GL_QUADS);
        glColor4f(bg_color.r, bg_color.g, bg_color.b, bg_color.a);
        glVertex3f(-1,-1,0);
        glVertex3f(client_size.x,-1,0);
        glVertex3f(client_size.x,client_size.y,0);
        glVertex3f(-1,client_size.y,0);
    glEnd();
    glFlush();
    SwapBuffers();
    GLenum err = glGetError();
    //wxLogError("OpenGL error %d", err);
}