/*
Input

輸入的第一列有一個整數 C 代表以下有多少組測試資料。每組資料的第一個整數 N 代表班級總人數 ( 1 <= N <= 1000 )。接下來有N個以空白或換行來間隔的整數，代表每個學生的期末總成績 ( 0 <= 分數 <= 100 )。
　

Output

對每組測試資料輸出一列，算出有多少百分比的學生成績比全班平均高，請四捨五入到小數第三位。
*/

# include<stdio.h>
# include<string.h>
# include<stdlib.h>

main()
{
  int m = 0, n = 0, count = 0 ; // m代表我總共有幾組輸入數據、n代表我一組數據總共有幾個學生的成績
                                // count代表大於平均的人數個數 
  double avg = 0.0, total = 0.0 ;
  double inputArray[100] ;
  memset( inputArray, 0.0, 100 ) ;
  
  scanf( "%d", &m ) ; 
  
  for( int i = 0 ; i < m ; i++ )
  {
    scanf( "%d", &n ) ; // 所以我這一組總共有n個數據
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
    
    printf( "%.3f%%\n", ( count / (double) n ) * 100 ) ; // 要連續兩個%它才會印出% 

    memset( inputArray, 0.0, 100 ) ;
    count = 0 ;
    total = 0.0 ;
    
  } // for
  
  system( "pause" ) ;
  return 0 ; 
} // main()
