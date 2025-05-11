#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#define BUFFER_SIZE 5

int main() {
    int ss, sa;
    char input[BUFFER_SIZE + 1];  // +1 for null-termination
    int ascii_codes[BUFFER_SIZE];
    struct sockaddr_in ssa;

    memset(&ssa, 0, sizeof(ssa));
    ssa.sin_family = AF_INET;
    ssa.sin_addr.s_addr = htonl(INADDR_ANY);
    ssa.sin_port = htons(11234);

    ss = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    bind(ss, (struct sockaddr *)&ssa, sizeof(ssa));
    listen(ss, 5);

    while (1) {
      //연결을 기다리고 연결을 수락
        sa = accept(ss, NULL, NULL);
        if (sa < 0) continue; //실패시

        int len = recv(sa, input, BUFFER_SIZE, 0);
        if (len > 0) {
            input[len] = '\0';
            for (int i = 0; i < len; i++) {
                ascii_codes[i] = (int)input[i];
            }
            // 전송: ASCII 배열 전체 전송
            send(sa, ascii_codes, sizeof(int) * len, 0);
        }

        close(sa);
    }

    close(ss);
    return 0;
}
