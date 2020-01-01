//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <winbase.h>
#include <vector>
#include "main.h"
#include <math.h>
#include <wingdi.h>
#include <mmsystem.h>
#include <jpeg.hpp>

#include <windows.h>

//-----------
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys\stat.h>
#include <iostream.h>
#include <fstream.h>

#include <io.h>
#include <string.h>
#include "zapisz.cpp"
#include "laduj.cpp"
#include "nwyniki.cpp"
#include "mainintro.cpp"
#include "oprogramie.cpp"
#include "jimie.cpp"
#include "wspolne.h"


//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

#define kursor  5
#define czekaj  6
#define KGRACZE "Gracze"

UINT MCI_MidiDeviceID;

 void CloseMusic()
 {
   if(MCI_MidiDeviceID) mciSendCommand(MCI_MidiDeviceID,MCI_CLOSE,0,NULL);
   MCI_MidiDeviceID = 0;
 }
DWORD PlayMusic(LPSTR filename)
{
  MCI_OPEN_PARMS mciOpenParms;
  MCI_PLAY_PARMS mciPlayParms;
  DWORD dwReturn;
  
  mciOpenParms.lpstrDeviceType = "sequencer";
  mciOpenParms.lpstrElementName = filename;
  dwReturn=mciSendCommand(NULL,MCI_OPEN,MCI_OPEN_TYPE|MCI_OPEN_ELEMENT,(DWORD)(LPVOID)&mciOpenParms);
  if(dwReturn)
  {
	  return dwReturn;
  }

  MCI_MidiDeviceID = mciOpenParms.wDeviceID;
  
  mciPlayParms.dwCallback = (DWORD)Form1->Handle;
  dwReturn = mciSendCommand(MCI_MidiDeviceID,MCI_PLAY,MCI_NOTIFY,(DWORD)(LPVOID)&mciPlayParms);
  if(dwReturn)
  {
    CloseMusic();
    return dwReturn;
  }

  return 0L;
} 





class Powiazanie
{
  public:
  struct puzel *puz;
  Powiazanie *pNastepne;
 Powiazanie()
  {
    puz = NULL;
    pNastepne = NULL;
  }
};
class StosPuzli
{
  private:
  Powiazanie* pPierwsze;

