#include "mainframe.hpp"
#include <wx/wx.h>
#include <iostream>
#include <sstream>
#include <vector>
#include <fstream> 
#include <filesystem>
#include <wx/string.h>
#include <wx/spinctrl.h>




MainFrame::MainFrame(const wxString& title) : wxFrame(nullptr, wxID_ANY, title) {
  wxPanel* panel = new wxPanel(this);

  wxButton* button = new wxButton(panel, wxID_ANY, "GUI", wxPoint(150, 50),
                                  wxSize(100, 35));
  wxCheckBox* check_box = new wxCheckBox(panel, wxID_ANY, "Checkbox",  wxPoint(550, 55));
   wxStaticText* label = new wxStaticText(panel, wxID_ANY, "this is static", wxPoint (550,150));
  wxTextCtrl* text = new wxTextCtrl(panel, wxID_ANY," some text goes heere", wxPoint(120, 120), wxSize(200, 50),wxTE_PASSWORD);
  wxTextCtrl* text2 = new wxTextCtrl(panel, wxID_ANY," ohne passwort", wxPoint(160, 170), wxSize(100, 35));
  wxSlider* slider = new wxSlider(panel, wxID_ANY, 25, 0,100, wxPoint(20, 200), wxSize(-1, 200), wxSL_VALUE_LABEL);  // 200 od gore na dole  val, min, max
  wxGauge* gauge = new wxGauge(panel, wxID_ANY,  100, wxPoint(500, 200), wxSize(200, 90));   // wxSL_VERTICAL
    gauge->SetValue(75);
      
      // array of strings  = choices,  MainFrame is already in the loop
      wxArrayString choices;
      choices.Add("Alvin");
      choices.Add("Fabi");
      choices.Add("Mihi");
      choices.Add("Santa");
      
       wxChoice*  choice = new wxChoice(panel, wxID_ANY, wxPoint(60, 250), wxSize(100, -1), choices);  // 250 is von oben nach unten
       choice->Select(2);
    // wxSpinCtrl* spin = new wxSpinCtrl(panel,wxID_ANY, "", wxPoint(60, 300));
     wxListBox* list = new wxListBox(panel, wxID_ANY, wxPoint(200,400), wxSize(100, -1), choices);
     wxRadioBox* radiobox = new wxRadioBox(panel, wxID_ANY,  "radio  box", wxPoint(60, 500), wxDefaultSize, choices);

//CreateStatusBar();
wxStatusBar* statusBar=CreateStatusBar();
statusBar->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_3DFACE));   // nasao
statusBar->SetDoubleBuffered(true);   // ovo je kad imamo flickering
    

     button->Bind(wxEVT_BUTTON, &MainFrame::OnButtonClick, this);  // same like in table, but with &
     slider->Bind(wxEVT_SLIDER, &MainFrame::OnSliderChanged, this);
     text->Bind(wxEVT_TEXT, &MainFrame::OnTextChanged, this);
     panel->Bind(wxEVT_LEFT_DOWN, &MainFrame::OnMouseEvent, this);  // (mosue event type) event tag + moouse event method
    panel->Bind(wxEVT_MOTION, &MainFrame::OnMouseEvent, this);   // this is for mouse movement
    button->Bind(wxEVT_MOTION, &MainFrame::OnMouseEvent, this);   // now x y axis funktioneirt auch on button), 
     panel->Bind(wxEVT_KEY_DOWN, &MainFrame::OnKeyEvent, this);
      
  }


  void MainFrame::OnButtonClick(wxCommandEvent& event) {
    wxLogStatus("Button Click Yoo");
  }

  void MainFrame::OnSliderChanged(wxCommandEvent& event) {
    wxString str = wxString::Format("Slider value: %d", event.GetInt());
    wxLogStatus(str);
  }

  void MainFrame::OnTextChanged(wxCommandEvent& event) {
    wxString str = wxString::Format("Text: %s",event.GetString());
    wxLogStatus(str);
  }

  void MainFrame::OnMouseEvent(wxMouseEvent& event) {
    wxPoint mousePos = event.GetPosition();
    wxString message = wxString::Format("Mouse geht (x=%d y=%d)", mousePos.x, mousePos.y);  
    wxLogStatus(message);   //   moza pocetak upisati poruku: "mouse on click"  -- to check if works
  }

  void MainFrame::OnKeyEvent(wxKeyEvent& event) {   // now is blocked
    wxChar keyChar = event.GetUnicodeKey();  // just for printable chracters (no - caps Lock)  

    if(keyChar ==   WXK_NONE) {   // if entered  z.B tab  , that is none = null so  give me integer than
        int keyCode = event.GetKeyCode();
        wxLogStatus("Key Event %d", keyCode); // keyCode == integer
    }
    else {
           wxLogStatus("key  event: %c", keyChar);
    }
      
  }



