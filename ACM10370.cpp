/*
Input

��J���Ĥ@�C���@�Ӿ�� C �N��H�U���h�ֲմ��ո�ơC�C�ո�ƪ��Ĥ@�Ӿ�� N �N��Z���`�H�� ( 1 <= N <= 1000 )�C���U�Ӧ�N�ӥH�ťթδ���Ӷ��j����ơA�N��C�Ӿǥͪ������`���Z ( 0 <= ���� <= 100 )�C
�@

Output

��C�մ��ո�ƿ�X�@�C�A��X���h�֦ʤ��񪺾ǥͦ��Z����Z�������A�Х|�ˤ��J��p�ƲĤT��C
*/

# include<stdio.h>
# include<string.h>
# include<stdlib.h>

main()
{
  int m = 0, n = 0, count = 0 ; // m�N����`�@���X�տ�J�ƾڡBn�N��ڤ@�ռƾ��`�@���X�Ӿǥͪ����Z
                                // count�N��j�󥭧����H�ƭӼ� 
  double avg = 0.0, total = 0.0 ;
  double inputArray[100] ;
  memset( inputArray, 0.0, 100 ) ;
  
  scanf( "%d", &m ) ; 
  
  for( int i = 0 ; i < m ; i++ )
  {
    scanf( "%d", &n ) ; // �ҥH�ڳo�@���`�@��n�Ӽƾ�
    for ( int j = 0 ; j < n ; j++ )
    {
      scanf( "%lf", &inputArray[j] ) ;
      total = total + inputArray[j] ; 
    } // for     

    avg = total / (double) n ;
    for ( int j = 0 ; j < n ; j++ )
    {
      if ( inputArray[j] > avg )
        count++ ;
    } // for
    
    printf( "%.3f%%\n", ( count / (double) n ) * 100 ) ; // �n�s����%���~�|�L�X% 

    memset( inputArray, 0.0, 100 ) ;
    count = 0 ;
    total = 0.0 ;
    
  } // for
  
  system( "pause" ) ;
  return 0 ; 
} // main()
