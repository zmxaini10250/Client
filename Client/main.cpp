#include <winsock2.h>
#include <iostream>
using namespace std;

#define PORT 59000
#define IP_ADDRESS "192.168.108.80"

int main(int argc, char * argv[])
{
	WSADATA Ws;
	SOCKET ClientSocket;
	struct sockaddr_in ServerAddr;
	int Ret = 0;
	int AddrLen = 0;
	HANDLE hThread = NULL;


	//Init Windows Socket
	if (WSAStartup(MAKEWORD(2, 2), &Ws) != 0)
	{
		cout << "Init Windows Socket Failed::" << GetLastError() << endl;
		return -1;
	}
	//Create Socket
	ClientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (ClientSocket == INVALID_SOCKET)
	{
		cout << "Create Sockeat Failed::" << GetLastError() << endl;
		return -1;
	}

	ServerAddr.sin_family = AF_INET;
	ServerAddr.sin_addr.s_addr = inet_addr(IP_ADDRESS);
	ServerAddr.sin_port = htons(PORT);
	memset(ServerAddr.sin_zero, 0x00, 8);
	
	Ret = connect(ClientSocket, (struct sockaddr*)&ServerAddr, sizeof(ServerAddr));
	if (Ret == SOCKET_ERROR)
	{
		cout << "Connect Error::" << GetLastError() << endl;
		return -1;
	}
	else
	{
		cout << "连接成功!" << endl;
	}

	while (true)
	{
		char SendBuffer[MAX_PATH] = { 0 };
		char RecvBuffer[MAX_PATH] = { 0 };
		memset(SendBuffer,0, sizeof(SendBuffer));
		cin.getline(SendBuffer, sizeof(SendBuffer));

		Ret = send(ClientSocket, SendBuffer, (int)strlen(SendBuffer), 0);
		if (Ret == SOCKET_ERROR)
		{
			cout << "Send Info Error::" << GetLastError() << endl;
			break;
		}
		//Ret = recv(ClientSocket, RecvBuffer, MAX_PATH, 0);
		//if (Ret == 0 || Ret == SOCKET_ERROR) {
		//	cout << "客户端退出！" << endl;
		//	break;
		//}
		//cout << RecvBuffer << endl;
	}

	closesocket(ClientSocket);
	WSACleanup();

	return 0;
}