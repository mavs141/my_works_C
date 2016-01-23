# include<iostream.h>
# include<math.h>

/*
�D�ءG
Input

��J�i��]�t�F�n�X�C���ո�ơA�C�@�C���@���Ƹ�� i�Aj �C

0< i�Aj < 1,000,000

Output

��C�@���J i , j �A���ӭn��X  i, j �M���� i, j �������ƩҲ��ͪ��ƦC���̤j�� cycle length�C
*/

int findLength( int i ) ;

int main()
{
  int input1 = 0, input2 = 0, theBiggerOne = 0, theLessOne = 0, maxLength = 0 ;

  while ( cin >> input1 >> input2 )
  {
    /*
    ����X�j���Ʀr�M�p���Ʀr�A�w�X�d��C
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
    �M�w�n�d���A�ΰj��@�ӭӥh�ˬd�ӭȪ�length
    */
    for ( int i = theLessOne ; i < theBiggerOne ; i++ )
    {
      if ( maxLength < findLength( i ) )
        maxLength = findLength( i ) ;
    } // for

    cout << input1 << " , " << input2 << " , " << maxLength << endl ;

    /*
    �C���������e�n����maxLength�k0
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
  �Y i == 1  => ����
     i�O���� => i = i/2
     i�O�_�� => i = 3i+1
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