//   -------------------------  AsciHex converter  ---------------------
MainFrame::MainFrame(const wxString &title)
    : wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition, wxDefaultSize,
              wxDEFAULT_FRAME_STYLE & ~wxRESIZE_BORDER) {
panel = new wxPanel(this);

  textInput1 = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(10, 20), wxSize(100,100));
  textInput1->Bind(wxEVT_CHAR, &MainFrame::OnTextInput1KeyDown, this);
  textInput2 = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(10, 150), wxSize(100,100));
  textInput2->Bind(wxEVT_CHAR, &MainFrame::OnTextInput2KeyDown, this);
  clearButton = new wxButton(panel, wxID_ANY, "CLEAR", wxPoint(140, 400), wxSize(85, 35));
  clearButton->Bind(wxEVT_BUTTON, &MainFrame::OnClearButton, this);
  saveButton = new wxButton(panel, wxID_ANY, "SAVE", wxPoint(20, 400), wxSize(80, 35));
  saveButton->Bind(wxEVT_BUTTON, &MainFrame::OnSaveButton, this);
  loadButton = new wxButton(panel, wxID_ANY, "LOAD", wxPoint(50, 400), wxSize(80,35));
  loadButton->Bind(wxEVT_BUTTON, &MainFrame::OnLoadButton, this);
}



int MainFrame::WriteInFile(std::string str, bool append) {
  std::ofstream myfile;
  if(append) {
    myfile.open("data.txt", std::ofstream::out | std::ofstream::app); // appending
  } else {
    myfile.open("data.txt", std::ofstream::out);
  }

  if(myfile.is_open()){
      myfile << str << std::endl;
      myfile.close();
  } else {
      std::cerr << "Unable to open file" << std::endl;
      return -1;
  }
  return 0;
}

void MainFrame::OnSaveButton(wxCommandEvent& event) {
  if(textInput1->GetValue().ToStdString() != "") {
    std::string text1 = textInput1->GetValue().ToStdString();
    std::string text2 = textInput2->GetValue().ToStdString();
    std::vector<std::string> text1v;
    std::vector<std::string> text2v;
    text1v.push_back(text1);
    text2v.push_back(text2);
    
    // erase data and write ascii
    for(auto& e : text1v) {WriteInFile(e, false);}  //kod obicnog texta nema append
    
    // append hex
    for(auto& e : text2v) {WriteInFile(e, true);}
  }
}

void MainFrame::OnLoadButton(wxCommandEvent& event) {
  std::ifstream myfile;
  std::string str, ascii, hex;  //str -> store one line
  myfile.open("data.txt");
  if(myfile.is_open()){
    while(std::getline(myfile, str)) {  //getline() read line by line
      if(ascii == "") {
        ascii = str;
      } else {
        hex = str; 
      }
    }
    myfile.close();

    //  ASCII string is first line, hex 2nd
    textInput1->SetValue(ascii);
    textInput2->SetValue(hex);
  } else {
    std::cerr << "Unable to open file" << std::endl;
  }
}
  

void MainFrame::OnClearButton(wxCommandEvent& event) {
  textInput1->Clear();
  textInput2->Clear();
}

void MainFrame::OnTextInput1KeyDown(wxKeyEvent& key) {
  if (key.GetUnicodeKey() == 8) {
    wxString hexStr = textInput1->GetValue();
    if(!hexStr.IsEmpty()) {
      hexStr.RemoveLast();
      textInput1->SetValue(hexStr);
    }
  } else {
    std::string keyStr(1, static_cast<char>(key.GetUnicodeKey()));
    textInput1->AppendText(keyStr);
  }
}

void MainFrame::OnTextInput2KeyDown(wxKeyEvent& key) {
  if (key.GetUnicodeKey() == 8) {
    wxString hexStr = textInput2->GetValue();
    if(!hexStr.IsEmpty()) {
      hexStr.RemoveLast();
      textInput2->SetValue(hexStr);
    }
  } else {
    std::string keyStr(1, static_cast<char>(key.GetUnicodeKey()));
    textInput2->AppendText(keyStr);
  }
}