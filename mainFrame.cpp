#include "mainFrame.hpp"
#include <wx/wx.h>
#include <wx/tokenzr.h>
#include <iostream>
#include <fstream>
#include <string>



 MainFrame::MainFrame(const wxString &title) : wxFrame(nullptr, wxID_ANY, title)
{

panel = new wxPanel(this,wxID_ANY);
panel->SetBackgroundColour(wxColor(173, 216, 230));

inputTxt = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(20,20), wxSize(580,250), wxTE_MULTILINE | wxTE_RICH);   
inputTxtAsci = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(20,300), wxSize(580,250), wxTE_MULTILINE | wxTE_RICH); 
btnSave = new wxButton(panel, wxID_ANY, "Save", wxPoint(20,580), wxSize(80,35));
btnClear = new wxButton(panel, wxID_ANY, "Clear", wxPoint(130,580), wxSize(80,35));
btnloadFile = new wxButton(panel, wxID_ANY, "Load File", wxPoint(250,580), wxSize(100,35));


inputTxt->Bind(wxEVT_TEXT, &MainFrame::OntxtToHexa, this ); //wxEVT_TEXT   wxEVT_KEY_DOWN
//inputTxtAsci->Bind(wxEVT_TEXT, &MainFrame::OnKeyToHex, this);
btnClear->Bind(wxEVT_BUTTON, &MainFrame::OnButtonDelete, this);
btnSave->Bind(wxEVT_BUTTON,&MainFrame::OnButtonSave, this);
btnloadFile->Bind(wxEVT_BUTTON,&MainFrame::OnLoadButton, this);

wxTextValidator textValidator(wxFILTER_INCLUDE_CHAR_LIST);
textValidator.SetCharIncludes("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789 []=-()*&^%$#@!~';.,<>?/"":+_");
inputTxt->SetValidator(textValidator);


wxTextValidator hexValidator(wxFILTER_INCLUDE_CHAR_LIST);
hexValidator.SetCharIncludes("0123456789ABCDEFabcdef \n");
inputTxtAsci->SetValidator(hexValidator);
    
}

// convert text to hexa
void MainFrame::OntxtToHexa(wxCommandEvent& evt) // wxKeyEvent &evt
{
   wxString text = inputTxt->GetValue();
     convertToHexa(text);                
}

// hex to asci code (text)
void MainFrame::OnKeyToHex(wxCommandEvent& evt) // wxKeyEvent &evt
{
   //wxString text = inputTxt->GetValue();
    wxString hexToAscii = inputTxtAsci->GetValue().ToStdString();
    inputTxtAsci->SetValue(hexToAscii);
}


void MainFrame::convertToHexa(const wxString& text)
{
    wxString asciiText;
    for (wxChar ch : text)
    {
        wxString hexValue = wxString::Format("%02X", static_cast<int>(ch));
        asciiText += hexValue + " ";
    }
    std::cout << "ASCII Hex: " << asciiText << std::endl;
   inputTxtAsci->SetValue(asciiText);
}

// --- convert to text
void MainFrame::convertToText(const wxString& hexToAscii)
{
    wxString text;
    wxStringTokenizer tokenizer(hexToAscii, " ");
    wxString token;
    
    while (tokenizer.HasMoreTokens())
    {
        token = tokenizer.GetNextToken();
        
        long hexValue;
        if (token.ToLong(&hexValue, 16))
        {
            wxString character(static_cast<wxChar>(hexValue));
            text += character;      
        }   
    }
     inputTxt->SetValue(text);
    // inputTxt->SetFocus();
     
    std::cout << "Text: " << text << std::endl;
}


void MainFrame::OnButtonDelete(wxCommandEvent& event)
{
   if(inputTxt->IsEmpty() && inputTxtAsci->IsEmpty()) {
      return;
   }
     wxMessageDialog dialog(this, "Are you sure", "Delete All", wxYES_NO | wxCANCEL);
     int result = dialog.ShowModal();

     if (result == wxID_YES) {
        inputTxt->Clear();
        inputTxtAsci->Clear();
     }
}


void MainFrame::saveInputToFile(const wxString& filename, const wxString& content)
{
    std::ofstream file(filename); //  .ToStdString()
    if (file.is_open())
    {
        file << content;
        file.close();
        std::cout << "Input saved to file: " << filename << std::endl;
    }
    else
    {
        std::cerr << "Unable to open file: " << filename << std::endl;
    }
}


void MainFrame::OnButtonSave(wxCommandEvent& event)
{
    wxString content = inputTxt->GetValue();
    std::string filename = "txtToHex.txt";
    saveInputToFile(filename, content);
   
}


void MainFrame::OnLoadButton(wxCommandEvent& event) {
  std::ifstream file;
  std::string str, ascii, hex;
  file.open("txtToHex.txt");
  if(file.is_open()){
    while(std::getline(file, str)) {
      if(ascii == "") {
        ascii = str;
      } else {
           hex = str; 
        }
    }
    file.close();

    inputTxt->SetValue(ascii);
    inputTxtAsci->SetValue(hex);

  } else {
    std::cerr << "cannot open f." << std::endl;
  }
}


