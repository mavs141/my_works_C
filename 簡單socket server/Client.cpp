
#include <iostream.h>

#include <Windows.h>
#include <Winsock.h>
#pragma comment(lib, "WSock32.lib")

int main()
{
	cout << "�o�̬OClient��!!\n" << endl ;

	int sockfd , port ;

	struct sockaddr_in serv_addr ;

	char firNum[100] , secNum[100] , oper[100] , theAns[100] , IPaddress[100] ; 

	WSADATA wsaData ;
	WSAStartup( 0x0101, &wsaData ) ; // ��l��

	memset((char*)&serv_addr, 0, sizeof(serv_addr));

	cout << "�п�Jip��m:" << endl ;
	cin >> IPaddress ;

	cout << "�п�JPORT��m:" << endl ;
	cin >> port ;

	serv_addr.sin_family = AF_INET ;
  serv_addr.sin_addr.s_addr = inet_addr( IPaddress ) ;
	serv_addr.sin_port = htons( port ) ;

	//Open a TCP socket

	if ( ( sockfd = socket( AF_INET, SOCK_STREAM, 0 ) ) < 0 )  
	{
		cout << "Client: Can't Open Stream Socket!!" << endl ;
		exit(1);
	} // if

	//Connect to the server
	if ( connect( sockfd , (struct sockaddr *)&serv_addr , sizeof( serv_addr ) ) < 0 )
	{
		cout << "Client: Can't Connect to Server!!" << endl ;
		exit(1);
	}

	cout << "�n�JServer���\!!\n\n\n" << endl ; 

	//Receive message from the server
	//recv(sockfd, prompt, sizeof(prompt), 0);
	//printf("%s\n", prompt);

	//Clinet-Server interaction
	while ( 1 ) // �L�a�j��
	{
		cout << "�п�J�Ĥ@�ӼƦr!!" << endl ;
		cin >> firNum ;
		send( sockfd , firNum , sizeof( firNum ) , 0 ) ;

		if ( firNum[0] == 'e' )
		{
      cout << "���}Server!!" << endl ;
			break;
		} // if

		cout << "�п�J�B��Ÿ�!!" << endl ;
    cin >> oper ;
		send( sockfd , oper , sizeof( oper ) , 0 ) ;

		cout << "�п�J�ĤG�ӼƦr!!" << endl ;
		cin >> secNum ;
		send( sockfd , secNum , sizeof( secNum ) , 0 ) ;

		// �N�H�W����ưe��Server�A�ñN���׶Ǧ^��U������code

		recv( sockfd , theAns , sizeof(theAns) , 0) ;
		cout << "�p�⵲�G�O:" << theAns << endl ;

	} // while // ��e�H��~�|���}while

	//Close the TCP socket
	closesocket( sockfd ) ;

	WSACleanup() ;

	return 0 ;

} // main