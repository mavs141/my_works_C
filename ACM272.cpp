/*
��J�O�Y�z�C����r�A�䤤�����ƭ����޸��] " �^�A�H end-of-file �������C��X����r�����M��J���@�Ҥ@�ˡA���F�G

�C�@�����޸����Ĥ@�� " �����Ψ�� ` �r���]�N�O `` �^�ӥN��
�C�@�����޸����ĤG�� " �����Ψ�� ' �r���] �N�O ''�^�ӥN���C

�]�N�O�Ĥ@�Ӥ޸��@�w�O�� `` �ӥN���A�A�ӥ� ''�A�M��� `` �A���ۥ� '' �A�̦������C
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

