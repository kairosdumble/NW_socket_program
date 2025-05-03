#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h> //소켓과 인터넷에 관련된 라이브러리
#include <arpa/inet.h> //아파넷 관련 함수

void main(){
  int cs;
  char buf[5];
  // sockaddr_in은 ip주소나 포트 번호와 같은 주소 정보를 가지는 구조체
  struct sockaddr_in csa;


  memset(&csa,0,sizeof(csa)); //  csa의 모든 바이트 초기화
  csa.sin_family =AF_INET; //인터넷을 사용하겠다는 의미
  // 서버의 ip주소 설정
  // 127.0.0.1은 루프백 주소로, 클라이언트 & 서버를 같은 컴퓨터에서 실행할 수 있도록함.
  csa.sin_addr.s_addr = inet_addr("127.0.0.1");
  csa.sin_port =htons(11234); //서버의 \포트번호


  //소켓 전송
  cs =socket(PF_INET,SOCK_STREAM,IPPROTO_TCP); //socket open (TCP통신)
  connect(cs, (struct sockaddr *) &csa,sizeof(csa)); //connect with server


  //서버로 부터 메시지 수신
  recv(cs,buf,5,0); //received 5 byte of char
  printf("RECEIVED [%s]\n",buf);


  //연결 종료
  close(cs);
}
