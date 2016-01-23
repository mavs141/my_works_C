# include<iostream.h>

int main()
{
    int input1 = 0, input2 = 0 ;
    cin >> input1 ;
    cin >> input2 ;

    while( input1 != -1 || input2 != -1 )
    {
        if ( input1 >= input2 )
            cout << "Error Input" << endl ;
        else
        {
            int ans1 = 0, ans2 = 0 ;
            ans1 = input2 - input1 ;
            ans2 = ( input1 + 100 ) - input2 ;

            if ( ans1 < ans2 )
                cout << ans1 << endl ;
            else
                cout << ans2 << endl ;
        } // else
        cin >> input1 ;
        cin >> input2 ;
    } // while

    return 0 ;
}