  public:
  StosPuzli()
  {
   pPierwsze = NULL;
  };
  bool Pusta(){ return (pPierwsze==NULL); }
   void pUsun(struct puzel *pl)
    {
     Powiazanie* nex,*tmp = pPierwsze;
     if(Pusta()) return;
       if(pl==pPierwsze->puz)
        {
          nex = pPierwsze;
          pPierwsze=pPierwsze->pNastepne;
          delete nex;
          return;
        }
       nex=tmp->pNastepne;
       while(nex->puz!=pl)
        {
          tmp=tmp->pNastepne;
          nex=tmp->pNastepne;
        }
       tmp->pNastepne=nex->pNastepne;
       delete nex;  
    }
   void pWstaw(struct puzel *p)
    {
      Powiazanie* pow = new Powiazanie;
      pow->puz = p; 
      if(Pusta()) pPierwsze = pow;else
       {
         Powiazanie *tmp=pPierwsze;
         while(tmp->pNastepne!=NULL)
          tmp=tmp->pNastepne;
         tmp->pNastepne=pow;
       }
    }
   ~StosPuzli()
    {
     Powiazanie* tmp;
     if(!Pusta())
      while(pPierwsze!=NULL)
       {
         tmp = pPierwsze;
         pPierwsze=pPierwsze->pNastepne;
         delete tmp;
       }
    }
   struct puzel *pop()
    {
        static Powiazanie *tmp=NULL;
        if(Pusta()) return NULL;
        if(tmp==NULL)
        tmp=pPierwsze;else tmp=tmp->pNastepne;
        if(tmp==NULL)
        return NULL;else
        return tmp->puz;
    }
};
class ListaPuzli
{
  private:
  Powiazanie* pPierwsze;
  Powiazanie* p;
  public:
  ListaPuzli()
  {
   pPierwsze = NULL;
   p=NULL;
  };
  bool Pusta(){ return (pPierwsze==NULL); }
  int Licz()
   {
     if(Pusta())return 0;
     Powiazanie* p = pPierwsze;
     int s = 0;
     while(p!=NULL)
      {
       s++;
       p = p->pNastepne;
      }
     return s;
   }
   void pUsun(struct puzel *pl)
    {
     Powiazanie* nex,*tmp = pPierwsze;
       if(pl==pPierwsze->puz)
        {
          nex = pPierwsze;
          if(p==pPierwsze) p=pPierwsze->pNastepne;
          pPierwsze=pPierwsze->pNastepne;
          delete nex;
          return;
        }
       nex=tmp->pNastepne;
       while(nex->puz!=pl)
        {
          tmp=tmp->pNastepne;
          nex=tmp->pNastepne;
        }
       tmp->pNastepne=nex->pNastepne;
       if(p==nex) p=tmp;
       delete nex;  
    }
   void pWstaw(struct puzel *p)
    {
      Powiazanie* pow = new Powiazanie;
      pow->puz = p; 
      if(Pusta()) pPierwsze = pow;else
       {
        int r = random(Licz());
         Powiazanie *prev,*tmp=pPierwsze;
         for(int i = 0;i<r;i++)
          tmp=tmp->pNastepne;
        prev=tmp->pNastepne;
        tmp->pNastepne=pow;
        pow->pNastepne=prev;
       }
    }
   ~ListaPuzli()
    {
     Powiazanie* tmp;
     if(!Pusta())
      while(pPierwsze!=NULL)
       {
         tmp = pPierwsze;
         pPierwsze=pPierwsze->pNastepne;
         delete tmp;
       }
    }
   struct puzel *pop()
    {
      if(p == NULL) p = pPierwsze;else
      p = p->pNastepne;
      if(p == NULL) p = pPierwsze;
      return p->puz;
    }
};
///////////////////////////////////////////
struct puzel{
Graphics::TBitmap *p;
unsigned char obrot;
unsigned char nr;
};
static i = 10; //do funkcji pisz
Graphics::TBitmap *podklad,*ppodklad;
Graphics::TBitmap *puzle;
Graphics::TBitmap *mpuzle;
Graphics::TBitmap *mini;
Graphics::TBitmap *I;
Graphics::TBitmap *start;
ListaPuzli *lpuzli;
StosPuzli  *spuzli;
bool menu = false;
struct puzel **obraz;
struct puzel ***ekran;
struct puzel *klocek;
int picture = 0;
AnsiString filename = "save.puz";
TColor duch;
int rysunkow,rysunek,rozmiar,bok,poziomo,pionowo,mbok,x,y;
char godzina,minuta,sekunda;
unsigned char RYSUNKI[LRYS];

char Imie[20];
 unsigned char *r;

 unsigned int *rysunki_los=NULL;


void tworz_liste_obrazkow()
{
  unsigned int l = 0;
 if(rysunki_los!=NULL)
  delete rysunki_los;


 for(register unsigned int o = 0;o<LRYS;o++)
    if(RYSUNKI[o]!=0)l++;
 rysunki_los = new unsigned int [l];
 rysunkow = l;
 l = 0;
 for(register unsigned int o = 0;o<LRYS;o++)
  if(RYSUNKI[o]!=0)rysunki_los[l++]=o+1;
}
void laduj_status_obrazkow()
{
 AnsiString s;
 s = Imie;
 s+=".gra";
 memset(RYSUNKI,0,sizeof RYSUNKI);

 ifstream in(s.c_str(),ios::in | ios::binary);
 if(in){
 in.get(rysunek);
 in .read((unsigned char *)RYSUNKI,sizeof RYSUNKI);
 in.close();    }

 tworz_liste_obrazkow();
}

void zapisz_status_obrazkow()
{
  AnsiString s = Imie;
  s+=".gra";
  ofstream out(s.c_str(),ios::out | ios::binary);
  if(out){
  out.put((unsigned char)rysunek);
  out.write((unsigned char *)RYSUNKI,sizeof RYSUNKI);
  out.close(); }
}

int Dopasuj_Wysokosc(int wysokosc)
{
 return (wysokosc*3)/4;
}
int Dopasuj_Szerokosc(int szerokosc)
{
 //int r;
 for(int i = szerokosc;i>4;i--)
  if((i%16==0)&&(i%12==0)&&//(Dopasuj_Wysokosc(i)%16==0)&&
      (Dopasuj_Wysokosc(i)%12==0))
  //r = i;
 return i;
}
////////////////////////////////////////////////////
TForm1 *Form1;




void Set_Menu_Visible(bool b)
{
 Form1->Gra1->Visible=b;
 Form1->Ustawienia1->Visible=b;
 Form1->Najlepszewyniki1->Visible=b;
 Form1->Pomoc1->Visible=b;
}

