//---------------------------------------------------------------------------

#ifndef mainH
#define mainH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Menus.hpp>
#include <ExtCtrls.hpp>
#include <jpeg.hpp>
#include <ImgList.hpp>
//---------------------------------------------------------------------------
class TfrmMain : public TForm
{
__published:	// IDE-managed Components
    TMainMenu *mmMain;
    TMenuItem *mmuFile;
    TMenuItem *mmuPlayer12;
    TMenuItem *mmuAbout;
    TStaticText *txtGameCount;
    TLabel *lblGameCount;
    TPanel *pnlGame;
    TMenuItem *mmuNewPlayComputer;
    TStaticText *txtPlayer1;
    TStaticText *txtPlayer2;
    TMenuItem *mmuHowPlay;
    TImage *imgPlayer1;
    TImage *imgPlayer2;
    TStaticText *txtPlayer_1;
    TStaticText *txtPlayer_2;
    TStaticText *txtStart;
	
    void __fastcall mmuAboutClick(TObject *Sender);
    void __fastcall mmuPlayer12Click(TObject *Sender);
    void __fastcall mmuHowPlayClick(TObject *Sender);
    void __fastcall FormKeyPress(TObject *Sender, char &Key);
    void __fastcall mmuNewPlayComputerClick(TObject *Sender);
	
private:	// User declarations
	int __fastcall PlayerResult(int py1,int py2);
public:		// User declarations
    __fastcall TfrmMain(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmMain *frmMain;
//---------------------------------------------------------------------------
#endif
