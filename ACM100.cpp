# include<iostream.h>
# include<math.h>

/*
題目：
Input

輸入可能包含了好幾列測試資料，每一列有一對整數資料 i，j 。

0< i，j < 1,000,000

Output

對每一對輸入 i , j 你應該要輸出  i, j 和介於 i, j 之間的數所產生的數列中最大的 cycle length。
*/

int findLength( int i ) ;

int main()
{
  int input1 = 0, input2 = 0, theBiggerOne = 0, theLessOne = 0, maxLength = 0 ;

  while ( cin >> input1 >> input2 )
  {
    /*
    先找出大的數字和小的數字，定出範圍。
    */
    if ( input1 > input2 )
    {
      theBiggerOne = input1 ;
      theLessOne = input2 ;
    } // if
    else
    {
      theBiggerOne = input2 ;
      theLessOne = input1 ;
    } // else

    /*
    決定好範圍後，用迴圈一個個去檢查該值的length
    */
    for ( int i = theLessOne ; i < theBiggerOne ; i++ )
    {
      if ( maxLength < findLength( i ) )
        maxLength = findLength( i ) ;
    } // for

    cout << input1 << " , " << input2 << " , " << maxLength << endl ;

    /*
    每次做完之前要先把maxLength歸0
    */
    maxLength = 0 ;

  } // while

  // system( "pause" ) ;
  return 0 ;
} // main()

int findLength( int i )
{
  int count = 1 ;

  /*
  若 i == 1  => 結束
     i是偶數 => i = i/2
     i是奇數 => i = 3i+1
  */
  while ( 1 )
  {
    if ( i == 1 )
      return count ;
    else if ( i % 2 == 0 )
    {
      i = i / 2 ;
      count++ ;
    } // else if
    else
    {
      i = ( 3 * i ) + 1 ;
      count++ ;
    } // else
  } // while

} // findLength()