void Graj(AnsiString name,DWORD mode)
{
 if(Form1->Dzwieki1->Checked)
    PlaySound(name.c_str(),HInstance,SND_RESOURCE | mode);
}
HBITMAP Dopasuj(Graphics::TBitmap *img,int szer,int wys,bool niszcz)
{
 BITMAP bm1,bm2;
 HBITMAP bitmap2;
 HDC hdc,hdcMem1,hdcMem2;
 hdc = CreateIC("DISPLAY",NULL,NULL,NULL);
 hdcMem1 = CreateCompatibleDC(hdc);
 hdcMem2 = CreateCompatibleDC(hdc);
 DeleteDC(hdc);
 GetObject(img->Handle, sizeof (BITMAP),(PSTR) &bm1);
 bm2 = bm1;
 bm2.bmWidth = szer;// szer *procent;
 bm2.bmHeight = wys; // wys *procent;
 bm2.bmWidthBytes = (bm2.bmWidth)*(bm2.bmBitsPixel/8);
 bitmap2 = CreateBitmapIndirect(&bm2);
 SelectObject(hdcMem1,img->Handle);
 SelectObject(hdcMem2,bitmap2);
 SetStretchBltMode(hdcMem2,COLORONCOLOR);
 StretchBlt(hdcMem2,0,0,bm2.bmWidth,bm2.bmHeight,
             hdcMem1,0,0,bm1.bmWidth,bm1.bmHeight,SRCCOPY);
 DeleteDC(hdcMem1);
 DeleteDC(hdcMem2);
 if(niszcz)
 DeleteObject(img->Handle);
 return bitmap2;
}
bool Wygrana()
{
 int numer = 1;
 for (int i = 0; i < poziomo; i++)
  for (int j = 0; j < pionowo; j++)
  {
    if(ekran[i][j]!=NULL)
     {
       if((ekran[i][j]->nr!=numer)||
          (ekran[i][j]->obrot!=0))
        return false;
     }else return false;
    numer++;
  }
 return true;
}
void RelaseData()
{
for (int i = 0; i < poziomo; i++)
  for (int j = 0; j < pionowo; j++)
  if(obraz[i][j].p!=NULL) delete obraz[i][j].p;
for (int j = 0; j < poziomo; j++)
 {
if(obraz[j]!=NULL)  delete [] obraz[j];
if(*ekran[j]!=NULL)  delete [] *ekran[j];
 }
if(obraz!=NULL)  delete [] obraz;
if(ekran!=NULL)  delete [] *ekran;
if(puzle!=NULL) delete puzle;
if(mpuzle!=NULL) delete mpuzle;
if(mini!=NULL) delete mini;
if(podklad!=NULL) delete podklad;
if(ppodklad!=NULL) delete ppodklad;
if(I!=NULL) delete I;
if(lpuzli!=NULL) delete lpuzli;
if(spuzli!=NULL) delete spuzli;
}


void Obrot90(struct puzel *puz)// kat 0=0 1=90 2=180 3=270
{
Graphics::TBitmap *tmp = new Graphics::TBitmap;
tmp->TransparentColor=puz->p->TransparentColor;
tmp->Transparent=true;
tmp->Width=puz->p->Width;
tmp->Height=puz->p->Height;
for(int i=0;i<=tmp->Height;i++)
 for(int j=0;j<=tmp->Width;j++) {
  tmp->Canvas->Pixels[tmp->Height-i-1][j]=puz->p->Canvas->Pixels[j][i]; }
puz->p->Assign(tmp);
delete tmp;
}
void Obrot180(struct puzel *puz)// kat 0=0 1=90 2=180 3=270
{
 Graphics::TBitmap *tmp = new Graphics::TBitmap;
tmp->TransparentColor=puz->p->TransparentColor;
tmp->Transparent=true;
tmp->Width=puz->p->Width;
tmp->Height=puz->p->Height;
for(int i=0;i<=tmp->Height;i++)
 for(int j=0;j<=tmp->Width;j++)  {
  tmp->Canvas->Pixels[tmp->Width-j-1][tmp->Height-i-1]=puz->p->Canvas->Pixels[j][i];    }
puz->p->Assign(tmp);
delete tmp;

}
void Obrot270(struct puzel *puz)// kat 0=0 1=90 2=180 3=270
{

 Graphics::TBitmap *tmp = new Graphics::TBitmap;
tmp->TransparentColor=puz->p->TransparentColor;
tmp->Transparent=true;
tmp->Width=puz->p->Width;
tmp->Height=puz->p->Height;
for(int i=0;i<=tmp->Height;i++)
 for(int j=0;j<=tmp->Width;j++)   {
  tmp->Canvas->Pixels[j][tmp->Height-i-1]=puz->p->Canvas->Pixels[i][j];}
puz->p->Assign(tmp);
delete tmp;
}

