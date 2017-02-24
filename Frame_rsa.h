#ifndef HEADERS_INCLUS_RSA

	#define HEADERS_INCLUS_RSA
	#include <wx/wx.h>
	#include <gmp.h>

	class Frame_rsa: public wxFrame
	{
		protected:
        wxTextCtrl *input_p,*input_q,*input_e,* input_phi,*input_n,*input_d,*input_texte_a_chiffrer,*input_texte_a_dechiffrer,*input_resultat_chiffrer,*input_resultat_dechiffrer,*input_resultat_nombres_chiffrer,*input_resultat_nombres_dechiffrer,*input_nombres_a_dechiffrer,*input_nombres_a_chiffrer;

		public:
			Frame_rsa();
			virtual ~Frame_rsa(){};
            void onClose(wxCloseEvent &evenement);
			void onQuit(wxCommandEvent &evenement);

            void onChange_pqe(wxCommandEvent &evenement);
            void onChange_data_encrypt(wxCommandEvent &evenement);
            void onChange_data_decrypt(wxCommandEvent &evenement);

            long algo_euclide_etendu(mpz_t a,mpz_t b,mpz_t u);
            void corrige_u_besout(mpz_t u, mpz_t b);

	};

#endif
