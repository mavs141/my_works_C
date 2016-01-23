
#include <iostream.h>

#include <Windows.h>
#include <Winsock.h>
#pragma comment(lib, "WSock32.lib")

int main()
{
	cout << "這裡是Client端!!\n" << endl ;

	int sockfd , port ;

	struct sockaddr_in serv_addr ;

	char firNum[100] , secNum[100] , oper[100] , theAns[100] , IPaddress[100] ; 

	WSADATA wsaData ;
	WSAStartup( 0x0101, &wsaData ) ; // 初始化

	memset((char*)&serv_addr, 0, sizeof(serv_addr));

	cout << "請輸入ip位置:" << endl ;
	cin >> IPaddress ;

	cout << "請輸入PORT位置:" << endl ;
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

	cout << "登入Server成功!!\n\n\n" << endl ; 

	//Receive message from the server
	//recv(sockfd, prompt, sizeof(prompt), 0);
	//printf("%s\n", prompt);

	//Clinet-Server interaction
	while ( 1 ) // 無窮迴圈
	{
		cout << "請輸入第一個數字!!" << endl ;
		cin >> firNum ;
		send( sockfd , firNum , sizeof( firNum ) , 0 ) ;

		if ( firNum[0] == 'e' )
		{
      cout << "離開Server!!" << endl ;
			break;
		} // if

		cout << "請輸入運算符號!!" << endl ;
    cin >> oper ;
		send( sockfd , oper , sizeof( oper ) , 0 ) ;

		cout << "請輸入第二個數字!!" << endl ;
		cin >> secNum ;
		send( sockfd , secNum , sizeof( secNum ) , 0 ) ;

		// 將以上的資料送到Server，並將答案傳回到下面那行code

		recv( sockfd , theAns , sizeof(theAns) , 0) ;
		cout << "計算結果是:" << theAns << endl ;

	} // while // 按e以後才會離開while

	//Close the TCP socket
	closesocket( sockfd ) ;

	WSACleanup() ;

	return 0 ;

} // main