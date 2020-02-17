#include <glew.h>
#include "EditorGLCanvas.hpp"
#include "EditorGLContext.hpp"
#include "PreviewBall.hpp"
#include "PreviewCamera.hpp"

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
    
    
    const wxSize client_size = this->GetSize();
    glViewport(0, 0, client_size.x, client_size.y);
    PreviewCamera * camera = PreviewCamera::get();
    camera->set_position(Vertex(0, 0, 0));
    
    //ball = new PreviewBall(); 
    //printf("Position %f %f %f \n", ball->get_position().x, ball->get_position().y, ball->get_position().z);
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
    glClearColor(0.5,0,0,1);
    glClear(GL_COLOR_BUFFER_BIT);
    vector<PreviewBall*> * preview_ballz = &(wxGetApp().preview_ballz);
    for (int i = 0; i<preview_ballz->size(); i++)
    {
        preview_ballz->at(i)->draw();
    }
    
    glFlush();
    SwapBuffers();
    GLenum err = glGetError();
    //wxLogError("OpenGL error %s", (char*)gluErrorString(err));
}