void Obrot(struct puzel *puz,int kat)// kat 0=0 1=90 2=180 3=270
{
 if(kat==1)
  Obrot90(puz);else
 if(kat==2)
  Obrot180(puz);else
 if(kat==3)
  Obrot270(puz);
puz->obrot+=kat; puz->obrot=(puz->obrot%4);
}
Graphics::TBitmap *LoadJPG(AnsiString name,int id)
{
 TJPEGImage *img=new TJPEGImage;
 Graphics::TBitmap *bmp = new Graphics::TBitmap;
 AnsiString str = name+id;
 HRSRC fr = FindResource(HInstance,str.c_str(),"PUZLE_DATA");
 HGLOBAL hhandle=LoadResource(HInstance,fr);
 TMemoryStream *mem = new TMemoryStream;

 mem->Write(hhandle,SizeofResource(HInstance,fr));
 mem->Position = 0;
 img->LoadFromStream(mem);
 bmp->Width = img->Width;
 bmp->Height = img->Height;
 bmp->Canvas->Draw(0,0,img);
 delete mem;
 delete img;
 return bmp;
}

void pisz(AnsiString co)
{

  Form1->Canvas->Font->Name = "Courier New"; // czcionka
  Form1->Canvas->Font->Size = 20; // rozmiar czcionki
  Form1->Canvas->Font->Style =  TFontStyles()<< fsBold;// pogrubienie
  Form1->Canvas->Brush->Style = bsClear; // t³o przezroczyste
  Form1->Canvas->Font->Color = clWhite; // kolor czcionki
  Form1->Canvas->TextOut(20, i, co);
  i+=30;

}

