
#include <stdio.h>
#include <iostream.h>

#include <stdlib.h> 
#include <Winsock.h>
#pragma comment(lib, "WSock32.lib")

#include <Windows.h> // 多工用到的

DWORD WINAPI threadfunc ( LPVOID param )
{
	int newsockfd = *(DWORD*) param ;
	char firNum[100] , secNum[100] , oper[100] , theAns[100] ; 

	//Send message to the clinet

	//Client-Server interaction
  int a, b, c, num1, num2, ans ;

	for( ; ; ) // 無窮迴圈，利用return/break跳出
	{
		recv ( newsockfd , firNum , sizeof( firNum ) , 0 ) ;
    a = strlen ( firNum ) ;
		if( firNum[0] =='e' )
		{
			//Close the TCP socket
			cout << newsockfd << " 離開了Server!!" << endl ;
			closesocket(newsockfd);
			return 0;
		}

		else 
		{
			cout << "收到了來自" << newsockfd << "的第一個數字( " << firNum << " )!!\n" << endl ;
			recv ( newsockfd , oper , sizeof( oper ) , 0 );
			cout << "收到了來自" << newsockfd << "的運算符號( " << oper << " )!!\n" << endl ;
			recv ( newsockfd , secNum , sizeof( secNum ) , 0 );
			cout << "收到了來自" << newsockfd << "的第二個數字( " << secNum << " )!!\n" << endl ;
			cout << "開始計算來自" << newsockfd << "的資料!!" << endl ; 
			b = strlen( oper ) ;
			c = strlen( secNum ) ;

			firNum[a] = '\0' ; // 讓它找到結束符號
			oper[b] = '\0' ; 
			secNum[c] = '\0' ;
			num1 = atof( firNum ) ;
			num2 = atof( secNum ) ;

			if ( oper[0] == '+' ) 
				ans = ( num1 + num2 ) ;
			else if ( oper[0] == '-' )
				ans = ( num1 - num2 ) ;
			else if ( oper[0] == '*' )
				ans = ( num1 * num2 ) ;
			else if ( oper[0] == '/' )
			  ans = ( num1 / num2 ) ;

			//sprintf( theAns , "%d" , ans ) ; // 這裡是為啥要include<stdio.h>的原因..
			itoa ( ans , theAns , 10 ) ; // itoa : 將ans用10進位轉成字串丟到theAns
			cout << "答案是： " << ans << " !!" << endl ;

			send( newsockfd , theAns , sizeof( theAns ), 0 ) ; // 丟回client去

      cout << "已將結果回傳給 " << newsockfd << " !!\n" << endl ;
		} // else
	} // for
} // threadfunc

int main()
{
	int port ;
	cout << "請決定PORT!!" << endl ;
	cin >> port ;

	cout << "這裡是Server端!! (本Server的PORT為 "<< port << " )\n" << endl ;

	int sockfd , newsockfd , clilen ;
	struct sockaddr_in cli_addr , serv_addr ;

	HANDLE thread;
	DWORD thrdparam ; // 宣告成這樣是為了做thread threadid

	WSADATA wsaData ;
	WSAStartup ( 0x0101 , &wsaData ) ; // 初始化

	memset ( (char*)&serv_addr , 0 , sizeof( serv_addr ) ) ;


	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = htonl( INADDR_ANY );
	serv_addr.sin_port = htons( port );

	//Open a TCP socket
	if ( ( sockfd = socket( AF_INET , SOCK_STREAM , 0 ) ) < 0 )
	{
		cout << "Server: Can't Open Stream Socket!!" << endl ;
		exit(1) ;
	} // if


	//Bind our local address so that the clinet can send to us
	if ( bind( sockfd , (struct sockaddr *)&serv_addr , sizeof( serv_addr ) ) < 0 )
	{
		cout << "Server: Can't Bind Local Address" << endl ;
		exit(1);
	} // if

	listen( sockfd , 5 ) ;

	for( ; ; )
	{
		//wait for a connection from a client process
		clilen = sizeof( cli_addr ) ;
		newsockfd = accept( sockfd , (struct sockaddr *)&cli_addr , &clilen ) ; 

		if( newsockfd < 0 )
		{
			cout << "Server: Accept Error " << endl ;
			exit(1);
		} // if

		cout << newsockfd << " 登入!!\n" << endl ;

    /********************多工********************/
		thrdparam = newsockfd ;
		thread = CreateThread ( NULL, // 預設的thread屬性
												  	0, // 預設的stack size(1MB)
														threadfunc, // 這個指標指向要多工的地方的位置
														&thrdparam,  // 它的參數
														0, // 預設的flag
														NULL ) ;  // 將thread的id回傳

		if ( thread == NULL )
		{
			cout << "Server: Create Thread Failed" << endl ;
			exit(1);
		} // if
	} // for

	return 0;
} // main