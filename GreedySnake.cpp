/*
    注意：
    本程式中，Snake和Food的座標都是( vertical , horizontal )
    但是Draw裡面的參數是( horizontal , vertical )
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
        point的第一個參數是垂直座標，第二個才是水平座標
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
char gBorder[BORDER_HEIGHT][BORDER_WIDTH] ; // 貪食蛇的地圖，高20、寬40
Point gFoodPosition ;                       // 存放食物的位置
Point gSnake[GAME_WINNING_CONDITION] ;       // 蛇的長度，最大到50個，到50個以後就遊戲勝利
Point gDirection ;                          // 接收到鍵盤輸入後，會把方向存進來，再和gSnake一起運算出新的位置。
/*
    這邊的宣告都是給console用的，接收鍵盤訊息就是靠它們
*/
HANDLE gHandle_In, gHandle_Out ;            // I/O 控制器，gHandle_In和ReadConsoleInput搭配，負責接收鍵盤訊號
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
        Draw( gFoodPosition.horizontal, gFoodPosition.vertical, "X" ) ; // 把食物畫到地圖上
        if( kbhit() )
            /*
                因為原本的KeyControl反應速度太慢，所以改成直接讀我輸入的字元，
                再用該字元來決定方向
            */
            ControlDirection() ;
            //KeyControl() ;
        Snake_Move() ;
        PrintScore() ;
    } // while

    gotoxy( 10, 20 ) ; // 這是為了讓遊戲結束後，游標能夠指到最下面，不然結束訊息會把遊戲畫面切斷
    system( "pause" ) ;
    return 0 ;

} // main()

