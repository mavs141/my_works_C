
/*

  行事曆檔案名稱寫死為mySchedule.poher

  Step1：
    一開始進入程式，會詢問要登入還是註冊。
    如果要登入 => 輸入帳號密碼，並進行驗證。
    如果要註冊 => 輸入想申請的帳號密碼，並檢查帳號是否有重複，沒有重複才可以申請。

    （帳號名稱為myAccount.poher）

  Step2：
    登入之後，會詢問是要使用什麼功能，目前只規劃了新增、印出以及離開
    如果要新增 => 製造出一個linked list（型態為DateEvent）並加在陣列下面
    如果要印出 => 直接把該月份下面所有的list給印出就好

  補充：
    "帳號"為一linked list（型態為Account），裡面包含了帳號以及密碼。
    "行事曆的內容"為一linked list（型態為DateEvent），裡面包含了該事件的日期、創造者、時間、事件行數以及事件內容。
    "行事曆本身"則是一個陣列，我只規劃了一年份的行事曆，所以只有12個欄位，其中每個欄位包含了月份、該月份的行事曆的個數、行事曆的內容

*/
# include<fstream.h>
# include<iostream.h>
# include<string.h>
# include<time.h>
# define STR_MAX_LENGTH 100
# define NUM_OF_A_YEAR 12
# define STR_ZERO "0"

/*
  我自己會用到的定義區
*/

enum ErrorMsg
{
  NOT_A_INTEGER = -999,
  WRONG_MONTH,
  WRONG_DAY,
  WRONG_HOUR,
  WRONG_MINUTE,
  WRONG_ACCOUNT,
  WRONG_PASSWORD
};

typedef char Str100[100] ;

struct Content
{
  int length ;
  Str100 content ;
};

typedef Content Content10[10] ;

struct Account
{
  Str100 id ;
  Str100 pw ;

  Account *next ;
};

struct DateEvent
{
  Str100 date ;
  Str100 owner ;
  Str100 time ;
  Content10 content ;
  int lineOfContent ;

  DateEvent *next ;
};

struct Month
{
  int index ;
  int numOfEvent ;
  DateEvent *below ;
};

typedef DateEvent *DatePtr ;
typedef Month *MonthPtr ;
typedef Account *AccountPtr ;

/*
  function的宣告
*/

void GetToken( Str100 input, int length ) ;
void OpenAccount() ;
AccountPtr AddNewAccount( Str100 id, Str100 pw ) ;
void Register() ;
void Login() ;
bool IsAccountRepeat( Str100 id ) ;
bool VerifyAccountAndPassword( Str100 id, Str100 pw ) ;
void WriteAccountFile() ;
void OpenData() ;
int FindIndex( int month ) ;
void AddSchedule() ;
int IsInt( Str100 str ) ;
void KeyinScheduleDate( int &index, Str100 date ) ;
int CheckMonthAndIndex( Str100 str ) ;
int CheckDay( int index, Str100 str ) ;
void KeyinScheduleTime( Str100 str ) ;
int CheckHour( Str100 str ) ;
int CheckMinute( Str100 str ) ;
void KeyinScheduleContent( int &lineOfContent, Content10 content ) ;
DatePtr CreateDateEvent( Str100 date, Str100 owner, Str100 time,Content10 content, int lineOfContent ) ;
void ContentCopy( Content10 content1, Content10 content2, int lineOfContent ) ;
void WriteScheduleFile() ;
void ViewSchedule() ;
void GetCurrentDate( int &index, Str100 date ) ;
void DeleteSchedule() ;
void DeleteEvent( DatePtr &head, DatePtr target ) ;
void ShowSchedule( int index, Str100 date ) ;
int IsTheDateExist( int index, Str100 date ) ;
/*
  全域變數的宣告
*/
MonthPtr gMonthArray  = new Month[NUM_OF_A_YEAR] ;
AccountPtr gHeadAccount = NULL ;
Str100 gCurrentAccount ;

