//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "mainintro.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
Tintro *intro;
//---------------------------------------------------------------------------
__fastcall Tintro::Tintro(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall Tintro::FormActivate(TObject *Sender)
{
static bool show = true;
if(show) {
 MediaPlayer1->FileName = "intro.avi";
 MediaPlayer1->Open();
intro->Left = 0;
intro->Top = 0;
intro->Width = Screen->Width;
intro->Height = Screen->Height;
MediaPlayer1->DisplayRect = Rect(0, 0, intro->Width, intro->Height);

 MediaPlayer1->Play();
 Timer1->Enabled = true;
 show = false;
  }
}
//---------------------------------------------------------------------------

void __fastcall Tintro::FormKeyPress(TObject *Sender, char &Key)
{
//MediaPlayer1->Stop();
MediaPlayer1->Close();

intro->Close();
}
//---------------------------------------------------------------------------
void __fastcall Tintro::FormClick(TObject *Sender)
{
//MediaPlayer1->Stop();
MediaPlayer1->Close();


intro->Close();
}
//---------------------------------------------------------------------------


void __fastcall Tintro::Timer1Timer(TObject *Sender)
{
//MediaPlayer1->Stop();
MediaPlayer1->Close();

intro->Close();        
}
//---------------------------------------------------------------------------

