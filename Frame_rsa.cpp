#include <wx/wx.h>
#include <gmp.h>
#include "Frame_rsa.h"
#include "validator.h"


Frame_rsa::Frame_rsa(): wxFrame(NULL, wxID_ANY,_T("RSA"),wxDefaultPosition,wxSize(550,400))
{

    wxPanel         *fenetre					= new wxPanel(this); // un "panel" est la fenètre en elle même
    wxBoxSizer      *contenu_fenetre_sans_marge	= new wxBoxSizer(wxVERTICAL); //
    wxBoxSizer      *contenu_partie_nombres 	= new wxBoxSizer(wxHORIZONTAL);
    wxStaticBoxSizer*conteneur_chiffrement 	    = new wxStaticBoxSizer(wxVERTICAL,fenetre,"Texte a chiffrer/dechiffrer");
    wxFlexGridSizer *conteneur_chiffrement2     = new wxFlexGridSizer(3,0,5);

    wxStaticBoxSizer*conteneur_choix_nombres   	= new wxStaticBoxSizer(wxVERTICAL,fenetre,"Choix des nombres P Q et E");
    wxStaticBoxSizer*conteneur_autres_nombres   = new wxStaticBoxSizer(wxVERTICAL,fenetre,"Autres nombres");

    wxFlexGridSizer *contenur_grille_PQE        = new wxFlexGridSizer(2,0,5);
    wxFlexGridSizer *contenur_grille_autres     = new wxFlexGridSizer(2,0,5);

    wxStaticText	*texte_explicatif_p			= new wxStaticText(fenetre, -1, wxT("P = "));
    wxStaticText	*texte_explicatif_q			= new wxStaticText(fenetre, -1, wxT("Q = "));
    wxStaticText	*texte_explicatif_e			= new wxStaticText(fenetre, -1, wxT("E = "));
    wxStaticText	*texte_explicatif_n			= new wxStaticText(fenetre, -1, wxT("N = "));
    wxStaticText	*texte_explicatif_d			= new wxStaticText(fenetre, -1, wxT("D = "));
    wxStaticText	*texte_explicatif_phi		= new wxStaticText(fenetre, -1, wxT("φ = "));
    wxStaticText	*texte_explicatif2_e		= new wxStaticText(fenetre, -1, wxT("P et Q doivent être premiers entre eux\nE doit être un nombre premier avec φ"));
    wxStaticText	*advised_values     		= new wxStaticText(fenetre, -1, wxT("Valeurs conseillées : P=11, Q=43, E=17"));
    wxStaticText	*texte_warning_N		= new wxStaticText(fenetre, -1, wxT("Attention : Les codes ASCII des lettres entrées doivent être inférieur à N !\nSi N>512, les lettres du résultat peuvent être erronées à cause de la transformation en ASCII ! "));
    wxStaticText	*texte_chiffrement1		= new wxStaticText(fenetre, -1, wxT(""));
    wxStaticText	*texte_chiffrement2		= new wxStaticText(fenetre, -1, wxT("Texte avant opération (ASCII) : "));
    wxStaticText	*texte_chiffrement3		= new wxStaticText(fenetre, -1, wxT("Texte avant opération (nombres) : "));
    wxStaticText	*texte_chiffrement4		= new wxStaticText(fenetre, -1, wxT("Texte après opération (nombres) : "));
    wxStaticText	*texte_chiffrement5		= new wxStaticText(fenetre, -1, wxT("Texte après opération (ASCII) : "));


    wxStaticText	*texte_chiffrer	    	= new wxStaticText(fenetre, -1, wxT("Chiffrer : "));
    wxStaticText	*texte_dechiffrer		= new wxStaticText(fenetre, -1, wxT("Déchiffrer : "));

    input_p		= new wxTextCtrl(  fenetre, -1, _T(""),wxDefaultPosition,wxDefaultSize,0,wxTextValidator(wxFILTER_DIGITS));
    input_q		= new wxTextCtrl(  fenetre, -1, _T(""),wxDefaultPosition,wxDefaultSize,0,wxTextValidator(wxFILTER_DIGITS));
    input_e		= new wxTextCtrl(  fenetre, -1, _T(""),wxDefaultPosition,wxDefaultSize,0,wxTextValidator(wxFILTER_DIGITS));

    input_phi = new wxTextCtrl(  fenetre, -1, _T(""),wxDefaultPosition,wxDefaultSize,wxTE_READONLY);
    input_n	  = new wxTextCtrl(  fenetre, -1, _T(""),wxDefaultPosition,wxDefaultSize,wxTE_READONLY);
    input_d	  = new wxTextCtrl(  fenetre, -1, _T(""),wxDefaultPosition,wxDefaultSize,wxTE_READONLY);


    input_texte_a_chiffrer   = new wxTextCtrl(  fenetre, -1, _T(""),wxDefaultPosition,wxDefaultSize,0,wxTextRegexpValidator("[a-z]"));
    input_resultat_chiffrer	= new wxTextCtrl(  fenetre, -1, _T(""),wxDefaultPosition,wxDefaultSize,wxTE_READONLY);
    input_resultat_nombres_chiffrer	= new wxTextCtrl(  fenetre, -1, _T(""),wxDefaultPosition,wxDefaultSize,wxTE_READONLY);

    input_texte_a_dechiffrer = new wxTextCtrl(  fenetre, -1, _T(""),wxDefaultPosition,wxDefaultSize,0,wxTextRegexpValidator("[a-z]"));
    input_resultat_dechiffrer= new wxTextCtrl(  fenetre, -1, _T(""),wxDefaultPosition,wxDefaultSize,wxTE_READONLY);
    input_resultat_nombres_dechiffrer	= new wxTextCtrl(  fenetre, -1, _T(""),wxDefaultPosition,wxDefaultSize,wxTE_READONLY);

    input_nombres_a_dechiffrer	= new wxTextCtrl(  fenetre, -1, _T(""),wxDefaultPosition,wxDefaultSize,wxTE_READONLY);
    input_nombres_a_chiffrer	= new wxTextCtrl(  fenetre, -1, _T(""),wxDefaultPosition,wxDefaultSize,wxTE_READONLY);

    contenu_fenetre_sans_marge->Add(contenu_partie_nombres, 1, wxALIGN_CENTER|wxALL,10);
    contenu_fenetre_sans_marge->Add(conteneur_chiffrement, 1, wxALIGN_CENTER|wxALL,10);

    contenu_partie_nombres->Add(conteneur_choix_nombres, wxALIGN_CENTER,10);
    contenu_partie_nombres->Add(conteneur_autres_nombres,wxALIGN_CENTER,10);

    conteneur_choix_nombres->Add(contenur_grille_PQE,1);
    conteneur_choix_nombres->Add(texte_explicatif2_e,0,wxALIGN_BOTTOM);


    contenur_grille_PQE->Add(texte_explicatif_p);
    contenur_grille_PQE->Add(input_p);
    contenur_grille_PQE->Add(texte_explicatif_q);
    contenur_grille_PQE->Add(input_q);
    contenur_grille_PQE->Add(texte_explicatif_e);
    contenur_grille_PQE->Add(input_e);

    conteneur_autres_nombres->Add(contenur_grille_autres,1);
    conteneur_autres_nombres->Add(advised_values,0,wxTOP,5);

    contenur_grille_autres->Add(texte_explicatif_n);
    contenur_grille_autres->Add(input_n);
    contenur_grille_autres->Add(texte_explicatif_phi);
    contenur_grille_autres->Add(input_phi);
    contenur_grille_autres->Add(texte_explicatif_d);
    contenur_grille_autres->Add(input_d);

    conteneur_chiffrement->Add(conteneur_chiffrement2,0,wxALIGN_CENTER);
    conteneur_chiffrement->Add(texte_warning_N,0,wxTOP,5);

    conteneur_chiffrement2->Add(texte_chiffrement1);
    conteneur_chiffrement2->Add(texte_chiffrer);
    conteneur_chiffrement2->Add(texte_dechiffrer);

    conteneur_chiffrement2->Add(texte_chiffrement2);
    conteneur_chiffrement2->Add(input_texte_a_chiffrer);
    conteneur_chiffrement2->Add(input_texte_a_dechiffrer);


    conteneur_chiffrement2->Add(texte_chiffrement3);
    conteneur_chiffrement2->Add(input_nombres_a_chiffrer);
    conteneur_chiffrement2->Add(input_nombres_a_dechiffrer);


    conteneur_chiffrement2->Add(texte_chiffrement4);
    conteneur_chiffrement2->Add(input_resultat_nombres_chiffrer);
    conteneur_chiffrement2->Add(input_resultat_nombres_dechiffrer);

    conteneur_chiffrement2->Add(texte_chiffrement5);
    conteneur_chiffrement2->Add(input_resultat_chiffrer);
    conteneur_chiffrement2->Add(input_resultat_dechiffrer);


    input_p->Bind(wxEVT_TEXT,		  &Frame_rsa::onChange_pqe, this);
    input_q->Bind(wxEVT_TEXT,		  &Frame_rsa::onChange_pqe, this);
    input_e->Bind(wxEVT_TEXT,		  &Frame_rsa::onChange_pqe, this);
    input_texte_a_chiffrer->Bind(wxEVT_TEXT,		  &Frame_rsa::onChange_data_encrypt, this);
    input_texte_a_dechiffrer->Bind(wxEVT_TEXT,		  &Frame_rsa::onChange_data_decrypt, this);
    this->Bind(		  wxEVT_CLOSE_WINDOW, &Frame_rsa::onClose, 		 this);

	fenetre->SetSizer(contenu_fenetre_sans_marge);

	this->SetMinSize(wxSize(550,400));
    this->Show();

}