int main()
{
  Str100 temp, id, pw ;
  cout << "輸入login，登入帳號 " << endl ;
  cout << "輸入register，註冊新帳號 " << endl ;
  cin >> temp ;

  while( strcmp( temp, "login" ) != 0 && strcmp( temp, "register" ) != 0 )
  {
    cout << "指令錯誤！請重新輸入" << endl ;
    cin >> temp ;
  } // while

  OpenAccount() ;

  if( strcmp( temp, "register" ) ==  0 )
  {
    Register() ;
    cout << "帳號註冊完成，請重新開啟程式進行登入" << endl ;
  } // if
  else if ( strcmp( temp, "login" ) ==  0 )
  {
    Login() ;

    OpenData() ;

    cout << "輸入1，以新增行事曆 " << endl ;
    cout << "輸入2，以檢視行事曆 " << endl ;
    cout << "輸入3，以刪除行事曆 " << endl ;
    cout << "輸入exit，以離開" << endl ;

    Str100 instr ;

    cin >> instr ;
    while( strcmp( instr, "exit" ) != 0 )
    {
      if ( strcmp( instr, "1" ) == 0 ) // 新增行事曆
      {
        cout << "開始新增行事曆" << endl ;
        AddSchedule();
      } // if
      else if ( strcmp( instr, "2" ) == 0 ) // 檢視行事曆
      {
        cout << "開始檢視行事曆" << endl ;
        ViewSchedule() ;
      } // else if
      else if ( strcmp( instr, "3" ) == 0 ) // 刪除行事曆
      {
        cout << "開始刪除行事曆" << endl ;
        DeleteSchedule() ;
      } // else if
      else
        cout << "不明指令，請重新輸入。" << endl ;

      cout << "輸入1，以新增行事曆 " << endl ;
      cout << "輸入2，以檢視行事曆 " << endl ;
      cout << "輸入3，以刪除行事曆 " << endl ;
      cout << "輸入exit，以離開" << endl ;
      cin >> instr ;
    } // while
    //WriteScheduleFile() ;
    cout << "謝謝您的使用" << endl ;
  } // else if

  return 0 ;
} // main()

void GetToken( Str100 input, int length )
{
  /*
    一次取一個字元，以免把空白orTAB都當成結束
  */
  memset( input, '\0', STR_MAX_LENGTH ) ;
  for ( int i = 0 ; i < length ; i++ )
  {
    if( cin.peek() == '\n' )
      break ;

    input[i] = cin.get() ;
  } // for

  fflush(stdin) ;
} // GetToken

void OpenAccount()
{
  fstream fin ;
  fin.open( "myAccount.poher", ios::in ) ;

  /*
    如果沒有這個檔案，就代表我們要新增一個存放帳號的list。
    有的話就要把我們之前的帳號讀進來
    預設一定有一組帳號為root，密碼為toor
  */
  if( !fin )
    gHeadAccount = AddNewAccount( "root","toor" ) ;
  else
  {
    /*
      我在myAccount.poher內的帳號密碼是用id___pw的形式存放，所以我也要依照相同方式讀取出來
    */
    Str100 id, pw ;
    AccountPtr walk ;
    while( !fin.eof() )
    {
      fin >> id ;
      fin >> pw ;

      if( gHeadAccount == NULL )
        gHeadAccount = AddNewAccount( id, pw ) ;
      else
      {
        walk = gHeadAccount ;
        while( walk->next != NULL ) walk = walk->next ;
        walk->next = AddNewAccount( id, pw ) ;
      } // else
    } // while

  } // else

} // OpenAccount

AccountPtr AddNewAccount( Str100 id, Str100 pw )
{
  AccountPtr temp = new Account ;
  strcpy( temp->id, id ) ;
  strcpy( temp->pw, pw ) ;
  temp->next = NULL ;

  return temp ;
} // AddNewAccount

