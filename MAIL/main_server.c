// mainServer.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>

#define PORT 9000
#define BUFFER_SIZE 1024

void handle_client(int client_socket) {
    char buffer[BUFFER_SIZE];
    recv(client_socket, buffer, sizeof(buffer), 0);

    printf("[MainServer] Received: %s\n", buffer);

    // 메일서버로 전달
    int mail_socket = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in mail_addr;
    mail_addr.sin_family = AF_INET;
    mail_addr.sin_port = htons(9100);
    mail_addr.sin_addr.s_addr = INADDR_LOOPBACK;

    connect(mail_socket, (struct sockaddr*)&mail_addr, sizeof(mail_addr));
    send(mail_socket, buffer, strlen(buffer), 0);
    close(mail_socket);

    close(client_socket);
}

int main() {
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    addr.sin_addr.s_addr = INADDR_ANY;

    bind(server_fd, (struct sockaddr*)&addr, sizeof(addr));
    listen(server_fd, 5);
    printf("[MainServer] Running on port %d...\n", PORT);

    while (1) {
        int client_socket = accept(server_fd, NULL, NULL);
        handle_client(client_socket);
    }

    return 0;
}