void Frame_rsa::onChange_pqe(wxCommandEvent &evenement)
{
   mpz_t p,q,e,n,phi,d;
   char *n_str=nullptr,*phi_str=nullptr,*d_str=nullptr;

    mpz_init_set_str(p,input_p->GetValue().ToStdString().c_str(),10);
    mpz_init_set_str(q,input_q->GetValue().ToStdString().c_str(),10);
    mpz_init_set_str(e,input_e->GetValue().ToStdString().c_str(),10);

    mpz_init(phi);
    mpz_init(n);
    mpz_init(d);


    if(!input_p->IsEmpty() && !input_q->IsEmpty() && this->algo_euclide_etendu(p,q,d)==1)
    {
		mpz_mul(n,p,q);// N=P*Q

		mpz_sub_ui(p,p,1);
		mpz_sub_ui(q,q,1);

		mpz_mul(phi,p,q);

		mpz_add_ui(p,p,1);
		mpz_add_ui(q,q,1);

		phi_str=mpz_get_str(nullptr,10,phi);
		n_str=mpz_get_str(nullptr,10,n);

        input_n->SetValue(wxString::Format(wxT("%s"),n_str));
        input_phi->SetValue(wxString::Format(wxT("%s"),phi_str));

        this->algo_euclide_etendu(e,phi,d);

        if(!input_e->IsEmpty() && this->algo_euclide_etendu(e,phi,d)==1)
        {
            this->corrige_u_besout(d,phi);

            d_str=mpz_get_str(nullptr,10,d);
            input_d->SetValue(wxString::Format(wxT("%s"),d_str));


            this->onChange_data_decrypt(*new wxCommandEvent());
            this->onChange_data_encrypt(*new wxCommandEvent());

        }
        else
        {
            input_d->SetValue("");
            input_resultat_chiffrer->SetValue("");
            input_resultat_dechiffrer->SetValue("");
            input_resultat_nombres_dechiffrer->SetValue("");
            input_resultat_nombres_chiffrer->SetValue("");
            input_nombres_a_chiffrer->SetValue("");
            input_nombres_a_dechiffrer->SetValue("");
        }

    }
    else
    {
        input_n->SetValue("");
        input_d->SetValue("");
        input_phi->SetValue("");
        input_resultat_chiffrer->SetValue("");
        input_resultat_dechiffrer->SetValue("");
        input_resultat_nombres_dechiffrer->SetValue("");
        input_resultat_nombres_chiffrer->SetValue("");
        input_nombres_a_chiffrer->SetValue("");
        input_nombres_a_dechiffrer->SetValue("");
    }
}