void Register()
{
  /*
    此functon負責檢查註冊時帳號是否有重複？
    如果有的話，要請使用者重新輸入帳號。

    創完以後，還要把新創立的帳號寫到我的AccountList內
  */
  Str100 id, pw ;
  cout << "請輸入帳號" << endl ;
  cin >> id ;

  while( !IsAccountRepeat( id ) )
  {
    cout << "帳號重複！！，請輸入另一個帳號" << endl ;
    cin >> id ;
  } // while

  cout << "請輸入密碼" << endl ;
  cin >> pw ;

  AccountPtr walk = gHeadAccount ;
  while( walk->next != NULL )
    walk = walk->next ;
  walk->next = AddNewAccount( id, pw ) ;

  WriteAccountFile() ;
} // Register

void Login()
{
  /*
    請使用者輸入完帳號密碼後，再去比對AccountList內的帳號密碼是否相同，以確保不會出問題。

    最後確定帳號密碼正確後，還要把gCurrentAccount改成該帳號，在新建行事曆時會用到。
  */
  Str100 id, pw ;
  cout << "請輸入帳號" << endl ;
  cin >> id ;
  cout << "請輸入密碼" << endl ;
  cin >> pw ;

  while( !VerifyAccountAndPassword( id, pw ) )
  {
    cout << "帳號或密碼錯誤！請重新輸入帳號密碼" << endl ;
    cout << "請輸入帳號" << endl ;
    cin >> id ;
    cout << "請輸入密碼" << endl ;
    cin >> pw ;
  } // while

  strcpy( gCurrentAccount, id ) ;
//cout << "???????????????   " << gCurrentAccount << "  " << id << endl ;
} // Login

bool IsAccountRepeat( Str100 id )
{
  AccountPtr walk = gHeadAccount ;
  while( walk != NULL )
  {
    if( strcmp( walk->id, id ) == 0 )
      return false ;
    walk = walk->next ;
  } // for

  return true ;
} // IsAccountRepeat

void WriteAccountFile()
{
  ofstream fout ;
  fout.open( "myAccount.poher", ios::out ) ;

  /*
    如果我使用的是
    for( AccountPtr walk = gHeadAccount ; walk != NULL ; walk = walk->next )
      fout << walk->id << "       " << walk->pw << endl ;
    的話，

    那就會導致我寫出去的檔案最後面多了一個換行符號，會導致讀檔的時候出問題，所以要改寫為這樣
  */
  for( AccountPtr walk = gHeadAccount ; walk != NULL ; walk = walk->next )
  {
    fout << walk->id << "       " << walk->pw ;
    if( walk->next != NULL )
      fout << endl ;
  } // for

  fout.close() ;
} // WriteAccountFile

bool VerifyAccountAndPassword( Str100 id, Str100 pw )
{
  AccountPtr walk = gHeadAccount ;
  for( walk ; walk != NULL ; walk = walk->next )
  {
    if( strcmp( walk->id, id ) == 0 && strcmp( walk->pw, pw ) == 0 )
      return true ;
  } // for

  return false ;
} // VerifyAccountAndPassword

