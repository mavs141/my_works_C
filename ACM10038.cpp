# include<iostream.h>
# include<math.h>
# define INIT_INT -1

bool IsJolly( int inputArray[3000], int num ) ;

int main()
{
    int num = 0, inputArray[3000] ;
    for( int i = 0 ; i < 3000 ; i++ )
        inputArray[i] = INIT_INT ;

    while( 1 )
    {
        cin >> num ;
        if ( num >= 3000 )
            cout << "輸入太多，超出上限" << endl ;
        else if ( num < 3 )
            cout << "至少要三筆資料才能判斷" << endl ;
        else
        {
            for( int i = 0 ; i < num ; i++ )
                cin >> inputArray[i] ;

            if( IsJolly( inputArray, num ) )
                cout << "Jolly" << endl ;
            else
                cout << "Not Jolly" << endl ;
        } // else

        for( int i = 0 ; i < 3000 ; i++ )
            inputArray[i] = INIT_INT ;
    } // while

    return 0 ;
} // main())

bool IsJolly( int inputArray[3000], int num )
{
    int diff = INIT_INT ;
    for( int i = 0, j = i + 1 ; j < num ; i++, j++ )
    {
        if( i == 0 && j == 1 )
            diff = abs( inputArray[i] - inputArray[j] ) ;
        else
        {
            if( diff == 1 + abs( inputArray[i] - inputArray[j] ) )
               diff = abs( inputArray[i] - inputArray[j] ) ;
            else
                return false ;
        } // else

    } // for
    return true ;
} // IsJolly())
