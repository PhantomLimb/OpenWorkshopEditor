#include "EditorFrame.hpp"
#include "EditorApp.hpp"
#include "EditorGLCanvas.hpp"
#include "FileImporter.hpp"

wxBEGIN_EVENT_TABLE(EditorFrame, wxFrame)
    EVT_MENU(ID_IMPORT, EditorFrame::OnImport)
    EVT_MENU(wxID_CLOSE, EditorFrame::OnClose)
wxEND_EVENT_TABLE()

void EditorFrame::OnAbout(wxCommandEvent& event)
{
    wxMessageBox(wxString("OpenWorkshopEditor ").append(APP_VERSION),
                 "About OpenWorkshopEditor", wxOK | wxICON_INFORMATION);
}

void EditorFrame::OnExit(wxCommandEvent& event)
{
    Close(true);
}


void EditorFrame::OnClose(wxCommandEvent& WXUNUSED(event))
{
    Close(true);
}

void EditorFrame::OnImport(wxCommandEvent& WXUNUSED(event))
{
    printf("Loading file...");
    FileImporter importer;
    wxFileDialog open_file_dialogue(this, "Import File", "", "",
                       "Breed files (*.dog, *.cat)|*.dog;*.cat", wxFD_OPEN|wxFD_FILE_MUST_EXIST);
    if (open_file_dialogue.ShowModal() == wxID_CANCEL)
    {
        return;
    }
    importer.import(open_file_dialogue.GetPath().char_str());
}

EditorFrame::EditorFrame() : wxFrame(NULL, wxMAXIMIZE | wxDEFAULT_FRAME_STYLE, "OpenWorkshopEditor", wxDefaultPosition, wxSize(960,690))
{
    wxMenu *menuFile = new wxMenu;
    wxMenuItem * import_button = new wxMenuItem(menuFile, ID_IMPORT, "Import File", wxEmptyString, wxITEM_NORMAL, NULL);
    menuFile->Append(import_button);
    menuFile->Append(wxID_EXIT);
    
    wxMenu *menuHelp = new wxMenu;
    menuHelp->Append(wxID_ABOUT);
    wxMenuBar *menuBar = new wxMenuBar;
    menuBar->Append(menuFile, "&File");
    menuBar->Append(menuHelp, "&Help");
    SetMenuBar( menuBar );
    CreateStatusBar();
    //Show(true);
    SetStatusText(wxString("OpenWorkshopEditor ").append(APP_VERSION));
    //Bind(wxEVT_MENU, &MyFrame::OnHello, this, ID_Hello);
    Bind(wxEVT_MENU, &EditorFrame::OnAbout, this, wxID_ABOUT);
    Bind(wxEVT_MENU, &EditorFrame::OnExit, this, wxID_EXIT);
}