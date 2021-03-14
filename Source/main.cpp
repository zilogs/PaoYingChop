//---------------------------------------------------------------------------
#include <vcl.h>
#include <mmsystem.h>
#pragma hdrstop

#include <conio.h>

#include "main.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmMain *frmMain;

const char picture_start[]    = "Picture\\Start.jpg";

const char picture_rock[]     = "Picture\\Rock.jpg";
const char picture_scissors[] = "Picture\\Scissors.jpg";
const char picture_paper[]    = "Picture\\Paper.jpg";

//---------------------------------------------------------------------------
__fastcall TfrmMain::TfrmMain(TComponent* Owner)
    : TForm(Owner)
{
    imgPlayer1->Picture->LoadFromFile( picture_rock );
    imgPlayer2->Picture->LoadFromFile( picture_rock );
    // imgPlayer1->Picture = NULL;
    // imgPlayer2->Picture = NULL;
    srand ( time ( 0 ) );
    txtStart->Visible = false;
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::mmuAboutClick(TObject *Sender)
{
    PlaySoundClick();
    Sleep(200);
    Application->MessageBox(
        "โปรแกรมโดย\n\r"
         "\tนางสาว กัญญณัฐ\tแสนแก้ว\n\r" \
         "\tนางสาว วรกมล\tบุญมี\n\r" \
         "\tนาย วงศธร\t\tวรรณชัย\n\r",
        "เป่า ยิ้ง ฉุบ (Pao Ying Chup)",
        MB_OK ); // | MB_ICONINFORMATION);
}

//---------------------------------------------------------------------------
void __fastcall TfrmMain::mmuHowPlayClick(TObject *Sender)
{
    PlaySoundClick();
    Application->MessageBox(
        "ผู้เล่นคนที่ 1\n\rกด 'Q' เพื่อออก ค้อน\n\rกด  'A' เพื่อออก กรรไกร\n\rกด 'Z' เพื่อออก กระดาษ\n\r\n\r"
        "ผู้เล่นคนที่ 2 \n\rกด '9' เพื่อออก ค้อน\n\rกด  '6' เพื่อออก กรรไกร\n\rกด '3' เพื่อออก กระดาษ\n\r"
        , "วิธีการเล่น" ,
        MB_OK ); // | MB_ICONINFORMATION);

    return;
}

//---------------------------------------------------------------------------
/*
    Truth table of Pao Ying Chup

    Result          Rock        Scissors        Paper
    -------------------------------------------------------
    Rock            Equal(0)    Win(1)          Lose(-1)

    Scissors        Lose(-1)    Equal(0)        Win(1)

    Paper           Win(1)      Lose(-1)        Equal(0)

*/

// Global variable of Application.

AnsiString Player1 = "A" , Player2 = "B";
int Player1_score = 0 , Player2_score = 0;
int round_game = 10 , count_of_round;

enum { IDLE , STANDBY_2PLAYER , PLAY_2PLAYER , STANDBY_COMP , PLAY_COMP };
enum { NONE , ROCK , SCISSORS , PAPER };
enum { EQU = 0 , WIN = 1, LOSE = -1 };

const int player_result[3][3] = {
    {  EQU   ,  WIN  , LOSE } ,
    {  LOSE  ,  EQU  , WIN } ,
    {  WIN  ,   LOSE , EQU }
};

int state = IDLE;
int p1,p2;

//---------------------------------------------------------------------------
void __fastcall TfrmMain::mmuPlayer12Click(TObject *Sender)
{
    AnsiString number;

    PlaySoundClick();
    if ( InputQuery ("ผู้เล่นคนที่ 1","กรุณากรอกชื่อของคุณ ?", Player1) == false )
        return;
    txtPlayer1->Caption = Player1;
    txtPlayer_1->Caption = Player1;
    PlaySoundClick();
    if ( InputQuery ("ผู้เล่นคนที่ 2","กรุณากรอกชื่อของคุณ ?", Player2) == false )
        return;
    txtPlayer2->Caption = Player2;
    txtPlayer_2->Caption = Player2;
    PlaySoundClick();
    number = IntToStr( round_game );
    if ( InputQuery ("คำถาม","จำนวนเกม  ?", number ) == false )
        return;
    round_game = number.ToInt();
    txtGameCount->Caption = round_game;

    state = STANDBY_2PLAYER;
    imgPlayer1->Picture = NULL;
    imgPlayer2->Picture = NULL;
    Player1_score = Player2_score = 0;
    count_of_round = 1;
    txtGameCount->Caption = count_of_round;
    txtStart->Visible = true;
    return;
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::mmuNewPlayComputerClick(TObject *Sender)
{
    AnsiString number;

    PlaySoundClick();
    if ( InputQuery("ชื่อผู้เล่น","กรุณากรอกชื่อของคุณ ?",Player1) == False )
        return;
    txtPlayer1->Caption = Player1;
    txtPlayer_1->Caption = Player1;
    Player2 = "Computer";
    txtPlayer2->Caption = Player2;
    txtPlayer_2->Caption = Player2;

    PlaySoundClick();
    number = IntToStr( round_game );
    if ( InputQuery("คำถาม","จำนวนเกม  ?",number) == false )
        return;
    round_game = number.ToInt();
    txtGameCount->Caption = round_game;
    state = STANDBY_COMP;
    imgPlayer1->Picture = NULL;
    imgPlayer2->Picture = NULL;
    Player1_score = Player2_score = 0;
    count_of_round = 1;
    txtGameCount->Caption = count_of_round;
    txtStart->Visible = true;
    return;
}

//---------------------------------------------------------------------------
    int __fastcall TfrmMain::PlayerResult(int py1,int py2)
    {
        int result;
        AnsiString ans;

        result = player_result [py1-1][py2-1];
        if ( result == WIN )
            Player1_score++;
        ans = Player1 + " : " + IntToStr( Player1_score );
        txtPlayer1->Caption = ans;

        result = player_result [py2-1][py1-1];
        if ( result == WIN )
            Player2_score++;
        ans = Player2 + " : " + IntToStr( Player2_score );
            txtPlayer2->Caption = ans;

        txtGameCount->Caption = count_of_round;

        PlaySoundStop();
        Sleep( 100 );
        if ( count_of_round >= round_game ) {

            txtStart->Visible = false;
            if ( Player1_score == Player2_score ) {
                PlaySoundEx("Sound\\Tied.wav");
                Application->MessageBox( "เสมอกัน" , "สรุป" , MB_OK );
            } else {
                if ( Player1_score > Player2_score ) {
                    PlaySoundEx("Sound\\Win.wav");
                    ans = Player1 + " ชนะ.";
                    Application->MessageBox( ans.c_str() , "สรุป", MB_OK );
                } else {
                    PlaySoundEx("Sound\\Lose.wav");
                    ans = Player2 + " ชนะ.";
                    Application->MessageBox( ans.c_str() , "สรุป", MB_OK ); 
                }
            }

            // Clear picture
            imgPlayer1->Picture = NULL;
            imgPlayer2->Picture = NULL;
            state = IDLE;
            return 0;
        }

        count_of_round ++;
        return 1;
    }
//---------------------------------------------------------------------------
#define     ENTER_KEY       (13)

void __fastcall TfrmMain::FormKeyPress(TObject *Sender, char &Key)
{
    char k;
    AnsiString ans;
    unsigned r;

    k = Key;
    switch ( state ) {
    // Idle mode
    case IDLE :
        break;
    // Standby mode of 2player
    case STANDBY_2PLAYER :
        switch ( k ) {
        case ' ' :
        case ENTER_KEY :
            imgPlayer1->Picture->LoadFromFile( picture_start );
            imgPlayer2->Picture->LoadFromFile( picture_start );
            state = PLAY_2PLAYER;
            p1 = p2 = NONE;
            txtStart->Visible = false;
            PlaySoundBell();
            break;
        }
        break;

    // Player1 and Plyer2 play.
    case PLAY_2PLAYER :
        switch ( k ) {
        case 'Q' :
        case 'q' :
            p1 = ROCK;
            break;
        case 'A' :
        case 'a' :
            p1 = SCISSORS;
            break;
        case 'Z' :
        case 'z' :
            p1 = PAPER;
            break;
        case '9' :
            p2 = ROCK;
            break;
        case '6' :
            p2 = SCISSORS;
            break;
        case '3' :
            p2 = PAPER;
            break;
        default :
            return;
        }

        if ( p1 && p2 ) {
            txtStart->Visible = true;
            // Display Player1
            switch ( p1 ) {
            case ROCK :
                imgPlayer1->Picture->LoadFromFile( picture_rock );
                break;
            case SCISSORS :
                imgPlayer1->Picture->LoadFromFile( picture_scissors );
                break;
            case PAPER :
                imgPlayer1->Picture->LoadFromFile( picture_paper );
                break;
            }
            // Display Player2
            switch( p2 ) {
            case ROCK :
                imgPlayer2->Picture->LoadFromFile( picture_rock );
                break;
            case SCISSORS :
                imgPlayer2->Picture->LoadFromFile( picture_scissors );
                break;
            case PAPER :
                imgPlayer2->Picture->LoadFromFile( picture_paper );
                break;
            }

            state = STANDBY_2PLAYER;
            PlayerResult ( p1 , p2 );
        }
        break;

    // Standby mode of play with computer
    case STANDBY_COMP :
        switch ( k ) {
        case ' ' :
        case ENTER_KEY :
            imgPlayer1->Picture->LoadFromFile( picture_start );
            imgPlayer2->Picture->LoadFromFile( picture_start );
            state = PLAY_COMP;
            p1 = NONE;
            txtStart->Visible = false;
            PlaySoundBell();
            break;
        }
        break;

    // Play with Computer
    case PLAY_COMP :
        switch ( k ) {
        case 'Q' :
        case 'q' :
        case '9' :
            imgPlayer1->Picture->LoadFromFile( picture_rock );
            p1 = ROCK;
            break;
        case 'A' :
        case 'a' :
        case '6' :
            imgPlayer1->Picture->LoadFromFile( picture_scissors );
            p1 = SCISSORS;
            break;
        case 'Z' :
        case 'z' :
        case '3' :
            imgPlayer1->Picture->LoadFromFile( picture_paper );
            p1 = PAPER;
            break;
        default :
            return;
        }

        txtStart->Visible = true;
        // Randomize
        p2 = ( rand () % 3 ) + ROCK;

        switch ( p2 ) {
        case ROCK :
            imgPlayer2->Picture->LoadFromFile( picture_rock );
            break;
        case SCISSORS :
            imgPlayer2->Picture->LoadFromFile( picture_scissors );
            break;
        case PAPER :
            imgPlayer2->Picture->LoadFromFile( picture_paper );
            break;
        }

        state = STANDBY_COMP;
        PlayerResult ( p1 , p2 );
        break;

    default :
        return;
    }
    return;
}
//---------------------------------------------------------------------------

