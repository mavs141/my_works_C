# include<iostream.h>
# include<stdlib.h>

typedef char Str100[100] ;

void QuickSort( Str100 input, int left, int right ) ;
void Swap( char &a, char &b ) ;

int main()
{
    Str100 input ;
    for( int i = 0 ; i < 100 ; i++ )    input[i] = '\0' ;

    while( 1 )
    {
        cin >> input ;
        cout << "�Ƨǫe" << endl ;
        cout << input << "\n" << endl ;
        QuickSort( input, 0, strlen( input ) - 1 ) ;
        cout << "�Ƨǫ�" << endl ;
        cout << input << "\n" << endl ;
    } // while()

    return 0 ;
} // main()

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
                    �o��ӨM�wSort�O�Ѥj��p�٬O�Ѥp��j
                    �o��O�Ѥp��j
                */
                if( input[i] > pivot )  break ;
                i++ ;
            } // while

            while( j > left )
            {
                /*
                    �o��ӨM�wSort�O�Ѥj��p�٬O�Ѥp��j
                    �o��O�Ѥp��j
                */
                if ( input[j] < pivot ) break ;
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

void Swap( char &a, char &b )
{
    char temp = a ;
    a  = b ;
    b = temp ;
} // Swap()
