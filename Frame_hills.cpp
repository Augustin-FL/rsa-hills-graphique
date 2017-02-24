#include <wx/wx.h>
#include "Frame_hills.h"
#include "validator.h"


Frame_hills::Frame_hills(): wxFrame(NULL, wxID_ANY,_T("Hills"),wxDefaultPosition,wxSize(500,220))
{

    wxPanel         *fenetre					= new wxPanel(this); // un "panel" est la fenètre en elle même
    wxBoxSizer      *contenu_fenetre_sans_marge	= new wxBoxSizer(wxVERTICAL); //
    wxStaticBoxSizer*conteneur_zone_matrice    	= new wxStaticBoxSizer(wxHORIZONTAL,fenetre,"Matrice 2x2");
    wxFlexGridSizer *contenur_matrice           = new wxFlexGridSizer(2,0,5);

    wxStaticBoxSizer*conteneur_chiffrement 	    = new wxStaticBoxSizer(wxVERTICAL,fenetre,"Texte a chiffrer/dechiffrer");

    bouton_inverser_matrice	= new wxButton( fenetre, -1, _T("Inverser la matrice"));// Des champs d'input
    bouton_inverser_donnees = new wxButton(    fenetre, -1, _T("Inverser"));

    matrice_1_1		= new wxTextCtrl(  fenetre, -1, _T(""),wxDefaultPosition,wxSize(50,-1),0,wxTextValidator(wxFILTER_DIGITS));
    matrice_1_2		= new wxTextCtrl(  fenetre, -1, _T(""),wxDefaultPosition,wxSize(50,-1),0,wxTextValidator(wxFILTER_DIGITS));
    matrice_2_1		= new wxTextCtrl(  fenetre, -1, _T(""),wxDefaultPosition,wxSize(50,-1),0,wxTextValidator(wxFILTER_DIGITS));
    matrice_2_2		= new wxTextCtrl(  fenetre, -1, _T(""),wxDefaultPosition,wxSize(50,-1),0,wxTextValidator(wxFILTER_DIGITS));

    input_texte_a_chifrer= new wxTextCtrl(  fenetre, -1, _T(""),wxDefaultPosition,wxDefaultSize,0,wxTextRegexpValidator("[a-z]"));
    input_resultat		 = new wxTextCtrl(  fenetre, -1, _T(""),wxDefaultPosition,wxDefaultSize,wxTE_READONLY);


    contenu_fenetre_sans_marge->Add(conteneur_zone_matrice, 1, wxALIGN_CENTER);
    contenu_fenetre_sans_marge->Add(conteneur_chiffrement, 1, wxALIGN_CENTER);

    conteneur_zone_matrice->Add(contenur_matrice, 1);
    conteneur_zone_matrice->Add(bouton_inverser_matrice, 0 );

    contenur_matrice->Add(matrice_1_1);
    contenur_matrice->Add(matrice_1_2);
    contenur_matrice->Add(matrice_2_1);
    contenur_matrice->Add(matrice_2_2);

    conteneur_chiffrement->Add(input_texte_a_chifrer,0,wxALIGN_CENTER);
    conteneur_chiffrement->Add(bouton_inverser_donnees,0,wxALIGN_CENTER);
    conteneur_chiffrement->Add(input_resultat,0,wxALIGN_CENTER);


    bouton_inverser_matrice->Disable();

    bouton_inverser_matrice->Bind(wxEVT_BUTTON, 	  &Frame_hills::inverser_matrice, this);
    bouton_inverser_donnees->Bind(wxEVT_BUTTON, 	  &Frame_hills::inverser_data, this);
    matrice_1_1->Bind(wxEVT_TEXT,		  &Frame_hills::onChange_matrice, this);
    matrice_1_2->Bind(wxEVT_TEXT,		  &Frame_hills::onChange_matrice, this);
    matrice_2_1->Bind(wxEVT_TEXT,		  &Frame_hills::onChange_matrice, this);
    matrice_2_2->Bind(wxEVT_TEXT,		  &Frame_hills::onChange_matrice, this);

    input_texte_a_chifrer->Bind(  wxEVT_TEXT,		  &Frame_hills::onChange_data, 		 this);

    this->Bind(		  wxEVT_CLOSE_WINDOW, &Frame_hills::onClose, 		 this);

	fenetre->SetSizer(contenu_fenetre_sans_marge);

	this->SetMinSize(wxSize(500,220));
    this->Show();

}


