// UserAgent.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>

#define SERVER_PORT 9000
#define MAILSERVER_PORT 9100
#define BUFFER_SIZE 1024

void send_mail(const char* msg) {
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);
    server_addr.sin_addr.s_addr = INADDR_LOOPBACK;

    connect(sock, (struct sockaddr*)&server_addr, sizeof(server_addr));
    send(sock, msg, strlen(msg), 0);
    close(sock);
}

void fetch_mail() {
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in mail_addr;
    mail_addr.sin_family = AF_INET;
    mail_addr.sin_port = htons(MAILSERVER_PORT);
    mail_addr.sin_addr.s_addr = INADDR_LOOPBACK;

    connect(sock, (struct sockaddr*)&mail_addr, sizeof(mail_addr));
    send(sock, "GET", 3, 0);

    char buffer[BUFFER_SIZE] = {0};
    recv(sock, buffer, sizeof(buffer), 0);
    printf("[UserAgent] Received mail: %s\n", buffer);
    close(sock);
}

int main() {
    char input[BUFFER_SIZE];

    printf("1) Send mail\n2) Fetch mail\n> ");
    fgets(input, sizeof(input), stdin);

    if (input[0] == '1') {
        printf("Enter mail content: ");
        fgets(input, sizeof(input), stdin);
        send_mail(input);
    } else if (input[0] == '2') {
        fetch_mail();
    }

    return 0;
}