void Frame_rsa::onChange_data_encrypt(wxCommandEvent &evenement)
{

    if(!input_d->IsEmpty())
    {
        mpz_t e,n;

        mpz_init_set_str(e,input_e->GetValue().ToStdString().c_str(),10);
        mpz_init_set_str(n,input_n->GetValue().ToStdString().c_str(),10);

        std::wstring original_chain=input_texte_a_chiffrer->GetValue().ToStdWstring();
        std::string string_chain="";
        std::string original_number_chain="";
        mpz_t x;

        for(unsigned int i=0;i<original_chain.length();i++)
        {
            unsigned int number=static_cast<unsigned int>(original_chain[i]);

            mpz_init_set_ui(x,number);// pour chiffrer : x^e % n
			mpz_powm(x,x,e,n);
            original_chain[i]=mpz_get_ui(x);

            string_chain+=std::to_string(mpz_get_ui(x))+" ";
            original_number_chain+=std::to_string(number)+" ";

        }

        input_resultat_nombres_chiffrer->SetValue(wxString(string_chain));
        input_resultat_chiffrer->SetValue(wxString(original_chain));
        input_nombres_a_chiffrer->SetValue(wxString(original_number_chain));
    }
    else
    {
        input_resultat_chiffrer->SetValue("");
        input_resultat_nombres_chiffrer->SetValue("");
        input_nombres_a_chiffrer->SetValue("");
    }

}

