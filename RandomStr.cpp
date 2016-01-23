# include<iostream.h>
# include<time.h>
# include<string.h>

# define STR_LENGTH 100

typedef char Str100[STR_LENGTH] ;

void RandStr( Str100 str ) ;

int main()
{
    srand(time(NULL)) ;
    Str100 str ;
    int a = 0 ;

    while( a < 100 )
    {
        RandStr( str ) ;
        cout << str << endl ;
        a++ ;
    } // while
    return 0 ;
} // main()

void RandStr( Str100 str )
{
    int strLength = 0 ;
    strLength = rand() % 10 ;

    for( int i = 0 ; i < strLength ; i++ )
        str[i] = 'a' + ( rand() % 26 ) ;

    str[strLength] = '\0' ;

} // RandStr())
