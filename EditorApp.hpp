#ifndef EDITOR_APP_HPP
#define EDITOR_APP_HPP

#include <glew.h>
#include <wx/wx.h>
#include <wx/glcanvas.h>
#include <vector>
#include "EditorFrame.hpp"
#include "EditorGLContext.hpp"
#include "PreviewBall.hpp"
#include "LnzBall.hpp"

#define APP_VERSION "0.1.0"

using namespace std;

class EditorApp : public wxApp
{
public:
    virtual bool OnInit();
    int OnExit();
    EditorGLContext * get_gl_context(wxGLCanvas * canvas);
    EditorFrame * editor_frame;
    vector<PreviewBall*> preview_ballz;
    vector<LnzBall*> lnz_ballz;
private:
    wxPanel * bottom_panel;
    EditorGLContext * editor_gl_context;
};

#endif