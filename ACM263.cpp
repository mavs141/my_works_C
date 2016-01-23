/*
    用到的功能：
        1.字串反轉（strrev）      -    需要include string.h
        2.字串轉數字（sprintf）   -    需要include stdio.h
        3.BubbleSort
        4.QuickSort
        5.Swap
        6.enum
        7.typedef
*/

# include<iostream.h>
# include<string.h>
# include<stdio.h>

enum {
    DEFALUT_DIFF = 1000000000
};

typedef char Str100[100] ;

void FindBiggestAndSmallestNum( Str100 input, Str100 ans1, Str100 ans2 ) ;
void QuickSort( Str100 input, int left, int right ) ;
void BubbleSort( Str100 input ) ;
void Swap( char &a, char &b ) ;
bool IsRepeat( unsigned int diff ) ;

unsigned int gLastDiff = DEFALUT_DIFF ;

int main()
{
    int chainLength = 0 ;
    unsigned int num1 = 0, num2 = 0, diff = 0 ;
    Str100 input, theBiggestNum, theSmallestNum ;
    for( int i = 0 ; i < 100 ; i++ )    input[i] = theBiggestNum[i] = theSmallestNum[i] = '\0' ;

    cin >> input ;
    while( strcmp( input, "0" ) != 0 )
    {
        cout << "Original number was " << input << endl ;

        while( !IsRepeat( diff ) )
        {
            FindBiggestAndSmallestNum( input, theBiggestNum, theSmallestNum ) ;

            num1 = atoi( theBiggestNum ) ;
            num2 = atoi( theSmallestNum ) ;

            diff = num1 - num2 ;

            cout << num1 << " - " << num2 << " = " << diff << endl ;
            /*
                sprintf是將數字轉成字串，中間的%u代表的是我的數字是unsigned int
            */
            sprintf( input, "%u", diff ) ;
            chainLength++ ;
        } // while

        cout << "Chain Length " << chainLength << "\n" << endl ;

        /*
            得到答案後，別忘記初始化
        */
        gLastDiff = DEFALUT_DIFF ;
        chainLength = 0 ;

        cin >> input ;
    } // while

    return 0 ;
} // main()

void FindBiggestAndSmallestNum( Str100 input, Str100 ans1, Str100 ans2 )
{
    char tempChar = NULL ;
    Str100 temp ;
    for( int i = 0 ; i < 100 ; i++ )    temp[i] = '\0' ;

    strcpy( temp, input ) ;

    /*
        這邊的Sort會把input的數字大到小排列並放到ans1裡面
    */
    // BubbleSort( temp ) ;
    QuickSort( temp, 0, strlen( temp ) - 1 ) ;
    strcpy( ans1, temp ) ;
    /*
        因為ans1裡面放著大到小，所以把他反過來讀就變成小到大
    */
    strcpy( ans2, ans1 ) ;
    strrev( ans2 ) ;

    /*
    strcpy( temp, input ) ;



        這邊的Sort會把input的數字大到排列並放到ans2裡面

    for( int i = 0 ; i < strlen( temp ) ; i++ )
    {
        for( int j = i + 1 ; j < strlen( temp ) ; j++ )
        {
            if( temp[i] > temp[j] )
            {
                tempChar = temp[i] ;
                temp[i] = temp[j] ;
                temp[j] = tempChar ;
            } // if
        } // for
    } // for

    strcpy( ans2, temp ) ;
    */
} // FindBiggestAndSmallestNum()

void QuickSort( Str100 input, int left, int right )
{
   if ( left >= right )    return ;
    else
    {
        int i = left + 1, j = right, pivot = input[left] ;
        while( 1 )
        {
            while( i <= right  )
            {
                /*
                    這邊來決定Sort是由大到小還是由小到大
                    這邊是由大到小
                */
                if( input[i] < pivot )  break ;
                i++ ;
            } // while

            while( j > left )
            {
                /*
                    這邊來決定Sort是由大到小還是由小到大
                    這邊是由大到小
                */
                if ( input[j] > pivot ) break ;
                    j-- ;
            } // while

            if( i > j ) break ;

            Swap( input[i], input[j] ) ;

        } // while
        Swap( input[left], input[j] ) ;
        QuickSort( input, left, j-1 ) ;
        QuickSort( input, j+1, right ) ;
    } // else

} // QuickSort()

void BubbleSort( Str100 input )
{
    for( int i = 0 ; i < strlen( input ) ; i++ )
    {
        for( int j = i + 1 ; j < strlen( input ) ; j++ )
        {
            if( input[i] < input[j] )
                Swap( input[i], input[j] ) ;
        } // for
    } // for

} // BubbleSort()

void Swap( char &a, char &b )
{
    char temp = a ;
    a = b ;
    b = temp ;
} // Swap()

bool IsRepeat( unsigned int diff )
{
    if ( diff == gLastDiff )    return true ;
    else
    {
        gLastDiff = diff ;
        return false ;
    } // else
} // IsRepeat())
