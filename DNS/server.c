//server.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8000
#define BUF_SIZE 1024
#define DB_FILE "serverDB.txt"

void handle_request(int client_sock) {
    char buffer[BUF_SIZE];
    read(client_sock, buffer, sizeof(buffer));

    char command, domain[256], ip[256];
    int matched = 0; //일치하는지 여부확인

    // 명령 파싱
    if (buffer[0] == 'R') {
        /*
        scanf : 표준입력처리(사용자 입력 처리)
        sscanf : 이미 존재하는 문자열에서 원하는 데이터 추출
        sprintf : 문자열에 포맷대로 출력.버퍼넘침 방지
        - sprintf(buffer, "The answer is %d", value);
        snprintf : 문자열에 포맷대로 출력.버퍼 오버런 방지
        - snprintf(buffer, sizeof(buffer), "The answer is %d", value);
        */
        //받은 메시지로부터 mode와 도메인 추출
        sscanf(buffer, "%c,%s", &command, domain);

        //파일 열기
        FILE *fp = fopen(DB_FILE, "r");
        if (!fp) {
            perror("DB file open error");
            close(client_sock);
            return;
        }

        /*
        %[^,] : 콤마가 나오기 전까지 모든 문자를 읽어서 domain에 저장
        %s:ip에 공백전까지의 문자열을 저장
        \n:줄바꿈 문자도 정확히 읽어야함.
        */
        while (fscanf(fp, "%[^,],%s\n", domain, ip) != EOF) {
            if (strcmp(buffer + 2, domain) == 0) {
                write(client_sock, ip, strlen(ip) + 1);
                matched = 1;
                break;
            }
        }

        fclose(fp);
        if (!matched) {
            char *msg = "해당 도메인은 존재하지 않습니다";
            write(client_sock, msg, strlen(msg) + 1);
        }

    } else if (buffer[0] == 'W') {
        sscanf(buffer, "%c,%[^,],%s", &command, domain, ip);

        FILE *fp = fopen(DB_FILE, "r");
        if (!fp) {
            perror("DB file open error");
            close(client_sock);
            return;
        }

        char db_domain[256], db_ip[256];
        while (fscanf(fp, "%[^,],%s\n", db_domain, db_ip) != EOF) {
            if (strcmp(db_domain, domain) == 0) {
                char *msg = "중복되는 도메인이 있습니다.";
                write(client_sock, msg, strlen(msg) + 1);
                fclose(fp);
                return;
            }
        }
        fclose(fp);

        // 중복이 없으면 append
        fp = fopen(DB_FILE, "a");
        fprintf(fp, "%s,%s\n", domain, ip);
        fclose(fp);

        char *msg = "저장 완료";
        write(client_sock, msg, strlen(msg) + 1);
    }

    close(client_sock);
}

int main() {
    int server_sock = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_len = sizeof(client_addr);

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY; //서버가 어떤 IP주소에서든 연결 요청을 받을 수 있도록 설정하는 코드

    //연결하고(bind) 서버 소켓을 수신 대기 상태로 만듦(listen)
    bind(server_sock, (struct sockaddr *)&server_addr, sizeof(server_addr));
    listen(server_sock, 5); //5는 대기열의 크기
    printf("서버 실행 중...\n");

    //TCP 서버가 클라이언트의 연결 요청을 계속해서
    while (1) {
        //블로킹 함수. 클라이언트가 데이터요청을 보낼때까지 대기
        int client_sock = accept(server_sock, (struct sockaddr *)&client_addr, &addr_len);
        handle_request(client_sock); //함수호출
    }

    close(server_sock);
    return 0;
}