void rysuj_stan(int p)
{
float dd = (float (p) / float(100));
int d = dd*Form1->Width;

Form1->Canvas->Brush->Color = clGreen;
Form1->Canvas->FillRect(Rect(0,Form1->Height-20,int(d),Form1->Height));
}
void LoadData(int r,int num,bool load,bool obracaj)
{
duch=clOlive;
puzle=new Graphics::TBitmap;
mpuzle=new Graphics::TBitmap;
mini=new Graphics::TBitmap;


if(!load){

memset(RYSUNKI,1,sizeof RYSUNKI);
tworz_liste_obrazkow();
puzle = LoadJPG("rysunek",picture=rysunki_los[rand()%LRYS]);

godzina = 0; minuta = 0; sekunda = 0;
  }else
   {
    puzle = LoadJPG("rysunek",picture=num);
   }
int szerokosc = Dopasuj_Szerokosc(Screen->Width-Screen->Width*0.2);
puzle->Handle=Dopasuj(puzle,Screen->Width,Screen->Height,true);
mpuzle->Handle=Dopasuj(puzle,szerokosc,Dopasuj_Wysokosc(szerokosc),false);
//mpuzle=zRozmiar(puzle,0.75);
mini->Handle=Dopasuj(puzle,Screen->Width-33-mpuzle->Width,Dopasuj_Wysokosc(Screen->Width-mpuzle->Width-33),false);
rozmiar=r;
bok = sqrt(mpuzle->Width*mpuzle->Height/rozmiar);
poziomo=mpuzle->Width/bok;
pionowo=mpuzle->Height/bok;
mbok=bok/4;
spuzli = new StosPuzli();
lpuzli = new ListaPuzli();
I = new Graphics::TBitmap;
I->Width=Form1->Width;
I->Height=Form1->Height;
podklad = new Graphics::TBitmap;
ppodklad = new Graphics::TBitmap;
Graphics::TBitmap *Image1;
Image1=LoadJPG("tap",random(12)+1);
podklad->Width=Form1->Width;
podklad->Height=Form1->Height;
podklad->Canvas->Brush->Bitmap=Image1;
podklad->Canvas->FillRect(Rect(0,0,Form1->Width,Form1->Height));
podklad->Canvas->Rectangle(10,10,mpuzle->Width+12,mpuzle->Height+12);
if(mini)
podklad->Canvas->Draw(Form1->Width-mini->Width-11,11,mini);
ppodklad->Assign(podklad);
menu = false;
Form1->Refresh();
Form1->Canvas->Draw(0,0,puzle);
i = 10;
pisz("Sterowanie gr¹:");
pisz(" - ESC wywo³anie menu");
pisz(" - SPACJA zmiana puzla");
pisz(" - R odrzucenie puzla");
pisz(" - Lewy przycisk myszy upuszczenie / podniesienie puzla");
pisz(" - Prawy klawisz myszy obrot puzla o 90 stopni");
delete Image1;
obraz = new struct puzel*[poziomo];
      for (int j = 0; j < poziomo; j++)
          obraz[j] =new struct puzel[pionowo];
ekran = new struct puzel**[poziomo];
      for (int j = 0; j < poziomo; j++)
          ekran[j] =new struct puzel*[pionowo];

Graphics::TBitmap *bmp = new Graphics::TBitmap;
Graphics::TBitmap *mbmp = new Graphics::TBitmap;
mbmp->Canvas->Brush->Color=duch;
mbmp->Width=mbok; mbmp->Height=mbok;
bmp->Width=bok;
bmp->Height=bok;

unsigned char numer = 1;
for (int i = 0; i < poziomo; i++)
  for (int j = 0; j < pionowo; j++)
  {
    Application->ProcessMessages();
    ekran[i][j]=NULL;
    obraz[i][j].p = new Graphics::TBitmap;
    obraz[i][j].p->Canvas->Brush->Color=duch;
    obraz[i][j].p->Width=bok+(2*mbok);
    obraz[i][j].p->Height=bok+(2*mbok);
    bmp->Canvas->CopyRect(Rect(0,0,bok,bok),mpuzle->Canvas,Rect(i*bok,j*bok,i*bok+bok,j*bok+bok));
    obraz[i][j].p->Canvas->Draw(mbok,mbok,bmp);
    obraz[i][j].p->TransparentColor=duch;
    obraz[i][j].p->Transparent=true;
    obraz[i][j].nr=numer; numer++;
    obraz[i][j].obrot=0;
    lpuzli->pWstaw(&obraz[i][j]);
  }
bmp->Width=mbok;
bmp->Height=mbok;
for(int j =0;j<pionowo;j++)
 for(int i = 1;i<poziomo;i++)
 {
   Application->ProcessMessages();
   bmp->Canvas->CopyRect(Rect(0,0,mbok,mbok),mpuzle->Canvas,Rect(i*bok,j*bok+mbok,i*bok+mbok,j*bok+2*mbok));
   obraz[i-1][j].p->Canvas->Draw(bok+mbok,2*mbok,bmp);
   obraz[i-1][j].p->Canvas->Draw(bok,3*mbok,mbmp);

   bmp->Canvas->CopyRect(Rect(0,0,mbok,mbok),mpuzle->Canvas,Rect(i*bok-mbok,j*bok+2*mbok,i*bok,j*bok+bok-mbok));
   obraz[i][j].p->Canvas->Draw(mbok,2*mbok,mbmp);
   obraz[i][j].p->Canvas->Draw(0,3*mbok,bmp);
 }

for(int j =0;j<pionowo-1;j++)
 for(int i = 0;i<poziomo;i++)
 {
  Application->ProcessMessages();
   bmp->Canvas->CopyRect(Rect(0,0,mbok,mbok),mpuzle->Canvas,Rect(i*bok+2*mbok,(j+1)*bok,i*bok+3*mbok,(j+1)*bok+mbok));
   obraz[i][j].p->Canvas->Draw(2*mbok,bok,mbmp);
   obraz[i][j].p->Canvas->Draw(3*mbok,bok+mbok,bmp);

   bmp->Canvas->CopyRect(Rect(0,0,mbok,mbok),mpuzle->Canvas,Rect(i*bok+mbok,(j+1)*bok-mbok,i*bok+2*mbok,(j+1)*bok));
   obraz[i][j+1].p->Canvas->Draw(bok-mbok,mbok,mbmp);
   obraz[i][j+1].p->Canvas->Draw(bok-2*mbok,0,bmp);
 }

AnsiString w;
int mianownik = ((poziomo)*(pionowo));
int licznik = 1;
if(obracaj)
for(int j =0;j<pionowo;j++)
 for(int i = 0;i<poziomo;i++) { Application->ProcessMessages();
  int proc = ((licznik++)*100)/mianownik;
 rysuj_stan(proc);
Obrot(&obraz[i][j],random(4)); }
if(obracaj){
klocek=lpuzli->pop();

delete mbmp,bmp;
godzina = 0; minuta = 0; sekunda = 0;
Form1->czas->Enabled=true;

I->Assign(ppodklad);
if(klocek)
I->Canvas->Draw(x-klocek->p->Width/2,y-klocek->p->Height/2,klocek->p);
Form1->Canvas->Draw(0,0,I);   }
}
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------


