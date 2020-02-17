#include "EditorApp.hpp"
#include "EditorGLCanvas.hpp"
#include <wx/font.h>
#include "AnimationLoader.hpp"

bool EditorApp::OnInit()
{
    //frame
    wxFont default_font(10, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, "Open Sans");
    editor_frame = new EditorFrame();
    editor_frame->SetFont(default_font);
    
    //canvas
    wxGLAttributes * attributes = new wxGLAttributes;
    attributes->PlatformDefaults().SampleBuffers(4).Samplers(4).EndList();
    EditorGLCanvas * editor_gl_canvas = new EditorGLCanvas(editor_frame, *attributes);
    wxBoxSizer * canvas_sizer = new wxBoxSizer(wxHORIZONTAL);
    canvas_sizer->SetMinSize(300, 200);
    editor_gl_canvas->SetSizer(canvas_sizer);
    
    //sidebar
    wxPanel * right_panel = new wxPanel(editor_frame);
    right_panel->SetBackgroundColour(wxColour(250, 250, 250, 255));
    wxBoxSizer * right_panel_sizer = new wxBoxSizer(wxHORIZONTAL);
    right_panel_sizer->SetMinSize(200, 200);
    right_panel->SetSizer(right_panel_sizer);
    
    //bottom panel
    wxPanel * bottom_panel_top_border = new wxPanel(editor_frame);
    bottom_panel_top_border->SetBackgroundColour(wxColour(250, 250, 250, 255));
    bottom_panel_top_border->SetSizeHints(-1, 10, -1, 10);
    
    bottom_panel = new wxPanel(editor_frame);
    bottom_panel->SetBackgroundColour(wxColour(60, 70, 110, 255));
    bottom_panel->SetForegroundColour(wxColour(250, 250, 250, 255));
    
    wxBoxSizer* bottom_panel_sizer = new wxBoxSizer(wxHORIZONTAL);
    bottom_panel_sizer->SetMinSize(200, 200);
    bottom_panel->SetSizer(bottom_panel_sizer);
    editor_gl_context = nullptr;
    
    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
    
    //sizer for the top two panels
    wxBoxSizer* top_sizer = new wxBoxSizer(wxHORIZONTAL);
    top_sizer->Add(editor_gl_canvas, 3, wxEXPAND);
    top_sizer->Add(right_panel, 1, wxEXPAND);
    
    // frame sizer
    sizer->Add(top_sizer, 2, wxEXPAND);
    sizer->Add(bottom_panel_top_border, 1, wxEXPAND);
    sizer->Add(bottom_panel, 1, wxEXPAND);
    
    editor_frame->SetSizeHints(500, 400);
    editor_frame->SetSizer(sizer);
    editor_frame->Show();
    
    AnimationLoader animation_loader;
    animation_loader.load_BHD();
    
    return true;
}

EditorGLContext * EditorApp::get_gl_context(wxGLCanvas * canvas)
{
    if (editor_gl_context == nullptr)
    {
        wxGLContextAttrs * attributes = new wxGLContextAttrs;
        attributes->CoreProfile().OGLVersion(4, 5).Robust().ResetIsolation().EndList();
        editor_gl_context = new EditorGLContext(canvas, attributes);
    }
    //editor_gl_context->SetCurrent(canvas);
    return editor_gl_context;
}

int EditorApp::OnExit()
{
    delete editor_gl_context;
    return wxApp::OnExit();
}