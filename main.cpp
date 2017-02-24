#include "main.h"
#include "Frame_choix.h"


IMPLEMENT_APP(App_Encryption);

bool App_Encryption::OnInit()
{
	Frame_choix* choix=new Frame_choix();
	choix->Show();//pour éviter un warning "unused variable"

    return true;
}


int App_Encryption::OnExit()
{
	return 0;
}
