/*
    �`�N�G
    ���{�����ASnake�MFood���y�г��O( vertical , horizontal )
    ���ODraw�̭����ѼƬO( horizontal , vertical )
*/
# include<stdio.h>
# include<string.h>
# include<conio.h>
# include<time.h>
# include<stdlib.h>
# include<windows.h>

# define BORDER_HEIGHT 20
# define BORDER_WIDTH 40
# define GAME_WINNING_CONDITION 32

struct Point
{
    /*
        point���Ĥ@�ӰѼƬO�����y�СA�ĤG�Ӥ~�O�����y��
    */
    int vertical ;
    int horizontal;
    void SetPosition( int x, int y )
    {
        vertical = x ;
        horizontal = y ;
    } // SetPosition()
} ;

bool gLeaveGame = false ;
int gSnakeLength = 0 ;
int gScore = 0 ;
int gDelayTime = 0 ;
int gSpeed = 0 ;
char gBorder[BORDER_HEIGHT][BORDER_WIDTH] ; // �g���D���a�ϡA��20�B�e40
Point gFoodPosition ;                       // �s�񭹪�����m
Point gSnake[GAME_WINNING_CONDITION] ;       // �D�����סA�̤j��50�ӡA��50�ӥH��N�C���ӧQ
Point gDirection ;                          // ��������L��J��A�|���V�s�i�ӡA�A�MgSnake�@�_�B��X�s����m�C
/*
    �o�䪺�ŧi���O��console�Ϊ��A������L�T���N�O�a����
*/
HANDLE gHandle_In, gHandle_Out ;            // I/O ����AgHandle_In�MReadConsoleInput�f�t�A�t�d������L�T��
DWORD gNumOfEventsRead ;
INPUT_RECORD gInputRecord ;

void gotoxy( int x, int y ) ;
void ChooseDelayTime() ;
void Init() ;
void SetBorder() ;
void SetFood() ;
void SetSnake() ;
void PrintMap() ;
void ControlDirection() ;
void Draw( int x, int y, char *pic ) ;
void KeyControl() ;
void MoveUp() ;
void MoveDown() ;
void MoveLeft() ;
void MoveRight() ;
void LeaveGame() ;
void Snake_Move() ;
bool Suicide() ;
void PrintScore() ;
void PrintManual() ;

int main()
{
    gHandle_In = GetStdHandle( STD_INPUT_HANDLE ) ;
    gHandle_Out = GetStdHandle( STD_OUTPUT_HANDLE ) ;
    ChooseDelayTime() ;

    srand( time(NULL) ) ;
    Init() ;

    while( !gLeaveGame )
    {
        Sleep( gDelayTime ) ;
        Draw( gFoodPosition.horizontal, gFoodPosition.vertical, "X" ) ; // �⭹���e��a�ϤW
        if( kbhit() )
            /*
                �]���쥻��KeyControl�����t�פӺC�A�ҥH�令����Ū�ڿ�J���r���A
                �A�θӦr���ӨM�w��V
            */
            ControlDirection() ;
            //KeyControl() ;
        Snake_Move() ;
        PrintScore() ;
    } // while

    gotoxy( 10, 20 ) ; // �o�O���F���C��������A��Я������̤U���A���M�����T���|��C���e�����_
    system( "pause" ) ;
    return 0 ;

} // main()

void ChooseDelayTime()
{
    printf( "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX\n" ) ;
    printf( "XX      �C���W�١G�g���D              XX\n" ) ;
    printf( "XX      �ӧQ����G�Y��30�ӭ���        XX\n" ) ;
    printf( "XX      ���ѱ���G��������ΦY��ۤv  XX\n" ) ;
    printf( "XX                                    XX\n" ) ;
    printf( "XX      ���׿�ܡG                    XX\n" ) ;
    printf( "XX      �]�ϥ�W�BS�ӤW�U���ʡ^        XX\n" ) ;
    printf( "XX                                    XX\n" ) ;
    printf( "XX      ���                          XX\n" ) ;
    printf( "XX      ����                          XX\n" ) ;
    printf( "XX      ����                          XX\n" ) ;
    printf( "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX\n" ) ;

    static int sInit_X_axis = 4 ; // "�������"��x�b��m�A�H�ۧڤW���L�X�Ӫ���Ƥ��P�ӭn��ۭק�
    static int sInit_Y_axis = 8 ; // "�������"��y�b��m�A�H�ۧڤW���L�X�Ӫ���Ƥ��P�ӭn��ۭק�
    int index = sInit_Y_axis ;
    Draw( sInit_X_axis, sInit_Y_axis, "=>" ) ;

    char instr ;

    while( instr = getch() )
    {
        if( instr == 13 ) // �p�G�O��getch���ܡA����Ÿ��O13�A�ڤ����D�������/n����
            break ;
        else if( instr == 'w' && index > sInit_Y_axis )
        {
            Draw( sInit_X_axis, index, "  " ) ;
            index-- ;
            Draw( sInit_X_axis, index, "=>" ) ;
        } // else if
        else if( instr == 's' && index < ( sInit_Y_axis + 2 ) )
         {
            Draw( sInit_X_axis, index, "  " ) ;
            index++ ;
            Draw( sInit_X_axis, index, "=>" ) ;
        } // else if

    } // while

    if( index == sInit_Y_axis )
    {
        gDelayTime = 170 ;
        gSpeed = 1 ;
    } // if
    else if( index == ( sInit_Y_axis + 1 ) )
    {
        gDelayTime = 150 ;
        gSpeed = 2 ;
    } // else if
    else if( index == ( sInit_Y_axis + 2 ) )
    {
        gDelayTime = 130 ;
        gSpeed = 3 ;
    } // else if

} // ChooseDelayTime

