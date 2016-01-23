
/*

  ��ƾ��ɮצW�ټg����mySchedule.poher

  Step1�G
    �@�}�l�i�J�{���A�|�߰ݭn�n�J�٬O���U�C
    �p�G�n�n�J => ��J�b���K�X�A�öi�����ҡC
    �p�G�n���U => ��J�Q�ӽЪ��b���K�X�A���ˬd�b���O�_�����ơA�S�����Ƥ~�i�H�ӽСC

    �]�b���W�٬�myAccount.poher�^

  Step2�G
    �n�J����A�|�߰ݬO�n�ϥΤ���\��A�ثe�u�W���F�s�W�B�L�X�H�����}
    �p�G�n�s�W => �s�y�X�@��linked list�]���A��DateEvent�^�å[�b�}�C�U��
    �p�G�n�L�X => ������Ӥ���U���Ҧ���list���L�X�N�n

  �ɥR�G
    "�b��"���@linked list�]���A��Account�^�A�̭��]�t�F�b���H�αK�X�C
    "��ƾ䪺���e"���@linked list�]���A��DateEvent�^�A�̭��]�t�F�Өƥ󪺤���B�гy�̡B�ɶ��B�ƥ��ƥH�Ψƥ󤺮e�C
    "��ƾ䥻��"�h�O�@�Ӱ}�C�A�ڥu�W���F�@�~������ƾ�A�ҥH�u��12�����A�䤤�C�����]�t�F����B�Ӥ������ƾ䪺�ӼơB��ƾ䪺���e

*/
# include<fstream.h>
# include<iostream.h>
# include<string.h>
# include<time.h>
# define STR_MAX_LENGTH 100
# define NUM_OF_A_YEAR 12
# define STR_ZERO "0"

/*
  �ڦۤv�|�Ψ쪺�w�q��
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
  function���ŧi
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
  �����ܼƪ��ŧi
*/
MonthPtr gMonthArray  = new Month[NUM_OF_A_YEAR] ;
AccountPtr gHeadAccount = NULL ;
Str100 gCurrentAccount ;

int main()
{
  Str100 temp, id, pw ;
  cout << "��Jlogin�A�n�J�b�� " << endl ;
  cout << "��Jregister�A���U�s�b�� " << endl ;
  cin >> temp ;

  while( strcmp( temp, "login" ) != 0 && strcmp( temp, "register" ) != 0 )
  {
    cout << "���O���~�I�Э��s��J" << endl ;
    cin >> temp ;
  } // while

  OpenAccount() ;

  if( strcmp( temp, "register" ) ==  0 )
  {
    Register() ;
    cout << "�b�����U�����A�Э��s�}�ҵ{���i��n�J" << endl ;
  } // if
  else if ( strcmp( temp, "login" ) ==  0 )
  {
    Login() ;

    OpenData() ;

    cout << "��J1�A�H�s�W��ƾ� " << endl ;
    cout << "��J2�A�H�˵���ƾ� " << endl ;
    cout << "��J3�A�H�R����ƾ� " << endl ;
    cout << "��Jexit�A�H���}" << endl ;

    Str100 instr ;

    cin >> instr ;
    while( strcmp( instr, "exit" ) != 0 )
    {
      if ( strcmp( instr, "1" ) == 0 ) // �s�W��ƾ�
      {
        cout << "�}�l�s�W��ƾ�" << endl ;
        AddSchedule();
      } // if
      else if ( strcmp( instr, "2" ) == 0 ) // �˵���ƾ�
      {
        cout << "�}�l�˵���ƾ�" << endl ;
        ViewSchedule() ;
      } // else if
      else if ( strcmp( instr, "3" ) == 0 ) // �R����ƾ�
      {
        cout << "�}�l�R����ƾ�" << endl ;
        DeleteSchedule() ;
      } // else if
      else
        cout << "�������O�A�Э��s��J�C" << endl ;

      cout << "��J1�A�H�s�W��ƾ� " << endl ;
      cout << "��J2�A�H�˵���ƾ� " << endl ;
      cout << "��J3�A�H�R����ƾ� " << endl ;
      cout << "��Jexit�A�H���}" << endl ;
      cin >> instr ;
    } // while
    //WriteScheduleFile() ;
    cout << "���±z���ϥ�" << endl ;
  } // else if

  return 0 ;
} // main()

