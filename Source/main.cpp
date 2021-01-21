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
		"�������\n\r"
		 "\t�ҧ��� �ѭ��Ѱ\t�ʹ���\n\r" \
		 "\t�ҧ��� �á��\t�ح��\n\r" \
		 "\t��� ǧȸ�\t\t��ó���\n\r", 
		"��� ��� �غ (Pao Ying Chup)", 
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

    Player1 = InputBox("�����蹤���� 1","��سҡ�͡���ͧ͢�س ?","A");
    txtPlayer1->Caption = Player1;
    txtPlayer_1->Caption = Player1;
    Player2 = InputBox("�����蹤���� 2","��سҡ�͡���ͧ͢�س ?","B");
    txtPlayer2->Caption = Player2;
    txtPlayer_2->Caption = Player2;
    number = InputBox("�Ӷ��","�ӹǹ��  ?",10);
	round_game = number.ToInt();
    txtGameCount->Caption = round_game;
    return;
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::mmuHowPlayClick(TObject *Sender)
{
    Application->MessageBox(		
		"�����蹤���� 1\n\r�� 'Q' �����͡ ��͹\n\r��  'A' �����͡ �����\n\r�� 'Z' �����͡ ��д��\n\r\n\r" 
		"�����蹤���� 2 \n\r�� '9' �����͡ ��͹\n\r��  '6' �����͡ �����\n\r�� '3' �����͡ ��д��\n\r"
		, 	
		"�Ըա�����" ,
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

