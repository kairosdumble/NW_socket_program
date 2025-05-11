#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8000
#define BUF_SIZE 1024

int main() {
    int sock;
    struct sockaddr_in server_addr;
    char buffer[BUF_SIZE]; //
    char recv_buf[BUF_SIZE]; //수신 버퍼

    //소켓 열기(TCP/IP)
    sock = socket(AF_INET, SOCK_STREAM, 0);
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1"); //현재 컴퓨터에서 스스로 통신

    connect(sock, (struct sockaddr*)&server_addr, sizeof(server_addr));

    // 사용자로부터 입력받기(문제열 끝에 붙는 개행문자\0 제거)
    printf("명령 입력 (예: R,naver.com 또는 W,naver.com,1.2.3.4): ");
    fgets(buffer, sizeof(buffer), stdin);
    // strcspn()은 문자열에서 특정문자가 처음나오는 위치를 반환한다.
    buffer[strcspn(buffer, "\n")] = 0;

    //sock소켓을 통해 버퍼의 내용을 전송(문자열의 길이에서 문자열 끝의 널문자까지  전송)
    write(sock, buffer, strlen(buffer) + 1);
    read(sock, recv_buf, sizeof(recv_buf));

    /*
    sizeof :변수나 타입의 크기를 바이트 단위로 반환 ->컴파일 타임에 결정되는 메모리 크기
    strlen : 문자열의 길이를 계산 (널 문자 \0 전까지)->런타임에 결정되는 문자 수
    */
    //서버로 부터 받은 응답을 출력하고 소켓을 닫는다.
    printf("서버 응답: %s\n", recv_buf);
    close(sock);
    return 0;
}
