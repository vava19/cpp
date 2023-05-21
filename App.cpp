#include "App.hpp"
#include "mainFrame.hpp"
#include <wx/wx.h> 


wxIMPLEMENT_APP(App); // wxwidgit must know which class is our main class for application

   bool App::OnInit() {
        MainFrame* mainFrame = new MainFrame("hewAsciConvert");     
        mainFrame->SetClientSize(700, 700);
        mainFrame-> Center();
        // mainFrame->SetBackgroundColour(wxColour(50, 80, 120));
        mainFrame->Show();  
        return true; 

    };