void ChooseDelayTime()
{
    printf( "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX\n" ) ;
    printf( "XX      遊戲名稱：貪食蛇              XX\n" ) ;
    printf( "XX      勝利條件：吃到30個食物        XX\n" ) ;
    printf( "XX      失敗條件：撞到牆壁或吃到自己  XX\n" ) ;
    printf( "XX                                    XX\n" ) ;
    printf( "XX      難度選擇：                    XX\n" ) ;
    printf( "XX      （使用W、S來上下移動）        XX\n" ) ;
    printf( "XX                                    XX\n" ) ;
    printf( "XX      初級                          XX\n" ) ;
    printf( "XX      中級                          XX\n" ) ;
    printf( "XX      高級                          XX\n" ) ;
    printf( "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX\n" ) ;

    static int sInit_X_axis = 4 ; // "初級難度"的x軸位置，隨著我上面印出來的行數不同而要跟著修改
    static int sInit_Y_axis = 8 ; // "初級難度"的y軸位置，隨著我上面印出來的行數不同而要跟著修改
    int index = sInit_Y_axis ;
    Draw( sInit_X_axis, sInit_Y_axis, "=>" ) ;

    char instr ;

    while( instr = getch() )
    {
        if( instr == 13 ) // 如果是用getch的話，換行符號是13，我不知道為什麼用/n不行
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
        這function可以將位置移到x,y
        第一個傳入的是水平軸座標，
        第二個傳入的才是垂直軸座標
    */
    COORD coord ;
    coord.X = x ;
    coord.Y = y ;
    SetConsoleCursorPosition ( gHandle_Out, coord ) ;
} // gotoxy()

void Init()
{
    gotoxy( 0, 0 ) ; // 先設定到( 0, 0 )的點再來繪圖

    /*
        這個function主要是做事前的設定，比如說：
            1.將貪食蛇的遊戲地圖設定好
            2.將貪食蛇的起始位置以及預設方向決定好
            3.將第一個食物的位子決定好
            4.把設定好的蛇跟食物畫出來
            5.印出操作說明
    */
    SetBorder() ; // 將貪食蛇的遊戲地圖設定好
    SetSnake() ; // 將貪食蛇的起始位置以及預設方向決定好
    SetFood() ; // 將第一個食物的位子決定好
    PrintMap() ; // 把設定好的蛇跟食物畫出來
    PrintManual() ; // 印出操作說明

} // Init()

void SetBorder()
{
    for( int i = 0 ; i < BORDER_HEIGHT ; i++ )
    {
        if( i == 0
            || i == ( BORDER_HEIGHT - 1 ) )
        {
            /*
                最上層和最下層，形狀應該是+-------+
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
                中間，形狀應該是|       |
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
      設定蛇一開始的位置和長度，以及一開始的方向
    */
    gSnake[0].SetPosition( 13, 25 ) ;
    gSnake[1].SetPosition( 13, 26 ) ;
    gSnakeLength = 2 ;
    gDirection.SetPosition( 0, -1 ) ; // 也就是向左移動的意思

} // SetSnake()

void SetFood()
{
    int x = 0, y = 0 ;
    x = 1 + rand() % ( BORDER_HEIGHT - 2 ) ; // 取1~18
    y = 1 + rand() % ( BORDER_WIDTH - 2 ) ; // 取1-38
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
        KeyControl的作法目前還看的不是很懂，好像需要先經過ReadConsoleInput以後，
        我們才可以將從鍵盤讀到的資料放到程式裡面，姑且先用，過些時候再來研究。
    */
    /*
        bool ReadConsoleInput
        (
　           HANDLE hConsoleInput, // 從console取得標準輸入代碼
　           INPUT_RECORD lrBuffer, // 回傳數據紀錄
　           DWORD nLength, // 這次要讀取多少個紀錄
　           DWORD lpNumberOfEventsRead // 我之前已經讀取過多少個紀錄
        ) ;

        KEY_EVENT_RECORD    STRUCT
        bKeyDown            BOOL    ?       ;若為 TRUE，表示按鍵被壓下；FALSE 表示按鍵被鬆開
        wRepeatCount        WORD    ?
        wVirtualKeyCode     WORD    ?       ;虛擬鍵碼
        wVirtualScanCode    WORD    ?       ;虛擬掃描碼
            UNION           uChar           ;uChar 表示按鍵的 ASCII 碼或萬國碼
                UnicodeChar WCHAR   ?       ;萬國碼，一個 WCHAR 相當於一個字組
                AsciiChar   CHAR    ?       ;ASCII 碼，一個 CHAR 相當於一個位元組
            ENDS
        dwControlKeyState   DWORD   ?       ;控制鍵 ( 如 Alt、Shift、Ctrl、Scroll Lock 等鍵 ) 的狀態
        KEY_EVENT_RECORD    ENDS

    */
    ReadConsoleInput( gHandle_In, &gInputRecord, 1, &gNumOfEventsRead ) ;
    /*
        如果我剛剛壓下的按鍵是被放開的話，就不要理他了
    */
    if( !gInputRecord.Event.KeyEvent.bKeyDown )
        return ;
    /*
        一般來說，我直接呼叫MoveUp/MoveDown/MoveLeft/MoveRight就可以，
        但是在這遊戲裡面，我希望如果上一個指令是UP的話，他不能在這個換成DOWN
    */
    if( gInputRecord.Event.KeyEvent.wVirtualKeyCode == VK_ESCAPE )
        LeaveGame() ;
    else if( gInputRecord.Event.KeyEvent.wVirtualKeyCode == VK_UP )
    {
        if( gDirection.vertical != 1 ) // 如果上一個指令是UP的話，他不能在這個換成DOWN
            MoveUp() ;
    } // else if
    else if( gInputRecord.Event.KeyEvent.wVirtualKeyCode == VK_DOWN )
    {
        if( gDirection.vertical != -1 ) // 如果上一個指令是DOWN的話，他不能在這個換成UP
            MoveDown() ;
    } // else if
    else if( gInputRecord.Event.KeyEvent.wVirtualKeyCode == VK_LEFT )
    {
        if( gDirection.horizontal != 1 ) // 如果上一個指令是RIGHT的話，他不能在這個換成LEFT
            MoveLeft() ;
    } // else if
    else if( gInputRecord.Event.KeyEvent.wVirtualKeyCode == VK_RIGHT )
    {
        if( gDirection.horizontal != -1 ) // 如果上一個指令是LEFT的話，他不能在這個換成RIGHT
            MoveRight() ;
    } // else if

} // KeyControl()

void ControlDirection()
{
  /*
      按鍵              ASCII碼（10進位/16進位）
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
    if( gDirection.vertical != 1 ) // 如果上一個指令是UP的話，他不能在這個換成DOWN
      MoveUp() ;
  } // else if
  else if( instr == 's' )
  {
    if( gDirection.vertical != -1 ) // 如果上一個指令是DOWN的話，他不能在這個換成UP
      MoveDown() ;
  } // else if
  else if( instr == 'a' )
  {
    if( gDirection.horizontal != 1 ) // 如果上一個指令是RIGHT的話，他不能在這個換成LEFT
      MoveLeft() ;
  } // else if
  else if( instr == 'd' )
  {
    if( gDirection.horizontal != -1 ) // 如果上一個指令是LEFT的話，他不能在這個換成RIGHT
      MoveRight() ;
  } // else if

} // ControlDirection

void Draw( int x, int y, char *str )
{
    gotoxy( x, y ) ;
    printf( "%s", str ) ;
} // Draw()

/*
    特別注意！！
    SetPosition第一個參數是垂直、第二個才是水平

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
        Draw( 12, 10, "遊戲勝利！！" ) ;
        gLeaveGame = true ;
        return ;
    } // if

    else if( gSnake[0].horizontal <= 1 || gSnake[0].horizontal >= BORDER_WIDTH - 1
             || gSnake[0].vertical <= 1 || gSnake[0].vertical >= BORDER_HEIGHT - 1 )
    {
        /*
            貪食蛇的頭如果撞到邊界，就要GG
        */
        Draw( 12, 10, "遊戲失敗！因為你撞到牆壁！！" ) ;
        gLeaveGame = true ;
        return ;
    } // else if

    else if( Suicide() )
    {
        /*
            吃到自己，GG
        */
        Draw( 12, 10, "遊戲失敗！因為你吃到自己！！" ) ;
        gLeaveGame = true ;
        return ;
    } // else if

    else if( gSnake[0].horizontal == gFoodPosition.horizontal
             && gSnake[0].vertical == gFoodPosition.vertical )
    {
        /*
            如果蛇的頭撞到了食物，那就要變長一單位並增加分數
            還要讓delaytime減少，變得更快
        */
        gDelayTime -= gSpeed ;
        gScore += ( 100 * gSpeed ) ;
        gSnakeLength++ ;
        SetFood() ;
    } // else if

    else
        Draw( gSnake[gSnakeLength-1].horizontal, gSnake[gSnakeLength-1].vertical, " ") ; //把最後面砍掉

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
        這個function是用來檢查貪食蛇會不會撞到自己
        所以我們利用一個for迴圈來判斷，如果頭跟身體的座標一樣，就代表產生碰撞
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
    char str[100] = "分數：", str2[100] ;
    sprintf( str2, "%d", gScore ) ;
    strcat( str, str2 ) ;
    Draw( 44, 10, str ) ;

} // PrintScore()

void PrintManual()
{
    Draw( 44,3, "操作說明" ) ;
    Draw( 44,4, "上：W           下：S" ) ;
    Draw( 44,5, "左：A           右：D" ) ;

} // PrintManual()