void __fastcall TForm1::FormCreate(TObject *Sender)
{


  DoubleBuffered = true;
randomize();
godzina = 0; minuta = 0; sekunda = 0;
Width=Screen->Width;
Height=Screen->Height;
Left=0;
Top=0;
obraz = NULL;
ekran=NULL;
puzle=NULL;
mpuzle=NULL;
mini=NULL;
podklad=NULL;
ppodklad=NULL;
I=NULL;
lpuzli=NULL;
spuzli=NULL;
start=NULL;

Screen->Cursors[kursor]=LoadCursor(HInstance,"kursor");
Screen->Cursors[czekaj]=LoadCursor(HInstance,"czekaj");
Cursor=kursor;
  start = LoadJPG("start",0);
  start->Handle=Dopasuj(start,Screen->Width,Screen->Height,true);
//PlayMusic("song.mid");
 laduj_statystyki();
  if (!DirectoryExists(KGRACZE))
    CreateDir(KGRACZE);
  if (!DirectoryExists(KATALOG))
    CreateDir(KATALOG);



}
//---------------------------------------------------------------------------







void __fastcall TForm1::FormPaint(TObject *Sender)
{
if(menu){
I->Assign(ppodklad);
if(klocek)
I->Canvas->Draw(x-klocek->p->Width/2,y-klocek->p->Height/2,klocek->p);
Canvas->Draw(0,0,I); }else
  {
    Canvas->Draw(0,0,start);
  }
}
//---------------------------------------------------------------------------


void __fastcall TForm1::FormMouseMove(TObject *Sender, TShiftState Shift,
      int X, int Y)
{
x = X; y = Y;
if(gameover->Enabled)return;
if(menu){
I->Assign(ppodklad);
if(klocek)
I->Canvas->Draw(X-klocek->p->Width/2,Y-klocek->p->Height/2,klocek->p);
Canvas->Draw(0,0,I); }
}
//---------------------------------------------------------------------------


void __fastcall TForm1::FormMouseDown(TObject *Sender, TMouseButton Button,
      TShiftState Shift, int X, int Y)
{
if(gameover->Enabled)return;
if(menu){
if(Button==mbRight){
if(klocek){
 Cursor=czekaj;
 Graj("obrot",SND_ASYNC);
 Obrot(klocek,1);
 Cursor=kursor;
 }
 I->Assign(ppodklad);
if(klocek)
I->Canvas->Draw(X-klocek->p->Width/2,Y-klocek->p->Height/2,klocek->p);
Canvas->Draw(0,0,I);} }
}
//---------------------------------------------------------------------------






void __fastcall TForm1::FormClose(TObject *Sender, TCloseAction &Action)
{
if(start!=NULL) delete start;
RelaseData();
zapisz_statystyki();
 ChDir(KGRACZE);
zapisz_status_obrazkow();
ChDir("..");
}
//---------------------------------------------------------------------------


