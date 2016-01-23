/*

對每一個測試的點，若其落在某矩形內，則輸出下列格式的訊息：

Point i is contained in figure j
如果某個點沒有落在任何矩形內，則輸出：

Point i is not contained in any figure
請注意：點和矩形的編號是按照他們出現在input的順序。請參考Sample Output

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
  // num代表我是第幾個矩形 
  // value1和value2代表矩形的X座標範圍
  // value3和value4代表矩形的y座標範圍 
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
// function宣告 

void CreateNode( nodePtr &root, int count, double value1, double value2, double value3, double value4 ) ;
void PointPlace( double point1, double point2, nodePtr root, int count2 ) ;
bool InScope( double num1, double num2, double num3 ) ;
void PrintNode( nodePtr root ) ;

////////////////////////////////////////////////////////////////////////
// global value的宣告，通常都是ErrorMsg才會用到
int gErrorMsg = 0 ; 

////////////////////////////////////////////////////////////////////////

int main()
{
  int count = 0, count2 = 0, ans = 0 ; // count是用來計算目前有幾個矩陣，count2則是計算我現在是第幾個point 
  double value1 = 0.0, value2 = 0.0, value3 = 0.0, value4 = 0.0, point1 = 0.0, point2 = 0.0  ;
  nodePtr root = NULL ;
  char input[STR_LENGTH] ;
  memset( input, '\0', STR_LENGTH ) ;
  
  /*
  第一個while，專門處理矩陣的輸入 
  */
  while ( 1 )
  {
    scanf( "%s", &input ) ;
    if ( strcmp( input, "*" ) == 0 )      // 矩陣輸入完畢
      break ;
    else if ( strcmp( input, "r" ) == 0 ) // 輸入的是矩陣資料 
    {
      scanf( "%lf %lf %lf %lf", &value1, &value2, &value3, &value4 ) ; // %f是float %lf才是double 
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
  // 單純初始化 
  nodePtr temp = new Node ;
  temp->num = 0 ;
  memset( temp->name, '\0', STR_LENGTH ) ;
  temp->value1 = temp->value2 = temp->value3 = temp->value4 = 0.0 ;
  temp->next = NULL ;
  
  // 將資料餵給NODE
  // NodeNum && NodeName 
  temp->num = count ;
  strcpy( temp->name, "figure " ) ;
  sprintf( str, "%d", count ) ;
  strcat( temp->name, str ) ;
  // NodeValue 
  // 特別注意，因為它輸入不會依照大小排列，但是我的比對需要依照大小，
  // 所以我要在這裡進行判斷，將x軸比較小的數字放到value1，比較大的放到value2
  // 而y軸比較小的數字放到value3，比較大的放到value4 
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
    printf( "%s的x軸範圍是%lf到%lf，y軸是%lf到%lf\n", walk->name, walk->value1, walk->value2, walk->value3, walk->value4 ) ;
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

  if( !canFindAns ) // 輸入的點不再任何矩形內 
    printf( "Point %d is not contained in any figure\n", count2 ) ;
  
} // PointPlace()

bool InScope( double num1, double num2, double num3 ) 
{
  if ( num3 >= num1 
       && num3 <= num2 )
    return true ;
  return false ; 
} // InScope
