/*

��C�@�Ӵ��ժ��I�A�Y�丨�b�Y�x�Τ��A�h��X�U�C�榡���T���G

Point i is contained in figure j
�p�G�Y���I�S�����b����x�Τ��A�h��X�G

Point i is not contained in any figure
�Ъ`�N�G�I�M�x�Ϊ��s���O���ӥL�̥X�{�binput�����ǡC�аѦ�Sample Output

Sample Input

r 8.5 17.0 25.5 -8.5
r 0.0 10.3 5.5 0.0
r 2.5 12.5 12.5 2.5
*
2.0 2.0
4.7 5.3
6.9 11.2
20.0 20.0
17.6 3.2
-5.2 -7.8
9999.9 9999.9


Sample Output

Point 1 is contained in figure 2
Point 2 is contained in figure 2
Point 2 is contained in figure 3
Point 3 is contained in figure 3
Point 4 is not contained in any figure
Point 5 is contained in figure 1
Point 6 is not contained in any figure

*/
////////////////////////////////////////////////////////////////////////

# include<stdio.h>
# include<stdlib.h>
# include<string.h>
# include<math.h>

# define STR_LENGTH 1000

////////////////////////////////////////////////////////////////////////

enum ErrorMsg
{
  INPUT_ERROR
  
};

struct Node
{
  /*
  // num�N��ڬO�ĴX�ӯx�� 
  // value1�Mvalue2�N��x�Ϊ�X�y�нd��
  // value3�Mvalue4�N��x�Ϊ�y�y�нd�� 
  */
  int num ;
  char name[STR_LENGTH] ;
  double value1 ;
  double value2 ;
  double value3 ;
  double value4 ;
  Node *next ;
};

typedef Node* nodePtr ;

////////////////////////////////////////////////////////////////////////
// function�ŧi 

void CreateNode( nodePtr &root, int count, double value1, double value2, double value3, double value4 ) ;
void PointPlace( double point1, double point2, nodePtr root, int count2 ) ;
bool InScope( double num1, double num2, double num3 ) ;
void PrintNode( nodePtr root ) ;

////////////////////////////////////////////////////////////////////////
// global value���ŧi�A�q�`���OErrorMsg�~�|�Ψ�
int gErrorMsg = 0 ; 

////////////////////////////////////////////////////////////////////////

int main()
{
  int count = 0, count2 = 0, ans = 0 ; // count�O�Ψӭp��ثe���X�ӯx�}�Acount2�h�O�p��ڲ{�b�O�ĴX��point 
  double value1 = 0.0, value2 = 0.0, value3 = 0.0, value4 = 0.0, point1 = 0.0, point2 = 0.0  ;
  nodePtr root = NULL ;
  char input[STR_LENGTH] ;
  memset( input, '\0', STR_LENGTH ) ;
  
  /*
  �Ĥ@��while�A�M���B�z�x�}����J 
  */
  while ( 1 )
  {
    scanf( "%s", &input ) ;
    if ( strcmp( input, "*" ) == 0 )      // �x�}��J����
      break ;
    else if ( strcmp( input, "r" ) == 0 ) // ��J���O�x�}��� 
    {
      scanf( "%lf %lf %lf %lf", &value1, &value2, &value3, &value4 ) ; // %f�Ofloat %lf�~�Odouble 
      count++ ;
      
      CreateNode( root, count, value1, value2, value3, value4 ) ;
    } // else if 
    else                                  // Error
      gErrorMsg = INPUT_ERROR ;
  } // while
  
  while( 1 )
  {
    scanf( "%lf %lf", &point1, &point2 ) ;
    if ( point1 == 9999.9 && point2 == 9999.9 )
      break ;
    else
    {
      count2++ ;
      PointPlace( point1, point2, root, count2 ) ;
      
    } // else
  } // while
  
  system( "pause" ) ;
  return 0 ;
} // main()

////////////////////////////////////////////////////////////////////////

void CreateNode( nodePtr &root, int count, double value1, double value2, double value3, double value4 ) 
{
  char str[STR_LENGTH] ;
  memset( str, '\0', STR_LENGTH) ;
  // ��ª�l�� 
  nodePtr temp = new Node ;
  temp->num = 0 ;
  memset( temp->name, '\0', STR_LENGTH ) ;
  temp->value1 = temp->value2 = temp->value3 = temp->value4 = 0.0 ;
  temp->next = NULL ;
  
  // �N�������NODE
  // NodeNum && NodeName 
  temp->num = count ;
  strcpy( temp->name, "figure " ) ;
  sprintf( str, "%d", count ) ;
  strcat( temp->name, str ) ;
  // NodeValue 
  // �S�O�`�N�A�]������J���|�̷Ӥj�p�ƦC�A���O�ڪ����ݭn�̷Ӥj�p�A
  // �ҥH�ڭn�b�o�̶i��P�_�A�Nx�b����p���Ʀr���value1�A����j�����value2
  // ��y�b����p���Ʀr���value3�A����j�����value4 
  if ( value1 < value3 )
  {
    temp->value1 = value1 ;
    temp->value2 = value3 ;
  } // if
  else
  {
    temp->value1 = value3 ;
    temp->value2 = value1 ;
  } // else
  if  ( value2 < value4 )
  {
    temp->value3 = value2 ;
    temp->value4 = value4 ;
  } // if
  else
  {
    temp->value3 = value4 ;
    temp->value4 = value2 ;
  } // else
  
  if ( root == NULL )
    root = temp ;
  else
  {
    nodePtr walk = root ;
    while ( walk->next != NULL )
      walk = walk->next ;
    walk->next = temp ;
  } // else
    
} // CreateNode()

void PrintNode( nodePtr root ) 
{
  nodePtr walk = root ;
  while ( walk != NULL )
  {
    printf( "%s��x�b�d��O%lf��%lf�Ay�b�O%lf��%lf\n", walk->name, walk->value1, walk->value2, walk->value3, walk->value4 ) ;
    walk = walk->next ;
  } // while
} // PrintNode()


void PointPlace( double point1, double point2, nodePtr root, int count2 )
{
  bool canFindAns = false ;
  while ( root != NULL )
  {
    if ( InScope( root->value1, root->value2, point1 )
         && InScope( root->value3, root->value4, point2 ) )
    {
      printf( "Point %d is contained in figure %d\n", count2, root->num ) ;
      canFindAns = true ;
    } // if
    root = root->next ;
  } // while

  if( !canFindAns ) // ��J���I���A����x�Τ� 
    printf( "Point %d is not contained in any figure\n", count2 ) ;
  
} // PointPlace()

bool InScope( double num1, double num2, double num3 ) 
{
  if ( num3 >= num1 
       && num3 <= num2 )
    return true ;
  return false ; 
} // InScope
