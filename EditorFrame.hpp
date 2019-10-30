#ifndef EDITOR_FRAME_HPP
#define EDITOR_FRAME_HPP

#include <wx/wx.h>

class EditorApp;

wxDECLARE_APP(EditorApp);

class EditorFrame : public wxFrame
{
public:
    enum MenuCommands
    {
        ID_IMPORT,
    };
    EditorFrame();
private:
    void OnClose(wxCommandEvent& event);
    void OnImport(wxCommandEvent& event);
    void OnExit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
    
    wxDECLARE_EVENT_TABLE();
};

#endif