void gotoxy( int x, int y )
{
    /*
        �ofunction�i�H�N��m����x,y
        �Ĥ@�ӶǤJ���O�����b�y�СA
        �ĤG�ӶǤJ���~�O�����b�y��
    */
    COORD coord ;
    coord.X = x ;
    coord.Y = y ;
    SetConsoleCursorPosition ( gHandle_Out, coord ) ;
} // gotoxy()

void Init()
{
    gotoxy( 0, 0 ) ; // ���]�w��( 0, 0 )���I�A��ø��

    /*
        �o��function�D�n�O���ƫe���]�w�A��p���G
            1.�N�g���D���C���a�ϳ]�w�n
            2.�N�g���D���_�l��m�H�ιw�]��V�M�w�n
            3.�N�Ĥ@�ӭ�������l�M�w�n
            4.��]�w�n���D�򭹪��e�X��
            5.�L�X�ާ@����
    */
    SetBorder() ; // �N�g���D���C���a�ϳ]�w�n
    SetSnake() ; // �N�g���D���_�l��m�H�ιw�]��V�M�w�n
    SetFood() ; // �N�Ĥ@�ӭ�������l�M�w�n
    PrintMap() ; // ��]�w�n���D�򭹪��e�X��
    PrintManual() ; // �L�X�ާ@����

} // Init()

void SetBorder()
{
    for( int i = 0 ; i < BORDER_HEIGHT ; i++ )
    {
        if( i == 0
            || i == ( BORDER_HEIGHT - 1 ) )
        {
            /*
                �̤W�h�M�̤U�h�A�Ϊ����ӬO+-------+
            */
            for( int j = 0 ; j < BORDER_WIDTH ; j++ )
            {
                if( j == 0
                    || j == ( BORDER_WIDTH - 1 ) )
                    gBorder[i][j] = '+' ;
                else
                    gBorder[i][j] = '-' ;
            } // for
        } // if

        else
        {
            /*
                �����A�Ϊ����ӬO|       |
            */
            for( int j = 0 ; j < BORDER_WIDTH ; j++ )
            {
                if( j == 0
                    || j == ( BORDER_WIDTH - 1 ) )
                    gBorder[i][j] = '|' ;
                else
                    gBorder[i][j] = ' ' ;
            } // for
        } // else
        //gBorder[i][BORDER_WIDTH] = '\0' ;
    } // for

} // SetBorder())

void SetSnake()
{
    /*
      �]�w�D�@�}�l����m�M���סA�H�Τ@�}�l����V
    */
    gSnake[0].SetPosition( 13, 25 ) ;
    gSnake[1].SetPosition( 13, 26 ) ;
    gSnakeLength = 2 ;
    gDirection.SetPosition( 0, -1 ) ; // �]�N�O�V�����ʪ��N��

} // SetSnake()

void SetFood()
{
    int x = 0, y = 0 ;
    x = 1 + rand() % ( BORDER_HEIGHT - 2 ) ; // ��1~18
    y = 1 + rand() % ( BORDER_WIDTH - 2 ) ; // ��1-38
    gFoodPosition.SetPosition( x, y ) ;

} // SetFood()

void PrintMap()
{
    for( int i = 0 ; i < BORDER_HEIGHT ; i++ )
    {
        for( int j = 0 ; j < BORDER_WIDTH ; j++ )
            printf( "%c", gBorder[i][j] ) ;
        printf( "\n" ) ;
    } // for

} // PrintMap()

