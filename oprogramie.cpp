//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "oprogramie.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm5 *Form5;
//---------------------------------------------------------------------------
__fastcall TForm5::TForm5(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------


void __fastcall TForm5::SpeedButton1Click(TObject *Sender)
{
Form5->Close();
}
//---------------------------------------------------------------------------
void __fastcall TForm5::FormCanResize(TObject *Sender, int &NewWidth,
      int &NewHeight, bool &Resize)
{
Resize=false;        
}
//---------------------------------------------------------------------------
