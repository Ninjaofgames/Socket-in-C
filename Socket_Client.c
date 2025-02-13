#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <winsock2.h>
#include <ws2tcpip.h>

#pragma comment(lib, "Ws2_32.lib") //Link Winsock library

#define PORT 8080
#define BUFFER_SIZE 1024

int main(){
    WSADATA wsa;
    SOCKET sock;
    struct sockaddr_in serv_addr;
    char buffer[BUFFER_SIZE] = {0};

    //Initialize Winsock
    if(WSAStartup(MAKEWORD(2, 2), &wsa) != 0){
        printf("WSAStartup failed\n");
        return 1;
    }

    //1.Create socket
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == INVALID_SOCKET){
        printf("Socket creation failed\n");
        return 1;
    }

    //2.Define server address
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr);

    //3. Connect server
    printf("Connecting to server...\n");
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == SOCKET_ERROR) {
        printf("Connection failed! Error: %d\n", WSAGetLastError());
        return 1;
    }

    //4. Receive msg
    recv(sock, buffer, BUFFER_SIZE, 0);
    printf("Server: %s\n", buffer);

    //5. Clean up
    closesocket(sock);
    WSACleanup();
    return 0;

    // Prevent window from closing immediately
    printf("Press Enter to exit...");
    getchar();
    return 0;
}