void Wypelnij()
{
ppodklad->Assign(podklad);
struct puzel *tmp;
while((tmp=spuzli->pop())!=NULL)
 for (int i = 0; i < poziomo; i++)
  for (int j = 0; j < pionowo; j++)
    if((ekran[i][j]!=NULL)&&(ekran[i][j]==tmp))
     ppodklad->Canvas->Draw(((i*bok)+11)-mbok,((j*bok)+11)-mbok,ekran[i][j]->p);
}
void __fastcall TForm1::FormClick(TObject *Sender)
{
if(gameover->Enabled)return;
   if(menu)
    if((x>11+mbok)&&(x<mpuzle->Width+12-2*mbok)
     &&(y>11+mbok)&&(y<mpuzle->Height+12-2*mbok))
     if(ekran[x/bok][y/bok]==NULL)
  { if(klocek){
    ppodklad->Canvas->Draw(((x/bok)*bok+11)-mbok,((y/bok)*bok+11)-mbok,klocek->p);
    ekran[x/bok][y/bok]=klocek;
    lpuzli->pUsun(klocek);
    spuzli->pWstaw(klocek);
       I->Assign(ppodklad);
   Canvas->Draw(0,0,I);
    klocek=NULL;
    Graj("upuszczenie",SND_ASYNC);
    if(Wygrana()){
                   czas->Enabled=false;
                   gameover->Enabled=true;
                   Graj("wygrana",SND_SYNC);
                   struct Gracz gr;
                    RYSUNKI[picture]=1;
                   tworz_liste_obrazkow();
                   if( ((sizeof rysunki_los)==0)||(rysunki_los==NULL) )

                       {
                         memset(RYSUNKI,1,sizeof RYSUNKI);
                         tworz_liste_obrazkow();
                         Application->MessageBox("Udalo Ci sie ulozyc wszystkie obrazki!", "Super",MB_OK);
                       }
                   if(Imie=="")
                   strcpy(gr.Imie,"Anonim");else
                   strcpy(gr.Imie,Imie);
                   gr.Godzina = godzina;
                   gr.Minuta = minuta;
                   gr.Sekunda = sekunda;
                   dodaj_do_statystyki(gr,rozmiar);
                   AnsiString str = "Gratulacje, u³o¿yleœ puzle w ";
                              str+=int(godzina);
                              str+=" godzin ";
                              str+=int(minuta);
                              str+=" minut i ";
                              str+=int(sekunda);
                              str+=" sekund. Spróbujesz jeszcze raz?";
                       if(MessageDlg(str, mtInformation, TMsgDlgButtons() << mbYes << mbNo, 0)==mrYes)
                       {
                         gameover->Enabled=false;
                         menu=false;
                         Set_Menu_Visible(true);
                         Canvas->Draw(0,0,start);
                       }else
                        {

                         // if(start!=NULL) delete start;
                        //  RelaseData();
                        //  zapisz_statystyki();
                          Close();
                        }
                   }
              }
  }else
  if(!klocek){
   klocek = ekran[x/bok][y/bok];
   lpuzli->pWstaw(klocek);
   spuzli->pUsun(klocek);
   ekran[x/bok][y/bok]=NULL;
   Cursor=czekaj;
   Wypelnij();
   Cursor=kursor;
   I->Assign(ppodklad);
   Canvas->Draw(0,0,I);
  }else Graj("nie_wolno",SND_ASYNC);
}
//---------------------------------------------------------------------------



void __fastcall TForm1::FormKeyPress(TObject *Sender, char &Key)
{
if(menu){
if(gameover->Enabled)
{
 gameover->Enabled=false;
 Canvas->Draw(0,0,start);
 menu=false;
// RelaseData();

}
switch (Key) {
  case 32:
          if(!lpuzli->Pusta())
          klocek=lpuzli->pop();
          I->Assign(ppodklad);
          if(klocek)
          I->Canvas->Draw(x-klocek->p->Width/2,y-klocek->p->Height/2,klocek->p);
          Canvas->Draw(0,0,I);
          break;
  case 27:
          if(Gra1->Visible)
          Set_Menu_Visible(false);else
          Set_Menu_Visible(true);
          break;
  case 'R':
  case 'r':
          klocek=NULL;
          break;
 } }

}
//---------------------------------------------------------------------------





