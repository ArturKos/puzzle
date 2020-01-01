//---------------------------------------------------------------------------

#ifndef mainintroH
#define mainintroH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <MPlayer.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class Tintro : public TForm
{
__published:	// IDE-managed Components
        TMediaPlayer *MediaPlayer1;
        TTimer *Timer1;
        void __fastcall FormActivate(TObject *Sender);
        void __fastcall FormKeyPress(TObject *Sender, char &Key);
        void __fastcall FormClick(TObject *Sender);
        void __fastcall Timer1Timer(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall Tintro(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE Tintro *intro;
//---------------------------------------------------------------------------
#endif
