//---------------------------------------------------------------------------

#include <vcl.h>
#include "wspolne.h"
#pragma hdrstop

#include "zapisz.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm2 *Form2;
AnsiString FileName;
//---------------------------------------------------------------------------
__fastcall TForm2::TForm2(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TForm2::BitBtn2Click(TObject *Sender)
{
 Close();         
}
//---------------------------------------------------------------------------


void init2()
{
  if (!DirectoryExists(KATALOG))
    CreateDir(KATALOG);
  Form2->ListBox1->Items->Clear();
  TSearchRec sr;
  ChDir(KATALOG);
  if (FindFirst("*.puz", faAnyFile, sr) == 0)

  {
    do
    {
      if ((sr.Attr & faDirectory) != sr.Attr)
        Form2->ListBox1->Items->Add(ExtractFileName(sr.Name));
    } while (FindNext(sr) == 0);
    FindClose(sr);
  }

   ChDir("..");
}


void __fastcall TForm2::FormActivate(TObject *Sender)
{
 init2();
 FileName = "";
 Edit1->Text="";
}
//---------------------------------------------------------------------------

void __fastcall TForm2::BitBtn1Click(TObject *Sender)
{
 FileName = Edit1->Text;
 Close();
}
//---------------------------------------------------------------------------

void __fastcall TForm2::ListBox1Click(TObject *Sender)
{
Edit1->Text = ListBox1->Items->Strings[ListBox1->ItemIndex];        
}
//---------------------------------------------------------------------------



