
#include <stdio.h>
#include <iostream.h>

#include <stdlib.h> 
#include <Winsock.h>
#pragma comment(lib, "WSock32.lib")

#include <Windows.h> // �h�u�Ψ쪺

DWORD WINAPI threadfunc ( LPVOID param )
{
	int newsockfd = *(DWORD*) param ;
	char firNum[100] , secNum[100] , oper[100] , theAns[100] ; 

	//Send message to the clinet

	//Client-Server interaction
  int a, b, c, num1, num2, ans ;

	for( ; ; ) // �L�a�j��A�Q��return/break���X
	{
		recv ( newsockfd , firNum , sizeof( firNum ) , 0 ) ;
    a = strlen ( firNum ) ;
		if( firNum[0] =='e' )
		{
			//Close the TCP socket
			cout << newsockfd << " ���}�FServer!!" << endl ;
			closesocket(newsockfd);
			return 0;
		}

		else 
		{
			cout << "����F�Ӧ�" << newsockfd << "���Ĥ@�ӼƦr( " << firNum << " )!!\n" << endl ;
			recv ( newsockfd , oper , sizeof( oper ) , 0 );
			cout << "����F�Ӧ�" << newsockfd << "���B��Ÿ�( " << oper << " )!!\n" << endl ;
			recv ( newsockfd , secNum , sizeof( secNum ) , 0 );
			cout << "����F�Ӧ�" << newsockfd << "���ĤG�ӼƦr( " << secNum << " )!!\n" << endl ;
			cout << "�}�l�p��Ӧ�" << newsockfd << "�����!!" << endl ; 
			b = strlen( oper ) ;
			c = strlen( secNum ) ;

			firNum[a] = '\0' ; // ������쵲���Ÿ�
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

			//sprintf( theAns , "%d" , ans ) ; // �o�̬O��ԣ�ninclude<stdio.h>����]..
			itoa ( ans , theAns , 10 ) ; // itoa : �Nans��10�i���ন�r����theAns
			cout << "���׬O�G " << ans << " !!" << endl ;

			send( newsockfd , theAns , sizeof( theAns ), 0 ) ; // ��^client�h

      cout << "�w�N���G�^�ǵ� " << newsockfd << " !!\n" << endl ;
		} // else
	} // for
} // threadfunc

int main()
{
	int port ;
	cout << "�ШM�wPORT!!" << endl ;
	cin >> port ;

	cout << "�o�̬OServer��!! (��Server��PORT�� "<< port << " )\n" << endl ;

	int sockfd , newsockfd , clilen ;
	struct sockaddr_in cli_addr , serv_addr ;

	HANDLE thread;
	DWORD thrdparam ; // �ŧi���o�ˬO���F��thread threadid

	WSADATA wsaData ;
	WSAStartup ( 0x0101 , &wsaData ) ; // ��l��

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

		cout << newsockfd << " �n�J!!\n" << endl ;

    /********************�h�u********************/
		thrdparam = newsockfd ;
		thread = CreateThread ( NULL, // �w�]��thread�ݩ�
												  	0, // �w�]��stack size(1MB)
														threadfunc, // �o�ӫ��Ы��V�n�h�u���a�誺��m
														&thrdparam,  // �����Ѽ�
														0, // �w�]��flag
														NULL ) ;  // �Nthread��id�^��

		if ( thread == NULL )
		{
			cout << "Server: Create Thread Failed" << endl ;
			exit(1);
		} // if
	} // for

	return 0;
} // main