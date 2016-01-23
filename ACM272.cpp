/*
輸入是若干列的文字，其中有偶數個雙引號（ " ），以 end-of-file 做結束。輸出的文字必須和輸入的一模一樣，除了：

每一組雙引號的第一個 " 必須用兩個 ` 字元（就是 `` ）來代替
每一組雙引號的第二個 " 必須用兩個 ' 字元（ 就是 ''）來代替。

也就是第一個引號一定是用 `` 來代替，再來用 ''，然後用 `` ，接著用 '' ，依此類推。
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main()
{
  char ch = '\0' ;
  bool firstUse = true ;
  
  while( ( ch = getchar() ) != EOF )
  {
    if ( ch == '"' )
    {
      if ( firstUse )
      {
        printf( "``" ) ;
        firstUse = false ;
      } // if 
      else
      {
        printf( "'" ) ;
        firstUse = true ; 
      } // else
    } // if
    else
      printf( "%c", ch ) ;
  } // while
  
  system( "pause" ) ;
  return 0 ;
} // main()