void GetToken( Str100 input, int length )
{
  /*
    �@�����@�Ӧr���A�H�K��ť�orTAB��������
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
    �p�G�S���o���ɮסA�N�N��ڭ̭n�s�W�@�Ӧs��b����list�C
    �����ܴN�n��ڭ̤��e���b��Ū�i��
    �w�]�@�w���@�ձb����root�A�K�X��toor
  */
  if( !fin )
    gHeadAccount = AddNewAccount( "root","toor" ) ;
  else
  {
    /*
      �ڦbmyAccount.poher�����b���K�X�O��id___pw���Φ��s��A�ҥH�ڤ]�n�̷ӬۦP�覡Ū���X��
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
    ��functon�t�d�ˬd���U�ɱb���O�_�����ơH
    �p�G�����ܡA�n�ШϥΪ̭��s��J�b���C

    �Ч��H��A�٭n��s�Хߪ��b���g��ڪ�AccountList��
  */
  Str100 id, pw ;
  cout << "�п�J�b��" << endl ;
  cin >> id ;

  while( !IsAccountRepeat( id ) )
  {
    cout << "�b�����ơI�I�A�п�J�t�@�ӱb��" << endl ;
    cin >> id ;
  } // while

  cout << "�п�J�K�X" << endl ;
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
    �ШϥΪ̿�J���b���K�X��A�A�h���AccountList�����b���K�X�O�_�ۦP�A�H�T�O���|�X���D�C

    �̫�T�w�b���K�X���T��A�٭n��gCurrentAccount�令�ӱb���A�b�s�ئ�ƾ�ɷ|�Ψ�C
  */
  Str100 id, pw ;
  cout << "�п�J�b��" << endl ;
  cin >> id ;
  cout << "�п�J�K�X" << endl ;
  cin >> pw ;

  while( !VerifyAccountAndPassword( id, pw ) )
  {
    cout << "�b���αK�X���~�I�Э��s��J�b���K�X" << endl ;
    cout << "�п�J�b��" << endl ;
    cin >> id ;
    cout << "�п�J�K�X" << endl ;
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
    �p�G�ڨϥΪ��O
    for( AccountPtr walk = gHeadAccount ; walk != NULL ; walk = walk->next )
      fout << walk->id << "       " << walk->pw << endl ;
    ���ܡA

    ���N�|�ɭP�ڼg�X�h���ɮ׳̫᭱�h�F�@�Ӵ���Ÿ��A�|�ɭPŪ�ɪ��ɭԥX���D�A�ҥH�n��g���o��
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
    ���צ��S����ƾ�A���n��l�ơC
    �t�O�u�O�b��p�G�ڤ��e�w�g���Ӧ�ƾ��ɮת��ܡA��������ɮת����e�ƻs�L�ӡA
    ���M�ڴN�����ιw�]���]�Ū��^��ƾ��~�򰵡C
  */
  for( int i = 0 ; i < NUM_OF_A_YEAR ; i++ )
  {
      /*
      �S�O�����G
      .   �O�}�C�Ϊ�
      ->  �Opointer�Ϊ�
      */
    gMonthArray[i].index = ( i + 1 ) ;
    gMonthArray[i].numOfEvent = 0 ;
    gMonthArray[i].below = NULL ;
  } // for

  /*
    �p�G�S���o���ɮסA�N�N��ڭ̭n�s�W�@��queue�C
    �����ܴN�n��ڭ̤��e����ƾ�Ū�i��
  */

  if( !fin )
    cout << "�䤣���ƾ�A���s�гy�@�ӷs��" << endl ;
  else
  {
    /*
      ���Q�Χڳ̫e����������Ӥ���barray����index�A
      �M��ĤG����J�A�i�H���D�ڦb�Ӥ�����h�֭Ӧ�ƾ�A
      ���̧ۨǿ�J����B�гy�̡B�ɶ��B���e����ơB�H�Τ��e
    */
    int month, index,numOfEvent, lineOfContent, length ;
    Str100 date, owner, time, event, trash ;

    char inputdata[4096] ;
    char *token, *delim = "��" ;
    Content10 content ;
    DatePtr walk = NULL ;

    cout << "���J���e����ƾ�" << endl ;

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

        //  �o��}�l�g�J�ڪ���ƾ��T

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
          Ū����ƫ�A�N�L�g��list��
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
        �]���}�C�O�q0�}�l�p��A�ҥH���p�ڭn��10��A���L��index���ӬO9
      */
      return i ;
  } // for
} // FindIndex