void OpenData()
{
  fstream fin ;
  fin.open( "mySchedule.poher", ios::in ) ;

  /*
    不論有沒有行事曆，都要初始化。
    差別只是在於如果我之前已經有個行事曆檔案的話，必須把該檔案的內容複製過來，
    不然我就直接用預設的（空的）行事曆繼續做。
  */
  for( int i = 0 ; i < NUM_OF_A_YEAR ; i++ )
  {
      /*
      特別註明：
      .   是陣列用的
      ->  是pointer用的
      */
    gMonthArray[i].index = ( i + 1 ) ;
    gMonthArray[i].numOfEvent = 0 ;
    gMonthArray[i].below = NULL ;
  } // for

  /*
    如果沒有這個檔案，就代表我們要新增一個queue。
    有的話就要把我們之前的行事曆讀進來
  */

  if( !fin )
    cout << "找不到行事曆，重新創造一個新的" << endl ;
  else
  {
    /*
      先利用我最前面的月份找到該月份在array中的index，
      然後第二筆輸入，可以知道我在該月份有多少個行事曆，
      接著依序輸入日期、創造者、時間、內容的行數、以及內容
    */
    int month, index,numOfEvent, lineOfContent, length ;
    Str100 date, owner, time, event, trash ;

    char inputdata[4096] ;
    char *token, *delim = "●" ;
    Content10 content ;
    DatePtr walk = NULL ;

    cout << "載入之前的行事曆" << endl ;

    while( !fin.eof() )
    {
      fin.getline( inputdata, 4096 ) ;
      //fin >> month ;
      token = strtok( inputdata, delim ) ;
      month = atoi( token ) ;

      index = FindIndex( month ) ;

      //fin >> numOfEvent ;
      token = strtok( NULL, delim ) ;
      numOfEvent = atoi( token ) ;
      gMonthArray[index].numOfEvent = numOfEvent ;

      for( int i = 0 ; i < numOfEvent ; i++ )
      {

        //  這邊開始寫入我的行事曆資訊

        //fin >> date ;
        token = strtok( NULL, delim ) ;
        strcpy( date, token ) ;
        //fin >> owner ;
        token = strtok( NULL, delim ) ;
        strcpy( owner, token ) ;
        //fin >> time ;
        token = strtok( NULL, delim ) ;
        strcpy( time, token ) ;
        //fin >> lineOfContent ;
        token = strtok( NULL, delim ) ;
        lineOfContent = atoi( token ) ;

        for( int j = 0 ; j < lineOfContent ; j++ )
        {
          //fin >> length ;
          token = strtok( NULL, delim ) ;
          length = atoi( token ) ;
          //fin >> event ;
          token = strtok( NULL, delim ) ;
          strcpy( event, token ) ;

          strncpy( content[j].content, event, length ) ;
          content[j].length = length ;
        } // for

        /*
          讀完資料後，將他寫到list內
        */

        if ( gMonthArray[index].below == NULL )
          gMonthArray[index].below = CreateDateEvent( date, owner, time, content, lineOfContent ) ;

        else
        {
          walk = gMonthArray[index].below ;
          while( walk->next != NULL )
            walk = walk->next ;
          walk->next = CreateDateEvent( date, owner, time, content, lineOfContent ) ;
        } // else

      } // for
    } // while

  } // else

} // OpenData()

int FindIndex( int month )
{
  for( int i = 0 ; i < NUM_OF_A_YEAR ; i++ )
  {
    if( ( i + 1 ) == month )
      /*
        因為陣列是從0開始計算，所以假如我要找10月，那他的index應該是9
      */
      return i ;
  } // for
} // FindIndex

void AddSchedule()
{
  /*
    ptr代表的是我的月份陣列，index會直接指向該陣列的位置，
    並把我新增的行事曆加到該月份的below的最下面
  */
  int index = 0 ; // 用來表示我現在新增的行事曆是在哪個月份用的
  Str100 date ; // 用來儲存日期
  Str100 time ; // 用來儲存時間
  Content10 content ;
  int lineOfContent = 0 ;

  KeyinScheduleDate( index, date ) ;
  KeyinScheduleTime( time ) ;
  KeyinScheduleContent( lineOfContent, content ) ;
/*
  cout << index<<"     "<<date << "  " << time << endl;

  cout << "創造者 : " << gCurrentAccount << endl ;
  cout << "內容共有 " << lineOfContent << " 行"  << endl ;
  for( int i = 0 ; i < lineOfContent ; i++ )
    cout << i << "___" << content[i] << endl ;
*/

  if( gMonthArray[index].below == NULL )
  {
    gMonthArray[index].below = CreateDateEvent( date, gCurrentAccount, time, content, lineOfContent ) ;
    gMonthArray[index].numOfEvent++ ;
  } // if
  else
  {
    DatePtr walk = gMonthArray[index].below ;
    while( walk->next != NULL )
      walk = walk->next ;
    walk->next = CreateDateEvent( date, gCurrentAccount, time, content, lineOfContent ) ;
    gMonthArray[index].numOfEvent++ ;
  } // else

/*
  //印出來看看有沒有問題
  for( DatePtr walk = gMonthArray[index].below ; walk != NULL ; walk = walk->next  )
  {
    cout << "   sd  " << walk->date << "  " << walk->owner << " " << endl ;
    for( int i = 0 ; i < walk->lineOfContent ; i++ )\
      cout << walk->content[i] << endl ;
  }
*/
  WriteScheduleFile() ;

} // AddSchedule()