void KeyControl()
{
    /*
        KeyControl���@�k�ثe�٬ݪ����O�����A�n���ݭn���g�LReadConsoleInput�H��A
        �ڭ̤~�i�H�N�q��LŪ�쪺��Ʃ��{���̭��A�h�B���ΡA�L�ǮɭԦA�Ӭ�s�C
    */
    /*
        bool ReadConsoleInput
        (
�@           HANDLE hConsoleInput, // �qconsole���o�зǿ�J�N�X
�@           INPUT_RECORD lrBuffer, // �^�Ǽƾڬ���
�@           DWORD nLength, // �o���nŪ���h�֭Ӭ���
�@           DWORD lpNumberOfEventsRead // �ڤ��e�w�gŪ���L�h�֭Ӭ���
        ) ;

        KEY_EVENT_RECORD    STRUCT
        bKeyDown            BOOL    ?       ;�Y�� TRUE�A��ܫ���Q���U�FFALSE ��ܫ���Q�P�}
        wRepeatCount        WORD    ?
        wVirtualKeyCode     WORD    ?       ;������X
        wVirtualScanCode    WORD    ?       ;�������y�X
            UNION           uChar           ;uChar ��ܫ��䪺 ASCII �X�θU��X
                UnicodeChar WCHAR   ?       ;�U��X�A�@�� WCHAR �۷��@�Ӧr��
                AsciiChar   CHAR    ?       ;ASCII �X�A�@�� CHAR �۷��@�Ӧ줸��
            ENDS
        dwControlKeyState   DWORD   ?       ;������ ( �p Alt�BShift�BCtrl�BScroll Lock ���� ) �����A
        KEY_EVENT_RECORD    ENDS

    */
    ReadConsoleInput( gHandle_In, &gInputRecord, 1, &gNumOfEventsRead ) ;
    /*
        �p�G�ڭ�����U������O�Q��}���ܡA�N���n�z�L�F
    */
    if( !gInputRecord.Event.KeyEvent.bKeyDown )
        return ;
    /*
        �@��ӻ��A�ڪ����I�sMoveUp/MoveDown/MoveLeft/MoveRight�N�i�H�A
        ���O�b�o�C���̭��A�ڧƱ�p�G�W�@�ӫ��O�OUP���ܡA�L����b�o�Ӵ���DOWN
    */
    if( gInputRecord.Event.KeyEvent.wVirtualKeyCode == VK_ESCAPE )
        LeaveGame() ;
    else if( gInputRecord.Event.KeyEvent.wVirtualKeyCode == VK_UP )
    {
        if( gDirection.vertical != 1 ) // �p�G�W�@�ӫ��O�OUP���ܡA�L����b�o�Ӵ���DOWN
            MoveUp() ;
    } // else if
    else if( gInputRecord.Event.KeyEvent.wVirtualKeyCode == VK_DOWN )
    {
        if( gDirection.vertical != -1 ) // �p�G�W�@�ӫ��O�ODOWN���ܡA�L����b�o�Ӵ���UP
            MoveDown() ;
    } // else if
    else if( gInputRecord.Event.KeyEvent.wVirtualKeyCode == VK_LEFT )
    {
        if( gDirection.horizontal != 1 ) // �p�G�W�@�ӫ��O�ORIGHT���ܡA�L����b�o�Ӵ���LEFT
            MoveLeft() ;
    } // else if
    else if( gInputRecord.Event.KeyEvent.wVirtualKeyCode == VK_RIGHT )
    {
        if( gDirection.horizontal != -1 ) // �p�G�W�@�ӫ��O�OLEFT���ܡA�L����b�o�Ӵ���RIGHT
            MoveRight() ;
    } // else if

} // KeyControl()

void ControlDirection()
{
  /*
      ����              ASCII�X�]10�i��/16�i��^
      UP                72  / 0x48
      DOWN              80  / 0x50
      LEFT              75  / 0x4B
      RIGHT             77  / 0x4D
      ESC               27  / 0x1B
  */

  char instr = getch() ;

  if( instr == 27 )
    LeaveGame() ;
  else if( instr == 'w' )
  {
    if( gDirection.vertical != 1 ) // �p�G�W�@�ӫ��O�OUP���ܡA�L����b�o�Ӵ���DOWN
      MoveUp() ;
  } // else if
  else if( instr == 's' )
  {
    if( gDirection.vertical != -1 ) // �p�G�W�@�ӫ��O�ODOWN���ܡA�L����b�o�Ӵ���UP
      MoveDown() ;
  } // else if
  else if( instr == 'a' )
  {
    if( gDirection.horizontal != 1 ) // �p�G�W�@�ӫ��O�ORIGHT���ܡA�L����b�o�Ӵ���LEFT
      MoveLeft() ;
  } // else if
  else if( instr == 'd' )
  {
    if( gDirection.horizontal != -1 ) // �p�G�W�@�ӫ��O�OLEFT���ܡA�L����b�o�Ӵ���RIGHT
      MoveRight() ;
  } // else if

} // ControlDirection