void AddSchedule()
{
  /*
    ptr�N���O�ڪ�����}�C�Aindex�|�������V�Ӱ}�C����m�A
    �ç�ڷs�W����ƾ�[��Ӥ����below���̤U��
  */
  int index = 0 ; // �ΨӪ�ܧڲ{�b�s�W����ƾ�O�b���Ӥ���Ϊ�
  Str100 date ; // �Ψ��x�s���
  Str100 time ; // �Ψ��x�s�ɶ�
  Content10 content ;
  int lineOfContent = 0 ;

  KeyinScheduleDate( index, date ) ;
  KeyinScheduleTime( time ) ;
  KeyinScheduleContent( lineOfContent, content ) ;
/*
  cout << index<<"     "<<date << "  " << time << endl;

  cout << "�гy�� : " << gCurrentAccount << endl ;
  cout << "���e�@�� " << lineOfContent << " ��"  << endl ;
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
  //�L�X�Ӭݬݦ��S�����D
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
    if( str[i] < 48 || str[i] > 57 ) // ���O�N��ascii code��0�M9
      return NOT_A_INTEGER ;
  } // for
  return atoi( str ) ;
} // IsInt

void KeyinScheduleDate( int &index, Str100 date )
{
  /*
    ���Ҥ���æs�Jdate���A�n��index�^�Ǧ^�h�A�]���ڭ̻ݭn���D�ӵ��Ƨѿ��o�s�b��array�������Ӧ�}�C

    �����G�O�o�n��ɶ��ק�L�A�p�G�ڿ�J���O1��1�骺�ܡA�����Ӧs��01��01��
  */
  Str100 month, day, temp ;
  cout << "�п�J����G" << endl ;
  cin >> month ;

  while( CheckMonthAndIndex( month ) < 0 )
  {
    cout << "�����J���~�I�I�Э��s��J�G" << endl ;
    cin >> month ;
  } // while

  index = CheckMonthAndIndex( month ) ;
  if( index >= 0 && index <= 8 )
  {
    /*
      �p�G�ڪ�����O1��~9�뤧�����ܡA�n���L�ɭ�0
      �ӥB�]��index�M��ڤ���|�ۮt1�A�ҥH�n��0~8�Ӭ�
    */
    strcpy( temp, STR_ZERO ) ;
    strcat( temp, month ) ;
    strcpy( month, temp ) ;
  } // if

  cout << "�п�J����G" << endl ;
  cin >> day ;

  while( CheckDay( index, day ) < 0 )
  {
    cout << "�����J���~�I�I�Э��s��J�G" << endl ;
    cin >> day ;
  } // while

  if( CheckDay( index, day ) >= 1 && CheckDay( index, day ) <= 9 )
  {
    /*
      �p�G�ڪ�����O1��~9���������ܡA�n���L�ɭ�0
    */
    strcpy( temp, STR_ZERO ) ;
    strcat( temp, day ) ;
    strcpy( day, temp ) ;
  } // if

  strcat( month, "��" ) ;
  strcat( day, "��" ) ;
  strcat( month, day ) ;
  strcpy( date, month ) ;

} // KeyinScheduleDate()

int CheckMonthAndIndex( Str100 str )
{
  /*
    �ofunction�D�n�u�O�b�ˬd�ڿ�J������O�_�b1~12�뤧���A
    �Y�O���ܴN�^�ǸӤ���barray�������Ӧ�m�]�ҥH�n-1�A�]����}�O�q0�}�l�p��^
    �Y���O�A�h�^��WRONG_MONTH���N��
  */
  int num = IsInt( str ) ;
  if( num == NOT_A_INTEGER )  return NOT_A_INTEGER ;
  else if ( num >= 1 && num <= 12 ) return ( num - 1 ) ;
  else  return WRONG_MONTH ;
} // CheckMonthAndIndex()

