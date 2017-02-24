#ifndef HEADERS_INCLUS_HILLS

	#define HEADERS_INCLUS_HILLS
	#include <wx/wx.h>

	class Frame_hills: public wxFrame
	{
		protected:
			wxButton *bouton_inverser_matrice,*bouton_inverser_donnees;
            wxTextCtrl *matrice_1_1,*matrice_1_2,*matrice_2_1,*matrice_2_2,*input_texte_a_chifrer,*input_resultat;

		public:
			Frame_hills();
			virtual ~Frame_hills(){};
            void onClose(wxCloseEvent &evenement);
			void onQuit(wxCommandEvent &evenement);
			void onChange_matrice(wxCommandEvent &evenement);
			void onChange_data(wxCommandEvent &evenement);
            void inverser_matrice(wxCommandEvent &evenement);
            void inverser_data(wxCommandEvent &evenement);

	};

#endif
