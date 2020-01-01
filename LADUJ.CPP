//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "wspolne.h"
#include "laduj.h"
#include <Filectrl.hpp>
//#include <sysutils.h>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm3 *Form3;
AnsiString Filename="domyslny";
//---------------------------------------------------------------------------
__fastcall TForm3::TForm3(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TForm3::BitBtn2Click(TObject *Sender)
{
Close();
}
//---------------------------------------------------------------------------



void init()
{
  if (!DirectoryExists(KATALOG))
    CreateDir(KATALOG);
  Form3->ListBox1->Items->Clear();
  TSearchRec sr;
  ChDir(KATALOG);
  if (FindFirst("*.puz", faAnyFile, sr) == 0)

  {
    do
    {
      if ((sr.Attr & faDirectory) != sr.Attr)
        Form3->ListBox1->Items->Add(ExtractFileName(sr.Name));
    } while (FindNext(sr) == 0);
    FindClose(sr);
  }

   ChDir("..");
}

void __fastcall TForm3::FormActivate(TObject *Sender)
{
 init();
 Filename = "";
  Edit1->Text="";
}
//---------------------------------------------------------------------------




void __fastcall TForm3::BitBtn1Click(TObject *Sender)
{
 Filename = Edit1->Text;
 Close();        
}
//---------------------------------------------------------------------------

void __fastcall TForm3::ListBox1Click(TObject *Sender)
{
 Edit1->Text = ListBox1->Items->Strings[ListBox1->ItemIndex];
}
//---------------------------------------------------------------------------