void Frame_rsa::onChange_data_decrypt(wxCommandEvent &evenement)
{
 if(!input_d->IsEmpty())
    {
        mpz_t d,n;

        mpz_init_set_str(d,input_d->GetValue().ToStdString().c_str(),10);
        mpz_init_set_str(n,input_n->GetValue().ToStdString().c_str(),10);

        std::wstring original_chain=input_texte_a_dechiffrer->GetValue().ToStdWstring();
        std::string string_chain="";
        std::string original_number_chain="";
        mpz_t x;

        for(unsigned int i=0;i<original_chain.length();i++)
        {
            unsigned int number=static_cast<unsigned int>(original_chain[i]);

            mpz_init_set_ui(x,number);// pour dechiffrer : x^d % n
			mpz_powm(x,x,d,n);
            original_chain[i]=mpz_get_ui(x);

            string_chain+=std::to_string(mpz_get_ui(x))+" ";
            original_number_chain+=std::to_string(number)+" ";
        }

        input_resultat_dechiffrer->SetValue(wxString(original_chain));
        input_resultat_nombres_dechiffrer->SetValue(wxString(string_chain));
        input_nombres_a_dechiffrer->SetValue(wxString(original_number_chain));

    }
    else
    {
        input_resultat_dechiffrer->SetValue("");
        input_resultat_nombres_dechiffrer->SetValue("");
        input_nombres_a_dechiffrer->SetValue(wxString(""));
    }

}

void Frame_rsa::onClose(wxCloseEvent &evenement)
{
     this->Hide();
}



long Frame_rsa::algo_euclide_etendu(mpz_t a_cpy,mpz_t b_cpy,mpz_t u)
{
	// --------------------- ALGO EUCLIDE ETENDU
	//tiré depuis wikipedia.

	mpz_t a, b, v, x, y, c, d, q, r,s,q1,q2;

	mpz_init(q1);
	mpz_init(q2);
	mpz_init(s);
	mpz_init(c);
	mpz_init(d);
	mpz_init(q);
	mpz_init(u);
	mpz_init(r);
	mpz_init_set(a,a_cpy);
	mpz_init_set(b,b_cpy);

	mpz_init_set_si(u,1);
	mpz_init_set_si(v,0);

	mpz_init_set_si(x,0);
	mpz_init_set_si(y,1);


	while (mpz_cmp_si(b,0))//while b>0
	{
		mpz_mod(r,a,b);
		mpz_sub(s,a,r);
		mpz_div(q,s,b);
		mpz_set(c,u);
		mpz_set(d,v);
		mpz_set(u,x);
		mpz_set(v,y);

		mpz_mul(q1,q,x);
		mpz_mul(q2,q,y);
		mpz_sub(x,c,q1);
		mpz_sub(y,d,q2);
		mpz_set(a,b);
		mpz_set(b,r);
	}

    return mpz_get_ui(a);
}

void Frame_rsa::corrige_u_besout(mpz_t u, mpz_t b_cpy)
{
   /* RSA impose que 2 < u < b...
	 * donc si u < 2 ou u > b, on calcule l'inverse de u :p
	  on a a*(u - k*b) + b*(v + k*a) = 1 -> il suffit de faire varier k
	 */

    mpz_t b,k,kb;

    mpz_init(kb);
    mpz_init_set(b,b_cpy);

	if(mpz_cmp_si(u,2)<0)//if u<2
	{
        mpz_init_set_si(k,2);

		mpz_sub(k,k,u);
		mpz_mul_si(b,b,-1);

		mpz_fdiv_q(k, k, b);// k =(2-u)/-b

		mpz_mul_si(b,b,-1);
        mpz_mul(kb,k,b);
		mpz_sub(u,u,kb);
	}

	if(mpz_cmp(u,b)>0)
	{
		mpz_set(k,b);


		mpz_sub(k,k,u);
		mpz_mul_si(b,b,-1);

        mpz_fdiv_q(k, k, b);//k=(b-u)/-b

		mpz_mul_si(b,b,-1);
        mpz_mul(kb,k,b);
		mpz_sub(u,u,kb);
	}
}