void Frame_hills::onChange_matrice(wxCommandEvent &evenement)
{
  this->onChange_data(*new wxCommandEvent());
}

void Frame_hills::onChange_data(wxCommandEvent &evenement)
{
    int m_1_1=wxAtoi(matrice_1_1->GetValue()),
    m_1_2=wxAtoi(matrice_1_2->GetValue()),
    m_2_1=wxAtoi(matrice_2_1->GetValue()),
    m_2_2=wxAtoi(matrice_2_2->GetValue());

    std::string original_chain=std::string(input_texte_a_chifrer->GetValue().mbc_str()),new_chain="";

    for(unsigned int i=0; i<original_chain.length();i++)
    {
        if(original_chain[i]<'a' || original_chain[i]>'z')
        {
            if(original_chain[i]>='A' && original_chain[i]<='Z')
            {
                new_chain+=original_chain[i]+('a'-'A');
            }
        }
        else new_chain+=original_chain[i];
    }
    original_chain=new_chain;

    int resultat=m_1_1*m_2_2-m_2_1*m_1_2;//ab-cd a*d-b*c
    if(resultat>0 && resultat%2==1 && resultat%13!=0)
    {
        bouton_inverser_matrice->Enable();
    }
    else
    {
       bouton_inverser_matrice->Disable();
    }

    if(!matrice_1_1->IsEmpty() && !matrice_2_1->IsEmpty() && !matrice_2_1->IsEmpty() && !matrice_2_2->IsEmpty())
    {
        //secu
        if(original_chain.length()%2==1) original_chain+='a';


        for(unsigned int i=0; i<original_chain.length();i+=2)
        {
            int tmp1=original_chain[i]-97;
            int tmp2=original_chain[i+1]-97;

            original_chain[i]=(tmp1*m_1_1+tmp2*m_1_2)%26+97;
            original_chain[i+1]=(tmp1*m_2_1+tmp2*m_2_2)%26+97;
        }
        input_resultat->SetValue(wxString(original_chain));

    }
}

void Frame_hills::inverser_matrice(wxCommandEvent &evenement)
{
    int a=wxAtoi(matrice_1_1->GetValue()),
    b=wxAtoi(matrice_1_2->GetValue()),
    c=wxAtoi(matrice_2_1->GetValue()),
    d=wxAtoi(matrice_2_2->GetValue());

    int adbc=a*d-b*c,inverse_test[12] ={1, 3, 5, 7, 9, 11, 15, 17, 19, 21, 23, 25} , inverse=0;

    for(int i=0;i<13 && inverse==0;i++)
    {
        if(inverse_test[i]*adbc%26==1)
        {
            inverse=inverse_test[i];
        }
    }

    matrice_1_1->SetValue(wxString::Format(wxT("%i"),(d*inverse)%26));
    matrice_1_2->SetValue(wxString::Format(wxT("%i"),(-b*inverse+25*26)%26));
    matrice_2_1->SetValue(wxString::Format(wxT("%i"),(-c*inverse+25*26)%26));
    matrice_2_2->SetValue(wxString::Format(wxT("%i"),(a*inverse)%26));

    this->onChange_data(*new wxCommandEvent());
}


void Frame_hills::inverser_data(wxCommandEvent &evenement)
{
    input_texte_a_chifrer->SetValue(input_resultat->GetValue());
    this->onChange_data(*new wxCommandEvent());
}

void Frame_hills::onClose(wxCloseEvent &evenement)
{
    this->Hide();
}