void Draw( int x, int y, char *str )
{
    gotoxy( x, y ) ;
    printf( "%s", str ) ;
} // Draw()

/*
    �S�O�`�N�I�I
    SetPosition�Ĥ@�ӰѼƬO�����B�ĤG�Ӥ~�O����

*/
void MoveUp()
{
    gDirection.SetPosition( -1, 0 ) ;
} // MoveUp

void MoveDown()
{
    gDirection.SetPosition( 1, 0 ) ;
} // MoveDown

void MoveLeft()
{
    gDirection.SetPosition( 0, -1 ) ;
} // MoveLeft

void MoveRight()
{
    gDirection.SetPosition( 0, 1 ) ;
} // MoveRight()

void LeaveGame()
{
    gLeaveGame = true ;
} // LeaveGame()

void Snake_Move()
{
    if( gSnakeLength == GAME_WINNING_CONDITION )
    {
        Draw( 12, 10, "�C���ӧQ�I�I" ) ;
        gLeaveGame = true ;
        return ;
    } // if

    else if( gSnake[0].horizontal <= 1 || gSnake[0].horizontal >= BORDER_WIDTH - 1
             || gSnake[0].vertical <= 1 || gSnake[0].vertical >= BORDER_HEIGHT - 1 )
    {
        /*
            �g���D���Y�p�G������ɡA�N�nGG
        */
        Draw( 12, 10, "�C�����ѡI�]���A��������I�I" ) ;
        gLeaveGame = true ;
        return ;
    } // else if

    else if( Suicide() )
    {
        /*
            �Y��ۤv�AGG
        */
        Draw( 12, 10, "�C�����ѡI�]���A�Y��ۤv�I�I" ) ;
        gLeaveGame = true ;
        return ;
    } // else if

    else if( gSnake[0].horizontal == gFoodPosition.horizontal
             && gSnake[0].vertical == gFoodPosition.vertical )
    {
        /*
            �p�G�D���Y����F�����A���N�n�ܪ��@���üW�[����
            �٭n��delaytime��֡A�ܱo���
        */
        gDelayTime -= gSpeed ;
        gScore += ( 100 * gSpeed ) ;
        gSnakeLength++ ;
        SetFood() ;
    } // else if

    else
        Draw( gSnake[gSnakeLength-1].horizontal, gSnake[gSnakeLength-1].vertical, " ") ; //��̫᭱�屼

    for( int i = gSnakeLength - 1 ; i > 0 ; --i )
        gSnake[i] = gSnake[i-1] ;

    gSnake[0].horizontal += gDirection.horizontal ;
    gSnake[0].vertical += gDirection.vertical ;

    for( int i = 0 ; i < gSnakeLength ; i++ )
    {
        if( i == 0 )
            Draw( gSnake[i].horizontal, gSnake[i].vertical, "@" ) ;
        else
            Draw( gSnake[i].horizontal, gSnake[i].vertical, "#" ) ;
    } // for

} // Snake_Move()

bool Suicide()
{
    /*
        �o��function�O�Ψ��ˬd�g���D�|���|����ۤv
        �ҥH�ڭ̧Q�Τ@��for�j��ӧP�_�A�p�G�Y���骺�y�Ф@�ˡA�N�N���͸I��
    */
    for( int i = 1 ; i < gSnakeLength ; i++ )
    {
        if( gSnake[0].horizontal == gSnake[i].horizontal
            && gSnake[0].vertical == gSnake[i].vertical )
            return true ;
    } // for

    return false ;

} // Suicide()

void PrintScore()
{
    char str[100] = "���ơG", str2[100] ;
    sprintf( str2, "%d", gScore ) ;
    strcat( str, str2 ) ;
    Draw( 44, 10, str ) ;

} // PrintScore()

void PrintManual()
{
    Draw( 44,3, "�ާ@����" ) ;
    Draw( 44,4, "�W�GW           �U�GS" ) ;
    Draw( 44,5, "���GA           �k�GD" ) ;

} // PrintManual()

