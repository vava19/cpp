#ifndef MAINFRAME_HPP
#define MAINFRAME_HPP

#include <wx/wx.h>
#include <wx/textctrl.h>


 class  MainFrame : public wxFrame 
 {

    // which methods gonna use
  public:
  MainFrame(const wxString& title);

   
   private:
// help function

// elements:
  wxPanel* panel = nullptr;
  wxTextCtrl* inputTxt;
  wxTextCtrl* inputTxtAsci;
  wxButton* btnSave = nullptr;
  wxButton* btnClear = nullptr;
  wxTextValidator* textValidator;
  wxButton* btnloadFile;
  wxString* text;



// methods:
void OntxtToHexa(wxCommandEvent& event);  // wxKeyEvent& evt
void convertToHexa(const wxString& text);
void convertToText(const wxString& hexToAsciia);
void OnKeyToHex(wxCommandEvent& evt);
void OnButtonDelete(wxCommandEvent& event);
void OnWindowsClosed(wxCloseEvent& event);

void saveInputToFile(const wxString&, const wxString&);
void OnButtonSave(wxCommandEvent& event);
//void readFileToString(wxCommandEvent& event);
// variables
void OnLoadButton(wxCommandEvent& event);


//for delete
int WriteInFile(std::string str, bool append);
void OnSaveButton(wxCommandEvent &event);
wxButton* saveButton;

 };


#endif  // MAINFRAME_HPP