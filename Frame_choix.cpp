#include <wx/wx.h>
#include "Frame_choix.h"
#include "Frame_hills.h"
#include "Frame_rsa.h"

Frame_choix::Frame_choix(): wxFrame(NULL, wxID_ANY,_T("Encryption"),wxDefaultPosition,wxSize(300,220))
{
    wxPanel         *fenetre					= new wxPanel(this); // un "panel" est la fenètre en elle même
    wxBoxSizer      *contenu_fenetre_sans_marge	= new wxBoxSizer(wxVERTICAL); // les boxSizer et StaticBoxSizer sont l'équivalent des "divs" en HTML
    wxBoxSizer 		*conteneur_centre			= new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer 		*conteneur_boutons			= new wxBoxSizer(wxVERTICAL);



    bouton_hills	= new wxButton(    fenetre, -1, _T("Chiffrement de Hills"));// Des champs d'input
    bouton_rsa  	= new wxButton(    fenetre, -1, _T("Chiffrement RSA"));

    wxStaticText	*copyright = new wxStaticText(fenetre, -1, wxT("by Augustin FL"));


    contenu_fenetre_sans_marge->Add(conteneur_centre, 1, wxALIGN_CENTER, 10);
    conteneur_centre->Add(conteneur_boutons, 1, wxALIGN_CENTER, 50);
    contenu_fenetre_sans_marge->Add(copyright,0,wxALIGN_CENTER_HORIZONTAL|wxALIGN_BOTTOM|wxBOTTOM,10);

    conteneur_boutons->Add(bouton_hills,1);
    conteneur_boutons->Add(bouton_rsa,1);


    bouton_rsa->MoveAfterInTabOrder(bouton_hills);//l'ordre des champs avec l'appui sur "tab"
    bouton_hills->MoveAfterInTabOrder(bouton_rsa);

    bouton_hills->Bind(wxEVT_BUTTON, 	  &Frame_choix::onClick_hills, this);
    bouton_rsa->Bind(wxEVT_BUTTON, 	  &Frame_choix::onClick_rsa, this);
    this->Bind(		  wxEVT_CLOSE_WINDOW, &Frame_choix::onClose, 		 this);

	fenetre->SetSizer(contenu_fenetre_sans_marge);

	this->SetMinSize(wxSize(300,220));
    this->Show();

    frame_hills=nullptr;
    frame_rsa=nullptr;
}



void Frame_choix::onClose(wxCloseEvent &evenement)
{
    if(evenement.CanVeto())
    {
        int reponse=wxMessageBox(_T("Voulez vous vraiment quitter?"), _T("Quitter"), wxYES_NO | wxCANCEL);
        if (reponse == wxNO)
        {
            evenement.Veto();
            return ;
        }
    }
    this->Destroy();
    if(frame_hills!=nullptr) frame_hills->Destroy();
    if(frame_rsa!=nullptr) frame_rsa->Destroy();
}

void Frame_choix::onClick_hills(wxCommandEvent &evenement)
{
    if(frame_hills!=nullptr) frame_hills->Destroy();
    frame_hills=new Frame_hills();
}

void Frame_choix::onClick_rsa(wxCommandEvent &evenement)
{
     if(frame_rsa!=nullptr)frame_rsa->Destroy();
     frame_rsa=new Frame_rsa();
}
