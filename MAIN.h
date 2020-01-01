//---------------------------------------------------------------------------

#ifndef mainH
#define mainH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
#include <Mask.hpp>
#include <Menus.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
        TMainMenu *Menu;
        TMenuItem *Gra1;
        TMenuItem *Nowa1;
        TMenuItem *Zapisz1;
        TMenuItem *aduj1;
        TMenuItem *Koniec1;
        TMenuItem *Najlepszewyniki1;
        TMenuItem *Poziomtrudnoci1;
        TMenuItem *atwy1;
        TMenuItem *redni1;
        TMenuItem *Trudny1;
        TMenuItem *Trudny2;
        TMenuItem *Ustawienia1;
        TMenuItem *Dzwieki1;
        TMenuItem *Pomoc1;
        TMenuItem *Oprogramie1;
        TMenuItem *N1;
        TMenuItem *N2;
        TTimer *czas;
        TTimer *gameover;
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall FormPaint(TObject *Sender);
        void __fastcall FormMouseMove(TObject *Sender, TShiftState Shift,
          int X, int Y);
        void __fastcall FormMouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall FormClick(TObject *Sender);
        void __fastcall FormKeyPress(TObject *Sender, char &Key);
        void __fastcall redni1Click(TObject *Sender);
        void __fastcall Trudny1Click(TObject *Sender);
        void __fastcall Trudny2Click(TObject *Sender);
        void __fastcall Koniec1Click(TObject *Sender);
        void __fastcall Dzwieki1Click(TObject *Sender);
        void __fastcall czasTimer(TObject *Sender);
        void __fastcall Zapisz1Click(TObject *Sender);
        void __fastcall aduj1Click(TObject *Sender);
        void __fastcall Najlepszewyniki1Click(TObject *Sender);
        void __fastcall gameoverTimer(TObject *Sender);
        void __fastcall FormActivate(TObject *Sender);
        void __fastcall Oprogramie1Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
