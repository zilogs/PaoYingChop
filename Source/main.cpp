//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "main.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmMain *frmMain;
//---------------------------------------------------------------------------
__fastcall TfrmMain::TfrmMain(TComponent* Owner)
    : TForm(Owner)
{
    imgPlayer1->Picture->LoadFromFile("Rock.jpg");
    imgPlayer2->Picture->LoadFromFile("Rock.jpg");
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::mmuAboutClick(TObject *Sender)
{
    Application->MessageBox(
		"โปรแกรมโดย\n\r"
		 "\tนางสาว กัญญณัฐ\tแสนแก้ว\n\r" \
		 "\tนางสาว วรกมล\tบุญมี\n\r" \
		 "\tนาย วงศธร\t\tวรรณชัย\n\r", 
		"เป่า ยิ้ง ฉุบ (Pao Ying Chup)", 
        MB_OK + MB_ICONINFORMATION);
}
//---------------------------------------------------------------------------

/*
	Truth table of Pao Ying Chup
	
	Result			Rock		Scissors		Paper
	-------------------------------------------------------
	Rock			Equal(0)	Win(1)			Lose(-1)
	
	Scissors		Lose(-1)	Equal(0)		Win(1)
	
	Paper			Win(1)		Lose(-1)		Equal(0)

*/

int round_game;
AnsiString Player1 , Player2 , Computer;
int Player1_score = 0,Player2_score = 0;

void __fastcall TfrmMain::mmuPlayer12Click(TObject *Sender)
{
    AnsiString number;

    Player1 = InputBox("ผู้เล่นคนที่ 1","กรุณากรอกชื่อของคุณ ?","A");
    txtPlayer1->Caption = Player1;
    txtPlayer_1->Caption = Player1;
    Player2 = InputBox("ผู้เล่นคนที่ 2","กรุณากรอกชื่อของคุณ ?","B");
    txtPlayer2->Caption = Player2;
    txtPlayer_2->Caption = Player2;
    number = InputBox("คำถาม","จำนวนเกม  ?",10);
	round_game = number.ToInt();
    txtGameCount->Caption = round_game;
    return;
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::mmuHowPlayClick(TObject *Sender)
{
    Application->MessageBox(		
		"ผู้เล่นคนที่ 1\n\rกด 'Q' เพื่อออก ค้อน\n\rกด  'A' เพื่อออก กรรไกร\n\rกด 'Z' เพื่อออก กระดาษ\n\r\n\r" 
		"ผู้เล่นคนที่ 2 \n\rกด '9' เพื่อออก ค้อน\n\rกด  '6' เพื่อออก กรรไกร\n\rกด '3' เพื่อออก กระดาษ\n\r"
		, 	
		"วิธีการเล่น" ,
		MB_OK + MB_ICONINFORMATION);

    return;
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::FormKeyPress(TObject *Sender, char &Key)
{
    char k;

    k = Key;
    switch ( k ) {
    case 'Q' :
	case 'q' :
        imgPlayer1->Picture->LoadFromFile("Rock.jpg");
        break;
    case 'A' :
	case 'a' :
        imgPlayer1->Picture->LoadFromFile("Scissors.jpg");
        break;
    case 'Z' :
	case 'z' :
        imgPlayer1->Picture->LoadFromFile("Paper.jpg");
        break;
	case '9' :
		imgPlayer2->Picture->LoadFromFile("Rock.jpg");
		break;
	case '6' :
		imgPlayer2->Picture->LoadFromFile("Scissors.jpg");
		break;
	case '3' :
		imgPlayer2->Picture->LoadFromFile("Paper.jpg");
		break;
    }
	
    return;
}
//---------------------------------------------------------------------------