int CheckDay( int index, Str100 str )
{
  /*
    �ofunction�D�n�u�O�b�ˬd�ڿ�J������O�_�X�k�]�̾ڤ�����P�]�|���Ҥ��P�^�A
    �Y���O�A�h�^��WRONG_DAY���N��
  */
  int num = IsInt( str ) ;
  if( num == NOT_A_INTEGER )
    return NOT_A_INTEGER ;

  index++ ; // �o�̥u�O��K���ˬd�ڪ�code�Aindex����@�N�N��@��A�p���Ӥw

  if ( index == 2 ) // �G��A����S�O�A�u��28��
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
    ���Үɶ��é�Jtime���C
  */

  Str100 hour, minute, temp ;
  cout << "�п�J�ɡG" << endl ;
  cin >> hour ;

  while( CheckHour( hour ) < 0 )
  {
    cout << "�ɶ��]�ɡ^��J���~�I�I�A�Э��s��J�G" << endl ;
    cin >> hour ;
  } // while

  if( CheckHour( hour ) >= 0 && CheckHour( hour ) <= 9 )
  {
    /*
      �p�G�ڪ��p�ɬO0~9�������ܡA�n���L�ɭ�0
    */
    strcpy( temp, STR_ZERO ) ;
    strcat( temp, hour ) ;
    strcpy( hour, temp ) ;
  } // if

  cout << "�п�J���G" << endl ;
  cin >> minute ;

  while( CheckMinute( minute ) < 0 )
  {
    cout << "�ɶ��]���^��J���~�I�I�A�Э��s��J�G" << endl ;
    cin >> minute ;
  } // while

  if( CheckMinute( minute ) >= 0 && CheckMinute( minute ) <= 9 )
  {
    /*
      �p�G�ڪ��p�ɬO0~9�������ܡA�n���L�ɭ�0
    */
    strcpy( temp, STR_ZERO ) ;
    strcat( temp, minute ) ;
    strcpy( minute, temp ) ;
  } // if

  strcat( hour, "��" ) ;
  strcat( minute, "��" ) ;
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
    �ڷ|�⤺�e���@�ӳ̦h10�檺�}�C�A�}�C���C�@�Ӥ������ݩ�@��ڿ�J��input
    ����ڿ�J#END�ɥN��ڿ�J����
  */
  Str100 input ;
  int count = 0 ;
  cout << "�п�J���e�]�̦h10��^�A�åH#END���פ�O�� " << endl ;
  cout << "�@�椺�e�̦h100�Ӧr���A�W�L�|����" << endl ;

  //cin >> input ;
  GetToken( input, STR_MAX_LENGTH ) ; // �o�̭n���Ƥ@���A��ڪ�\n��Ū��
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
      cout << "�w�F�줺�e��J��ƤW���A�j��פ�" << endl ;
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
    fout << gMonthArray[i].index << "��" << gMonthArray[i].numOfEvent << "��" ;
    for( DatePtr walk = gMonthArray[i].below ; walk != NULL ; walk = walk->next )
    {
      fout << walk->date << "��" << walk->owner << "��" << walk->time << "��" << walk->lineOfContent << "��" ;
      for( int j = 0 ; j < walk->lineOfContent ; j++ )
        fout << walk->content[j].length << "��" << walk->content[j].content << "��" ;
    } // for
    /*
      �p�G�ڤ��h�[�o��if���ܡA�|���ڪ��ɮצh�g�X�@�洫��Ÿ��A�ɭP�B�z����·�
    */
    if( i != ( NUM_OF_A_YEAR - 1 ) )
      fout << endl ;
  } // for

  fout.close() ;
} // WriteScheduleFile

void ViewSchedule()
{
  int index = 0 , numOfEvent = 0 ; // numOfEvent�N��ڦb�Ӥ�����h�֭Өƥ�
  Str100 instr, date ;
  cout << "�аݭn�ˬd���@�Ѫ���ƾ�H" << endl ;
  cout << "��J1 => �ˬd���ѡB��J2 => �ˬd���N�ѡC" << endl ;
  cin >> instr ;

  while( IsInt( instr ) < 0
        || IsInt( instr ) > 2 )
  {
    cout << "��J���~�I�Э��s��J" << endl ;
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
  strftime( date, 100, "%m��%d��", curTime ) ;
  /*
    �]���ڪ�����@�w�Oindex + 1�]�g�����^
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
    cout << date << " �S���ƥ�I�I�L�k�R��" << endl ;
  else
  {
    int count = 0 ;
    DatePtr target = NULL ;
    Str100 input ;
    ShowSchedule( index, date ) ;

    cout << "�аݭn�R�����@�Өƥ�H�]�п�J1��" << numOfEvent << "�^" << endl ;
    cin >> input ;

    while( IsInt( input ) > numOfEvent || IsInt( input ) < 0 )
    {
      cout << "��J���~�A�Э��s��J" << endl ;
      cin >> input ;
    } // while

    /*
      ���Nwalk���V�Ӥ������ƾ䪺�_�Y�A�A�ӴM��n�R�����`�I�O���@��
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

      i�n�q�@�}�l�A�]���ڭ̪��ƥ�]�O�q1�}�l�p�⪺

    for( int i = 1 ; i < IsInt( input ) ; i++ )
      target = target->next ;
    */
    /*
      �n�P�_�ثe�n�J�b�����H��Өƥ�owner�O�_�@�P�A�ۦP���ܤ~�i�H�R��
    */

    if( strcmp( target->owner, gCurrentAccount ) == 0 )
    {
      DeleteEvent( gMonthArray[index].below, target ) ;
      gMonthArray[index].numOfEvent-- ;

      //ShowSchedule( index, date );

      WriteScheduleFile() ;
    } // if
    else
      cout << "�Өƥ�ëD�ѧA�гy�A�L�k�R��" << endl ;

  } // else

} // DeleteSchedule

void DeleteEvent( DatePtr &head, DatePtr target )
{
  /*
    �S�O�`�N!!!!!!
    ���target�H��A�n�O�o��target��next���]��NULL�A�_�h�|�X���D
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
  int numOfEvent = 0, count = 0 ; // count�O�ΨӪ�ܧڥثe�w�g�L�F�h�֭ӸӤ�����`�I
  DatePtr walk = NULL ;

  numOfEvent = IsTheDateExist( index, date ) ;

  if( numOfEvent == 0 )
    cout << date  << "�èS������ƥ�C" << endl ;
  else
  {
    walk = gMonthArray[index].below ;
    cout << date << " �� " << numOfEvent << " �Өƥ�C���O���G" << endl ;

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
