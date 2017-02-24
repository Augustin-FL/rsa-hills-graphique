#ifndef HEADERS_INCLUS_CHOIX

	#define HEADERS_INCLUS_CHOIX
	#include <wx/wx.h>

    class Frame_hills;

	class Frame_choix: public wxFrame
	{
		protected:
			//Frame_login *parent;
            wxButton *bouton_hills, *bouton_rsa;
            wxWindow *frame_hills,*frame_rsa;

		public:
			Frame_choix();
			virtual ~Frame_choix(){};
            void onClose(wxCloseEvent &evenement);
			void onQuit(wxCommandEvent &evenement);
			void onClick_rsa(wxCommandEvent &evenement);
			void onClick_hills(wxCommandEvent &evenement);

	};

#endif