int IsInt( Str100 str )
{
  for( int i = 0 ; i < strlen( str ) ; i++ )
  {
    if( str[i] < 48 || str[i] > 57 ) // 分別代表ascii code的0和9
      return NOT_A_INTEGER ;
  } // for
  return atoi( str ) ;
} // IsInt

void KeyinScheduleDate( int &index, Str100 date )
{
  /*
    驗證日期並存入date中，要把index回傳回去，因為我們需要知道該筆備忘錄得存在於array中的哪個位址。

    附註：記得要把時間修改過，如果我輸入的是1月1日的話，我應該存成01月01日
  */
  Str100 month, day, temp ;
  cout << "請輸入月份：" << endl ;
  cin >> month ;

  while( CheckMonthAndIndex( month ) < 0 )
  {
    cout << "月份輸入錯誤！！請重新輸入：" << endl ;
    cin >> month ;
  } // while

  index = CheckMonthAndIndex( month ) ;
  if( index >= 0 && index <= 8 )
  {
    /*
      如果我的月份是1月~9月之間的話，要幫他補個0
      而且因為index和實際月份會相差1，所以要用0~8來看
    */
    strcpy( temp, STR_ZERO ) ;
    strcat( temp, month ) ;
    strcpy( month, temp ) ;
  } // if

  cout << "請輸入日期：" << endl ;
  cin >> day ;

  while( CheckDay( index, day ) < 0 )
  {
    cout << "日期輸入錯誤！！請重新輸入：" << endl ;
    cin >> day ;
  } // while

  if( CheckDay( index, day ) >= 1 && CheckDay( index, day ) <= 9 )
  {
    /*
      如果我的日期是1號~9號之間的話，要幫他補個0
    */
    strcpy( temp, STR_ZERO ) ;
    strcat( temp, day ) ;
    strcpy( day, temp ) ;
  } // if

  strcat( month, "月" ) ;
  strcat( day, "日" ) ;
  strcat( month, day ) ;
  strcpy( date, month ) ;

} // KeyinScheduleDate()

int CheckMonthAndIndex( Str100 str )
{
  /*
    這function主要只是在檢查我輸入的月份是否在1~12月之間，
    若是的話就回傳該月份在array中的哪個位置（所以要-1，因為位址是從0開始計算）
    若不是，則回傳WRONG_MONTH的代號
  */
  int num = IsInt( str ) ;
  if( num == NOT_A_INTEGER )  return NOT_A_INTEGER ;
  else if ( num >= 1 && num <= 12 ) return ( num - 1 ) ;
  else  return WRONG_MONTH ;
} // CheckMonthAndIndex()

