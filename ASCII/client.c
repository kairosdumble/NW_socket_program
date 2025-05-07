// client.c
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUFFER_SIZE 5

int main() {
    int cs;
    char input[BUFFER_SIZE + 1];
    int ascii_codes[BUFFER_SIZE];
    struct sockaddr_in csa;

    memset(&csa, 0, sizeof(csa));
    csa.sin_family = AF_INET;
    csa.sin_addr.s_addr = inet_addr("127.0.0.1");
    csa.sin_port = htons(11234);
    //연결
    cs = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    connect(cs, (struct sockaddr *)&csa, sizeof(csa));
    //입력 받고 전송
    printf("5개 이하의 알파벳을 입력하세요: ");
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = '\0';
    //수신
    send(cs, input, strlen(input), 0);
    int recv_len = recv(cs, ascii_codes, sizeof(ascii_codes), 0);
    int count = recv_len / sizeof(int);
    printf("받은 ASCII 코드: ");
    for (int i = 0; i < count; i++) {
        printf("%d ", ascii_codes[i]);
    }
    printf("\n");

    close(cs);
    return 0;
}


/*strlen()을 사용하는 이유
- buf는 뮨자열 이기 때문에 문자열의 끝은 '/0'로 표시됨.
- 하지만 send()는 문자열이 아니라 메모리상의 바이트 스트림을 전송함으로 '/0'을 기준으로
길이를 계산하지 않음
-strlen(buf)는 '/0'이전 까지의 실제 문자열 길이를 반환함으로 필요한 만큼만 전송할 수 있듬.
-쓰면 안되는 경우 : 쓰레기 값이 들어가는데 읽게되는 경우
*/
