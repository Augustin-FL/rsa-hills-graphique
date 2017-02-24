#ifndef HEADERS_INCLUS_MAIN
	#define HEADERS_INCLUS_MAIN

	#include <wx/wx.h>

	class App_Encryption : public wxApp // correspond au "main"
	{
		public :
			virtual bool OnInit();
			virtual int OnExit();
	};
	DECLARE_APP(App_Encryption);



#endif