int CheckDay( int index, Str100 str )
{
  /*
    這function主要只是在檢查我輸入的日期是否合法（依據月份不同也會有所不同），
    若不是，則回傳WRONG_DAY的代號
  */
  int num = IsInt( str ) ;
  if( num == NOT_A_INTEGER )
    return NOT_A_INTEGER ;

  index++ ; // 這裡只是方便我檢查我的code，index等於一就代表一月，如此而已

  if ( index == 2 ) // 二月，比較特別，只有28天
  {
    if( num >= 1 && num <= 28 ) return num ;
    else  return WRONG_DAY ;
  } // if
  else if ( index == 1 || index == 3 || index == 5 || index == 7 || index == 8
            || index == 10 || index == 12 )
  {
    if( num >= 1 && num <= 31 ) return num ;
    else  return WRONG_DAY ;
  } // else if
  else if ( index == 4 || index == 6 || index == 9 || index == 11 )
  {
    if( num >= 1 && num <= 30 ) return num ;
    else  return WRONG_DAY ;
  } // else if

} // CheckDate

void KeyinScheduleTime( Str100 time )
{
  /*
    驗證時間並放入time中。
  */

  Str100 hour, minute, temp ;
  cout << "請輸入時：" << endl ;
  cin >> hour ;

  while( CheckHour( hour ) < 0 )
  {
    cout << "時間（時）輸入錯誤！！，請重新輸入：" << endl ;
    cin >> hour ;
  } // while

  if( CheckHour( hour ) >= 0 && CheckHour( hour ) <= 9 )
  {
    /*
      如果我的小時是0~9之間的話，要幫他補個0
    */
    strcpy( temp, STR_ZERO ) ;
    strcat( temp, hour ) ;
    strcpy( hour, temp ) ;
  } // if

  cout << "請輸入分：" << endl ;
  cin >> minute ;

  while( CheckMinute( minute ) < 0 )
  {
    cout << "時間（分）輸入錯誤！！，請重新輸入：" << endl ;
    cin >> minute ;
  } // while

  if( CheckMinute( minute ) >= 0 && CheckMinute( minute ) <= 9 )
  {
    /*
      如果我的小時是0~9之間的話，要幫他補個0
    */
    strcpy( temp, STR_ZERO ) ;
    strcat( temp, minute ) ;
    strcpy( minute, temp ) ;
  } // if

  strcat( hour, "時" ) ;
  strcat( minute, "分" ) ;
  strcat( hour, minute ) ;
  strcpy( time, hour ) ;

} // KeyinScheduleTime

int CheckHour( Str100 str )
{
  int num = IsInt( str ) ;
  if( num == NOT_A_INTEGER )  return NOT_A_INTEGER ;
  else if ( num >= 0 && num <= 23 )  return num ;
  else  return WRONG_HOUR ;
} // Checkhour

int CheckMinute( Str100 str )
{
  int num = IsInt( str ) ;
  if( num == NOT_A_INTEGER )  return NOT_A_INTEGER ;
  else if ( num >= 0 && num <= 59 )  return num ;
  else  return WRONG_MINUTE ;
} // CheckMinute

void KeyinScheduleContent( int &lineOfContent, Content10 content )
{
  /*
    我會把內容當成一個最多10行的陣列，陣列的每一個元素都屬於一行我輸入的input
    直到我輸入#END時代表我輸入完畢
  */
  Str100 input ;
  int count = 0 ;
  cout << "請輸入內容（最多10行），並以#END為終止記號 " << endl ;
  cout << "一行內容最多100個字元，超過會忽略" << endl ;

  //cin >> input ;
  GetToken( input, STR_MAX_LENGTH ) ; // 這裡要重複一次，把我的\n給讀掉
  GetToken( input, STR_MAX_LENGTH ) ;

  while( strcmp( input, "#END" ) != 0 )
  {
    if( count < 10 )
    {
      //strcpy( content[count], input ) ;
      strncpy( content[count].content, input, strlen( input ) ) ;
      content[count].length = strlen( input ) ;
      count++ ;
     } // if
    else
    {
      cout << "已達到內容輸入行數上限，強制終止" << endl ;
      break ;
    } // else

    GetToken( input, STR_MAX_LENGTH ) ;
    //cin >> input ;
  } // while

  lineOfContent = count ;

} // KeyinScheduleContent

