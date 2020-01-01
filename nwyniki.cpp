//---------------------------------------------------------------------------

#include <vcl.h>
#include <stdio.h>
#include <string.h>
#include <iostream.h>
#include <fstream.h>
#pragma hdrstop

#include "nwyniki.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm4 *Form4;
struct Gracz{
 unsigned char Imie[20];
 unsigned char Godzina;
 unsigned char Minuta;
 unsigned char Sekunda;
};
struct Gracz poziom_latwy[10];
struct Gracz poziom_sredni[10];
struct Gracz poziom_trudny[10];
void laduj_statystyki()
{

 ifstream in("Gracze.gr",ios::in | ios::binary);
 if(!in)
  {
        for(int i = 0;i<10;i++)
       {
         strcpy(poziom_latwy[i].Imie,"Puzle_Latwy");
         poziom_latwy[i].Godzina=255;
         poziom_latwy[i].Minuta=255;
         poziom_latwy[i].Sekunda=255;

         strcpy(poziom_sredni[i].Imie,"Puzle_Œredni");
         poziom_sredni[i].Godzina=255;
         poziom_sredni[i].Minuta=255;
         poziom_sredni[i].Sekunda=255;

         strcpy(poziom_trudny[i].Imie,"Puzle_Trudny");
         poziom_trudny[i].Godzina=255;
         poziom_trudny[i].Minuta=255;
         poziom_trudny[i].Sekunda=255;
       }
    ofstream out("Gracze.gr",ios::out | ios::binary);
    out.write((unsigned char *)&poziom_latwy,sizeof poziom_latwy);
    out.write((unsigned char *)&poziom_sredni,sizeof poziom_sredni);
    out.write((unsigned char *)&poziom_trudny,sizeof poziom_trudny);
    out.close();
   }else
    {
     in.read((unsigned char *)&poziom_latwy,sizeof poziom_latwy);
     in.read((unsigned char *)&poziom_sredni,sizeof poziom_sredni);
     in.read((unsigned char *)&poziom_trudny,sizeof poziom_trudny);
     in.close();
     }
}
void sortuj_statystyki()
{
 int gr = 9;
 struct Gracz tmp;
 AnsiString akt,nast;
 while(gr)
{
 for(int i=0;i<gr;i++)
  {
    akt = int(poziom_latwy[i].Godzina);
    akt+=int(poziom_latwy[i].Minuta);
    akt+=int(poziom_latwy[i].Sekunda);
    nast = int(poziom_latwy[i+1].Godzina);
    nast+=int(poziom_latwy[i+1].Minuta);
    nast+=int(poziom_latwy[i+1].Sekunda);
    if(akt>nast)
     {
      tmp = poziom_latwy[i+1];
      poziom_latwy[i+1]=poziom_latwy[i];
      poziom_latwy[i]=tmp;
     }
    akt = int(poziom_sredni[i].Godzina);
    akt+=int(poziom_sredni[i].Minuta);
    akt+=int(poziom_sredni[i].Sekunda);
    nast = int(poziom_sredni[i+1].Godzina);
    nast+=int(poziom_sredni[i+1].Minuta);
    nast+=int(poziom_sredni[i+1].Sekunda);
    if(akt>nast)
     {
      tmp = poziom_sredni[i+1];
      poziom_sredni[i+1]=poziom_sredni[i];
      poziom_sredni[i]=tmp;
     }
    akt = int(poziom_trudny[i].Godzina);
    akt+=int(poziom_trudny[i].Minuta);
    akt+=int(poziom_trudny[i].Sekunda);
    nast = int(poziom_trudny[i+1].Godzina);
    nast+=int(poziom_trudny[i+1].Minuta);
    nast+=int(poziom_trudny[i+1].Sekunda);
    if(akt>nast)
     {
      tmp = poziom_trudny[i+1];
      poziom_trudny[i+1]=poziom_trudny[i];
      poziom_trudny[i]=tmp;
     }
  }
gr--;
}
}
bool dodaj_do_statystyki(struct Gracz g,char poziom)
{
 AnsiString gracz,akt;
 Gracz tmp;
 gracz = int(g.Godzina);
 gracz+=int(g.Minuta);
 gracz+=int(g.Sekunda);
switch(poziom){
case 12:
 for(int i=0;i<10;i++)
 {
  akt = int(poziom_latwy[i].Godzina);
  akt+=int(poziom_latwy[i].Minuta);
  akt+=int(poziom_latwy[i].Sekunda);
  if(gracz<akt)
   {
    for(int k=9;k>i;k--)
     poziom_latwy[k]=poziom_latwy[k-1];
    poziom_latwy[i]=g;
    return true;
   }
 }
break;
case 48:
 for(int i=0;i<10;i++)
 {
  akt = int(poziom_sredni[i].Godzina);
  akt+=int(poziom_sredni[i].Minuta);
  akt+=int(poziom_sredni[i].Sekunda);
  if(gracz<akt)
   {
    for(int k=9;k>i;k--)
     poziom_sredni[k]=poziom_sredni[k-1];
    poziom_sredni[i]=g;
    return true;
   }
 }
break;
case 192:
 for(int i=0;i<10;i++)
 {
  akt = int(poziom_trudny[i].Godzina);
  akt+=int(poziom_trudny[i].Minuta);
  akt+=int(poziom_trudny[i].Sekunda);
  if(gracz<akt)
   {
    for(int k=9;k>i;k--)
     poziom_trudny[k]=poziom_trudny[k-1];
    poziom_trudny[i]=g;
    return true;
   }
 }
break;}
 return false;
}
void zapisz_statystyki()
{
 ofstream out("Gracze.gr",ios::out | ios::binary);

 out.write((unsigned char *)&poziom_latwy,sizeof poziom_latwy);
 out.write((unsigned char *)&poziom_sredni,sizeof poziom_sredni);
 out.write((unsigned char *)&poziom_trudny,sizeof poziom_trudny);
 out.close();
 /*
 FILE *stream;
 if((stream = fopen("Gracze.gr", "w+"))!=NULL){
      for(int i = 0;i<10;i++)
       {
         fwrite(&poziom_latwy[i], sizeof(poziom_latwy[i]), 1, stream);
         fwrite(&poziom_sredni[i], sizeof(poziom_sredni[i]), 1, stream);
         fwrite(&poziom_trudny[i], sizeof(poziom_trudny[i]), 1, stream);
       }
      fclose(stream);}  */
};
//---------------------------------------------------------------------------
__fastcall TForm4::TForm4(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm4::FormCanResize(TObject *Sender, int &NewWidth,
      int &NewHeight, bool &Resize)
{
Resize=false;
}
 void rysuj()
 {
   Form4->val->Strings->Clear();
 AnsiString ad;
switch( Form4->TabControl1->TabIndex){
 case 0:
 for(int i=0;i<10;i++)
if(poziom_latwy[i].Godzina!=255 && poziom_latwy[i].Minuta!=255 && poziom_latwy[i].Sekunda!=255)
 {
  ad.printf(poziom_latwy[i].Imie);

     ad+="=";
     ad+=int(poziom_latwy[i].Godzina);
     ad+=" godzin "; ad+=int(poziom_latwy[i].Minuta);
     ad+=" minut "; ad+=int(poziom_latwy[i].Sekunda);
     ad+=" sekund";
      Form4->val->Strings->Add(ad);
 }
 break;
 case 1:
 for(int i=0;i<10;i++)
 if(poziom_sredni[i].Godzina!=255 && poziom_sredni[i].Minuta!=255 && poziom_sredni[i].Sekunda!=255)
 {
   ad.printf(poziom_sredni[i].Imie);
   ad.Trim();
     ad+="=";
     ad+=int(poziom_sredni[i].Godzina);
     ad+=" godzin "; ad+=int(poziom_sredni[i].Minuta);
     ad+=" minut "; ad+=int(poziom_sredni[i].Sekunda);
     ad+=" sekund";
      Form4->val->Strings->Add(ad);
     ad="";
 }
 break;
 case 2:
 for(int i=0;i<10;i++)
  if(poziom_trudny[i].Godzina!=255 && poziom_trudny[i].Minuta!=255 && poziom_trudny[i].Sekunda!=255)
 {
   ad.printf(poziom_trudny[i].Imie);
   ad.Trim();
     ad+="=";
     ad+=int(poziom_trudny[i].Godzina);
     ad+=" godzin "; ad+=int(poziom_trudny[i].Minuta);
     ad+=" minut "; ad+=int(poziom_trudny[i].Sekunda);
     ad+=" sekund";
      Form4->val->Strings->Add(ad);
     ad="";
 }
 break;}
 }
//---------------------------------------------------------------------------
void __fastcall TForm4::TabControl1Change(TObject *Sender)
{
 rysuj();
}
//---------------------------------------------------------------------------

void __fastcall TForm4::FormActivate(TObject *Sender)
{
 laduj_statystyki();
 sortuj_statystyki();
 rysuj();
}
//---------------------------------------------------------------------------