void __fastcall TForm1::redni1Click(TObject *Sender)
{

Set_Menu_Visible(false);
RelaseData();
LoadData(12,0,false,true);
menu=true;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Trudny1Click(TObject *Sender)
{

Set_Menu_Visible(false);
RelaseData();
LoadData(48,0,false,true);
menu=true;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Trudny2Click(TObject *Sender)
{

Set_Menu_Visible(false);
RelaseData();
LoadData(192,0,false,true);
menu=true;
}
//---------------------------------------------------------------------------



void __fastcall TForm1::Koniec1Click(TObject *Sender)
{
Close();        
}
//---------------------------------------------------------------------------






void __fastcall TForm1::Dzwieki1Click(TObject *Sender)
{
 if(Dzwieki1->Checked)
 Dzwieki1->Checked=false;else
 Dzwieki1->Checked=true;
if(menu) 
Set_Menu_Visible(false);
}
//---------------------------------------------------------------------------

void LadujGre(AnsiString filename)
{

Set_Menu_Visible(false);
RelaseData();
menu=true;
unsigned char ch;

 ifstream in(filename.c_str(), ios::in | ios::binary );
       in.read((unsigned char *) &Imie,sizeof Imie);
       in.read((unsigned char *) &rysunek,sizeof rysunek);
       in.read((unsigned char *) &rozmiar,sizeof rozmiar);
       in.read((unsigned char *) &poziomo,sizeof poziomo);
       in.read((unsigned char *) &pionowo,sizeof pionowo);
       in.read((unsigned char *) &picture,sizeof picture);
       in.read((unsigned char *) &godzina,sizeof godzina);
       in.read((unsigned char *) &minuta,sizeof minuta);
       in.read((unsigned char *) &sekunda,sizeof sekunda);
 LoadData(rozmiar,picture,true,false);
 int mianownik = ((poziomo)*(pionowo));
 int licznik = 1;
        for(int j =0;j<poziomo;j++)
        for(int i = 0;i<pionowo;i++)
         {
          in.read((unsigned char *) &ch,sizeof ch);
           Obrot(&obraz[j][i],ch);
           Application->ProcessMessages();
           int proc = ((licznik++)*100)/mianownik;
           rysuj_stan(proc);
          in.read((unsigned char *) &ch,sizeof ch);
           if(ch==255) ekran[j][i]=NULL;
           else
              for(int k =0;k<poziomo;k++)
                  for(int l = 0;l<pionowo;l++)
                   if(obraz[k][l].nr==ch){
                    ekran[j][i] = &obraz[k][l];
                    spuzli->pWstaw(&obraz[k][l]);
                    lpuzli->pUsun(&obraz[k][l]);

                    }  
         }
       Wypelnij();
       klocek=lpuzli->pop();
       Form1->czas->Enabled=true;
         menu=true;
Form1->Refresh();
}
void ZapiszGre(AnsiString filename)
{
unsigned char zero = 255;
 ofstream out(filename.c_str(), ios::out | ios::binary );
       out.write((unsigned char *) &Imie,sizeof Imie);
       out.write((unsigned char *) &rysunek,sizeof rysunek);
       out.write((unsigned char *) &rozmiar,sizeof rozmiar);
       out.write((unsigned char *) &poziomo,sizeof poziomo);
       out.write((unsigned char *) &pionowo,sizeof pionowo);
       out.write((unsigned char *) &picture,sizeof picture);
       out.write((unsigned char *) &godzina,sizeof godzina);
       out.write((unsigned char *) &minuta,sizeof minuta);
       out.write((unsigned char *) &sekunda,sizeof sekunda);

        for(int j =0;j<poziomo;j++)
         for(int i = 0;i<pionowo;i++)
         {
           out.write((unsigned char *) &obraz[j][i].obrot,sizeof obraz[j][i].obrot);
           if(ekran[j][i]!=NULL)
            out.write((unsigned char *) &ekran[j][i]->nr,sizeof ekran[j][i]->nr);
            else out.write((unsigned char *) &zero,sizeof zero);
         }
   out.close();
}



void __fastcall TForm1::czasTimer(TObject *Sender)
{
 if(sekunda<59) sekunda++;
  else { sekunda=0;
   if(minuta<59) minuta++;
  else { minuta=0; godzina++;}
                     }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Zapisz1Click(TObject *Sender)
{
Form2->ShowModal();
 ChDir(KATALOG);
ZapiszGre(FileName+".puz");
 ChDir("..");
}
//---------------------------------------------------------------------------

void __fastcall TForm1::aduj1Click(TObject *Sender)
{
 Form3->ShowModal();
  ChDir(KGRACZE);
 laduj_status_obrazkow();
 ChDir("..");
 ChDir(KATALOG);
 if(FileExists(Filename))
 LadujGre(Filename);
 ChDir("..");

}
//---------------------------------------------------------------------------

void __fastcall TForm1::Najlepszewyniki1Click(TObject *Sender)
{
Form4->ShowModal();
}
//---------------------------------------------------------------------------




void __fastcall TForm1::gameoverTimer(TObject *Sender)
{
Form1->Canvas->Draw(random(Form1->Width),random(Form1->Height),obraz[random(poziomo)][random(pionowo)].p);
}
//---------------------------------------------------------------------------




void __fastcall TForm1::FormActivate(TObject *Sender)
{
static bool show = true;
if(show) {
if(FileExists("intro.avi"))
intro->ShowModal();
Set_Menu_Visible(true);
 ChDir(KGRACZE);

 imie->ShowModal();
memset(Imie,0,sizeof Imie);
strcpy(Imie,imie->Edit1->Text.c_str());
laduj_status_obrazkow();
  ChDir("..");
  show = false; }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Oprogramie1Click(TObject *Sender)
{
Form5->ShowModal();
}
//---------------------------------------------------------------------------