DatePtr CreateDateEvent( Str100 date, Str100 owner, Str100 time,Content10 content, int lineOfContent )
{
  DatePtr temp = new DateEvent ;
  strcpy( temp->date, date ) ;
  strcpy( temp->owner, owner ) ;
  strcpy( temp->time, time ) ;
  temp->lineOfContent = lineOfContent ;
  ContentCopy( temp->content, content, lineOfContent ) ;

  return temp ;
} // CreateDateEvent()

void ContentCopy( Content10 content1, Content10 content2, int lineOfContent )
{
  for( int i = 0 ; i < lineOfContent ; i++ )
  {
    content1[i].length = content2[i].length ;
    strncpy( content1[i].content, content2[i].content, content1[i].length ) ;
  } // for
} // ContentCopy

void WriteScheduleFile()
{
  ofstream fout ;
  fout.open( "mySchedule.poher", ios::out ) ;

  for( int i = 0 ; i < NUM_OF_A_YEAR ; i++ )
  {
    fout << gMonthArray[i].index << "●" << gMonthArray[i].numOfEvent << "●" ;
    for( DatePtr walk = gMonthArray[i].below ; walk != NULL ; walk = walk->next )
    {
      fout << walk->date << "●" << walk->owner << "●" << walk->time << "●" << walk->lineOfContent << "●" ;
      for( int j = 0 ; j < walk->lineOfContent ; j++ )
        fout << walk->content[j].length << "●" << walk->content[j].content << "●" ;
    } // for
    /*
      如果我不多加這個if的話，會讓我的檔案多寫出一行換行符號，導致處理比較麻煩
    */
    if( i != ( NUM_OF_A_YEAR - 1 ) )
      fout << endl ;
  } // for

  fout.close() ;
} // WriteScheduleFile

void ViewSchedule()
{
  int index = 0 , numOfEvent = 0 ; // numOfEvent代表我在該日期有多少個事件
  Str100 instr, date ;
  cout << "請問要檢查哪一天的行事曆？" << endl ;
  cout << "輸入1 => 檢查今天、輸入2 => 檢查任意天。" << endl ;
  cin >> instr ;

  while( IsInt( instr ) < 0
        || IsInt( instr ) > 2 )
  {
    cout << "輸入錯誤！請重新輸入" << endl ;
    cin >> instr ;
  } // while

  if( IsInt( instr ) == 1 )
    GetCurrentDate( index, date ) ;
  else if ( IsInt( instr ) == 2 )
    KeyinScheduleDate( index, date ) ;

  ShowSchedule( index, date ) ;

} // ViewSchedule

void GetCurrentDate( int &index ,Str100 date )
{
  Str100 month, day, temp ;
  time_t currentTime = time( NULL ) ;
  struct tm *curTime ;
  curTime = localtime( &currentTime ) ;

  strftime( temp, 100, "%m", curTime ) ;
  strftime( date, 100, "%m月%d日", curTime ) ;
  /*
    因為我的月份一定是index + 1（寫死的）
  */
  index = atoi( temp ) - 1 ;
} // GetCurrentDate

