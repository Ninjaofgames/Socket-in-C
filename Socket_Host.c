#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <winsock2.h>
#include <ws2tcpip.h>

#pragma comment(lib, "Ws2_32.lib")

#define PORT 8080
#define BUFFER_SIZE 1024

int main(){
    WSADATA wsa;
    SOCKET server_fd, new_socket;
    struct sockaddr_in adress;
    int addrlen = sizeof(adress);
    char *msg = "Hello, Client!";

    //Initialize Winsock
    if(WSAStartup(MAKEWORD(2, 2), &wsa) != 0){
        printf("WSAStartup failed\n");
        return 1;
    }

    //1.Create Socket
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == INVALID_SOCKET) {
        printf("Socket creation failed\n");
        return 1;
    }

    //2.Define server adress
    adress.sin_family = AF_INET;
    adress.sin_addr.s_addr = INADDR_ANY;
    adress.sin_port = htons(PORT);

    //3. Bind socket
    if (bind(server_fd, (struct sockaddr *)&adress, sizeof(adress)) == SOCKET_ERROR) {
        printf("Bind failed\n");
        return 1;
    }

    //4. Listen for incoming connections
    if (listen(server_fd, 3) == SOCKET_ERROR) {
        printf("Listen failed\n");
        return 1;
    }

    printf("Server listening on port %d...\n", PORT);

    //5.Accept client connection
    new_socket = accept(server_fd, (struct sockaddr *)&adress, &addrlen);
    if (new_socket == INVALID_SOCKET) {
        printf("Accept failed\n");
        return 1;
    }

    //6. Send msg to client
    send(new_socket, msg, strlen(msg), 0);
    printf("Message sent to client.\n");

    //7. Close socket
    closesocket(new_socket);
    closesocket(server_fd);
    WSACleanup();
    return 0;
}
