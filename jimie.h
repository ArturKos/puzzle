//---------------------------------------------------------------------------

#ifndef jimieH
#define jimieH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
//---------------------------------------------------------------------------
class Timie : public TForm
{
__published:	// IDE-managed Components
        TEdit *Edit1;
        TBitBtn *BitBtn1;
        TListBox *ListBox1;
        TSpeedButton *SpeedButton1;
        void __fastcall BitBtn1Click(TObject *Sender);
        void __fastcall FormActivate(TObject *Sender);
        void __fastcall SpeedButton1Click(TObject *Sender);
        void __fastcall ListBox1Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall Timie(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE Timie *imie;
//---------------------------------------------------------------------------
#endif