void DeleteSchedule()
{
  int index = 0, numOfEvent = 0 ;
  Str100 date ;

  KeyinScheduleDate( index, date ) ;

  numOfEvent =IsTheDateExist( index, date ) ;

  if( numOfEvent == 0 )
    cout << date << " 沒有事件！！無法刪除" << endl ;
  else
  {
    int count = 0 ;
    DatePtr target = NULL ;
    Str100 input ;
    ShowSchedule( index, date ) ;

    cout << "請問要刪除哪一個事件？（請輸入1～" << numOfEvent << "）" << endl ;
    cin >> input ;

    while( IsInt( input ) > numOfEvent || IsInt( input ) < 0 )
    {
      cout << "輸入錯誤，請重新輸入" << endl ;
      cin >> input ;
    } // while

    /*
      先將walk指向該月份的行事曆的起頭，再來尋找要刪除的節點是哪一個
    */
    target = gMonthArray[index].below ;

    for( target ; target != NULL ; target = target->next )
    {
      if( strcmp( target->date, date ) == 0 )
      {
        count++ ;
        if( count == numOfEvent )
          break ;
      } // if
    } // for
    /*

      i要從一開始，因為我們的事件也是從1開始計算的

    for( int i = 1 ; i < IsInt( input ) ; i++ )
      target = target->next ;
    */
    /*
      要判斷目前登入帳號的人跟該事件的owner是否一致，相同的話才可以刪除
    */

    if( strcmp( target->owner, gCurrentAccount ) == 0 )
    {
      DeleteEvent( gMonthArray[index].below, target ) ;
      gMonthArray[index].numOfEvent-- ;

      //ShowSchedule( index, date );

      WriteScheduleFile() ;
    } // if
    else
      cout << "該事件並非由你創造，無法刪除" << endl ;

  } // else

} // DeleteSchedule

void DeleteEvent( DatePtr &head, DatePtr target )
{
  /*
    特別注意!!!!!!
    找到target以後，要記得把target的next給設成NULL，否則會出問題
  */
  if( target == head )
  {
    if( head->next == NULL )
      head = NULL ;
    else
      head = head->next ;
    target->next = NULL ;
  } // if
  else
  {
    DatePtr walk = head ;
    while( walk->next != NULL )
    {
      if( target == walk->next )
      {
        walk->next = target->next ;
        target->next = NULL ;
        break ;
      } // if

      walk = walk->next ;
    } // while
  } // else

  /*
  delete target ;
  */
  /*
  strcpy( target->date, "" ) ;
  strcpy( target->time, "" ) ;
  strcpy( target->owner, "" ) ;
  for( int i = 0 ; i < target->lineOfContent ; i++ )
    strcpy( target->content[i] ,"" ) ;
  target->lineOfContent = 0 ;
  target->next = NULL ;
  */
  delete target ;

} // DeleteEvent

void ShowSchedule( int index, Str100 date )
{
  int numOfEvent = 0, count = 0 ; // count是用來表示我目前已經印了多少個該日期的節點
  DatePtr walk = NULL ;

  numOfEvent = IsTheDateExist( index, date ) ;

  if( numOfEvent == 0 )
    cout << date  << "並沒有任何事件。" << endl ;
  else
  {
    walk = gMonthArray[index].below ;
    cout << date << " 有 " << numOfEvent << " 個事件。分別為：" << endl ;

    while( walk != NULL )
    {
      if( strcmp( walk->date, date ) == 0 )
      {
        count++ ;

        cout << count << "   " ;

        cout << walk->date << "  " << walk->owner << " " << walk->time << " " << walk->lineOfContent << " " << endl ;
        for( int i = 0 ; i < walk->lineOfContent ; i++ )\
          cout << walk->content[i].content << endl ;

        cout << endl ;
        } // if

      if( count == numOfEvent )
        break ;

      walk = walk->next ;
    } // while
    /*
    for( int i = 0 ; i < numOfEvent ; i++ )
    {
      cout << ( i + 1 ) << "   " ;

      cout << walk->date << "  " << walk->owner << " " << walk->time << " " << walk->lineOfContent << " " << endl ;
      for( int i = 0 ; i < walk->lineOfContent ; i++ )\
        cout << walk->content[i] << endl ;

      cout << endl ;

      walk = walk->next ;
    } // for
    */
  } // else
  cout << endl ;
} // ShowSchedule

int IsTheDateExist( int index, Str100 date )
{
  int count = 0 ;
  DatePtr walk = gMonthArray[index].below ;

  while( walk != NULL )
  {
    if( strcmp( walk->date, date ) == 0 )
      count++ ;
    walk = walk->next ;
  } // while

  return count ;
} // IsTheDateExist
