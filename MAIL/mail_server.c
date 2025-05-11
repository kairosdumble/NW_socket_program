// mailServer.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>

#define PORT 9100
#define BUFFER_SIZE 1024

char stored_mail[BUFFER_SIZE];

void handle_connection(int client_socket) {
    char buffer[BUFFER_SIZE] = {0};
    recv(client_socket, buffer, sizeof(buffer), 0);

    if (strncmp(buffer, "GET", 3) == 0) {
        // IMAP 요청
        send(client_socket, stored_mail, strlen(stored_mail), 0);
    } else {
        // SMTP 요청
        strcpy(stored_mail, buffer); // 메일 저장
        printf("[MailServer] Mail stored: %s\n", stored_mail);
    }

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
    printf("[MailServer] Running on port %d...\n", PORT);

    while (1) {
        int client_socket = accept(server_fd, NULL, NULL);
        handle_connection(client_socket);
    }

    return 0;
}
