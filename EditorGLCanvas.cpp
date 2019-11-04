#include <glew.h>
#include "EditorGLCanvas.hpp"
#include "EditorGLContext.hpp"
#include "PreviewBall.hpp"


wxBEGIN_EVENT_TABLE(EditorGLCanvas, wxGLCanvas)
    EVT_IDLE(EditorGLCanvas::render)
    //EVT
    EVT_PAINT(EditorGLCanvas::OnPaint)
wxEND_EVENT_TABLE()

EditorGLCanvas::EditorGLCanvas(wxWindow *parent, wxGLAttributes & p_attributes)
            : wxGLCanvas(parent, p_attributes, wxID_ANY,
                        wxDefaultPosition, wxDefaultSize,
                        wxFULL_REPAINT_ON_RESIZE)
{
    bg_color = Color(0.4,0.75,1);
    done_init = false;
}

bool EditorGLCanvas::get_done_init()
{
    return done_init;
}

void EditorGLCanvas::init_opengl()
{
    EditorGLContext * context = wxGetApp().get_gl_context(this);
    SetCurrent(*context);
    glewInit();
    //glEnable(GL_POLYGON_SMOOTH);
    //glEnable(GL_DEPTH_TEST);
    
    ball = new PreviewBall(); 
    ball->set_resolution(32);
    ball->set_size(0.25);
    ball->set_position(-0.25, -0.25, 0);
    ball->set_outline_width(4);
    Color ball_color(1, 0.5, 0.5, 1);
    Color outline_color(0, 0, 0, 1);
    ball->set_ball_color(ball_color);
    ball->set_outline_color(outline_color);
    printf("Position %f %f %f \n", ball->get_position().x, ball->get_position().y, ball->get_position().z);
    done_init = true;
}

void EditorGLCanvas::OnPaint(wxPaintEvent & WXUNUSED(event))
{
    wxPaintDC dc(this);
    if (!done_init)
    {
        init_opengl();
    }
}

void EditorGLCanvas::render(wxIdleEvent & event)
{
    if (!done_init)
    {
        return;
    }
    wxClientDC dc(this);
    EditorGLContext * context = wxGetApp().get_gl_context(this);
    const wxSize client_size = wxGetApp().editor_frame->GetSize();
    glViewport(0, 0, client_size.y, client_size.y);
    glClearColor(0.5,0,0,1);
    glClear(GL_COLOR_BUFFER_BIT);
    ball->draw(wxGetApp().editor_frame);
    glFlush();
    SwapBuffers();
    GLenum err = glGetError();
    //wxLogError("OpenGL error %s", (char*)gluErrorString(err));
}