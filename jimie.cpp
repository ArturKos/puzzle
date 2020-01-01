//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "jimie.h"
#include "wspolne.h"
#include <iostream.h>
#include <fstream.h>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
Timie *imie;
//---------------------------------------------------------------------------
__fastcall Timie::Timie(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall Timie::BitBtn1Click(TObject *Sender)
{
if(Edit1->Text!="")Close();
}
//---------------------------------------------------------------------------
void __fastcall Timie::FormActivate(TObject *Sender)
{
Edit1->Text=""; ListBox1->Clear();
  TSearchRec sr;
  if (FindFirst("*.gra", faAnyFile, sr) == 0)

  {
    do
    {
      if ((sr.Attr & faDirectory) != sr.Attr)
       {
        sr.Name.SetLength(sr.Name.Length()-4);
        ListBox1->Items->Add(ExtractFileName(sr.Name));
        }
    } while (FindNext(sr) == 0);
    FindClose(sr);
  }

}
//---------------------------------------------------------------------------


void __fastcall Timie::SpeedButton1Click(TObject *Sender)
{
 if(Edit1->Text=="") return;
 unsigned char RYSUNKI[LRYS];
 memset(RYSUNKI,1,sizeof RYSUNKI);
  AnsiString s = Edit1->Text;
  s+=".gra";
  ofstream out(s.c_str(),ios::out | ios::binary);
  if(out){
  out.put(1);
  out.write((unsigned char *)RYSUNKI,sizeof RYSUNKI);
 Close(); }
}
//---------------------------------------------------------------------------


void __fastcall Timie::ListBox1Click(TObject *Sender)
{
 Edit1->Text = ListBox1->Items->Strings[ListBox1->ItemIndex];
 BitBtn1->Enabled=true;    
}
//---------------------------------------------------------------------------

