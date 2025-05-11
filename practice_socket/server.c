#include <string.h>
#include <unistd.h>
#include <sys/socket.h> //소켓과 인터넷에 관련된 라이브러리
#include <arpa/inet.h> //아파넷 관련 함수

int main(){
  int ss,sa;
  struct sockaddr_in ssa;

  memset(&ssa, 0,sizeof(ssa));
  ssa.sin_family =AF_INET;
  //서버는 클라이언트의 주소를 알 수 없기 떄문에 이렇게 지정
  ssa.sin_addr.s_addr =htonl(INADDR_ANY);
  ssa.sin_port =htons(11234);

  //소켓 열기
  ss = socket(PF_INET,SOCK_STREAM,IPPROTO_TCP);
  //소켓 연결(서버에만 있는 함수
  //하나의 포트에 여러개의 소켓을 연결한다
  //소켓을 연 이후에는 한 번만 사용하면 됨
  bind(ss,(struct sockaddr *) &ssa,sizeof(ssa));

  //클라이 언트 요청이 있을 떄마다 서비스를 제공
  while(1){
    listen(ss,10);
    sa =accept(ss,0,0);
    send(sa,"test",5,0);
    close(sa);
  }
  return 0;
}

