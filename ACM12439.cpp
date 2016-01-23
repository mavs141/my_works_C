# include<iostream.h>
# include<string.h>
# define STR_DEFAULT_LENGTH 100

typedef char Str100[STR_DEFAULT_LENGTH] ;

enum
{
    ERROR_INPUT = 32767
} ;

struct Date
{
    int day ;
    int month ;
    unsigned int year ;
} ;

void InitStr( Str100 str ) ;
void InitMyDate( Date &myDate ) ;
void FindMonth( Str100 input, int &month ) ;
int Determine( Date date ) ;
bool IsLeap( Date date ) ;

int main()
{
    /*
        �ŧi
    */
    int dataNum ;
    Str100 temp ;
    Date date1, date2 ;

    /*
        ��l��
    */
    dataNum = 0 ;
    InitStr( temp ) ;
    InitMyDate( date1 ) ;
    InitMyDate( date2 ) ;

    cin >> dataNum ;

    while( dataNum > 0 )
    {
        cin >> temp ;
        FindMonth( temp, date1.month ) ;
        cin >> date1.day ;
        cin >> temp ;
        cin >> date1.year ;

        cin >> temp ;
        FindMonth( temp, date2.month ) ;
        cin >> date2.day ;
        cin >> temp ;
        cin >> date2.year ;

        /*
            �ڭ쥻���Q�k�O�G����Xdate1�`�@�|�g�L�X�Ӷ|�~�A
                            �A��Xdate2�`�@�|�g�L�X�Ӷ|�~�A
                            �̫�N��ӼƦr�۴�A�N�i�H�o��L�̤������X�Ӷ|�~�C

            ����ڶ]�Ldate��o�{�A�p�G�ڰ_�l��l�]�]�N�Odate1�^��n�b2/29�����ܡA�ڷ|�ֺ��@�Ӷ|�~
            �]�]���}�l�����@�Ѥ]�n��^�A�ҥH�ڤ~�n�A�L�X�e�A�h�[�@�^��
        */
        if ( IsLeap( date1 ) )  cout << ( Determine( date2 ) - Determine( date1 ) + 1 ) << endl ;
        else    cout << ( Determine( date2 ) - Determine( date1 ) ) << endl ;
        dataNum-- ;

        /*
            ��l��
        */
        InitStr( temp ) ;
        InitMyDate( date1 ) ;
        InitMyDate( date2 ) ;
    } // while()

    return 0 ;
} // main())

void InitStr( Str100 str )
{
    for( int i = 0 ; i < STR_DEFAULT_LENGTH ; i++ ) str[i] = '\0' ;
} // InitStr()

void InitMyDate( Date &myDate )
{
    myDate.day = 0 ;
    myDate.year = 0 ;
    myDate.month = 0 ;
} // InitMyDate()

void FindMonth( Str100 input, int &month )
{
    if( strcmp( input, "January" ) == 0 )    month = 1 ;
    else if( strcmp( input, "February" ) == 0 )  month = 2 ;
    else if( strcmp( input, "March" ) == 0 )  month = 3 ;
    else if( strcmp( input, "April" ) == 0 )  month = 4 ;
    else if( strcmp( input, "May" ) == 0 )  month = 5 ;
    else if( strcmp( input, "June" ) == 0 )  month = 6 ;
    else if( strcmp( input, "July" ) == 0 )  month = 7 ;
    else if( strcmp( input, "August" ) == 0 )  month = 8 ;
    else if( strcmp( input, "September" ) == 0 )  month = 9 ;
    else if( strcmp( input, "October" ) == 0 )  month = 10 ;
    else if( strcmp( input, "November" ) == 0 )  month = 11 ;
    else if( strcmp( input, "December" ) == 0 )  month = 12 ;
    else    month = ERROR_INPUT ;
} // FindMonth())

int Determine( Date date )
{
    int numOfLeap = date.year ;
    numOfLeap = ( numOfLeap / 4 ) - ( numOfLeap / 100 ) + ( numOfLeap / 400 ) ;

    if ( date.month == 1 )  numOfLeap-- ;
    else if ( date.month == 2 && date.day < 29 )    numOfLeap-- ;

    return numOfLeap ;
} // Determine()

bool IsLeap( Date date )
{
    if ( date.month == 2 && date.day == 29 )    return true ;
    return false ;
} // IsLeap()
