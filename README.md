2025.1학기 네트워크수업 소켓과제

1. 서버-클라이언트) 클라이언트가 알파벳 5개이하를 전송하면 서버가 아스키코드로 변환하여 전송해줌
   
2. DNS) 클라이언트가 도메인을 등록하거나, 도메인을 전송하여 IP주소를 찾을 수 있는 프로그램.
   - read -> domain이름을 보면 ip주소를 serverDB에서 찾아서 클라이언트에게 리턴(R,domain)
   - write -> domain이름과 ip주소를 받아 serverDB에 저장.
   - 
3. 메일 전송) user agent(UA), mail server를 통해 메일 서버끼리 서로 메시지를 주고 받는 프로그램
   - user agent와 mail server -> pop3, imap, http중 사용
   - mail server와 mail server -> smtp구현

[실행방법]
0. c코드 컴파일
1. 해당 폴더에 들어가서 ./server &을 통해 server를 백그라운드로 실행. (하나의 컴퓨터에서 서버와 클라이언트를 모두 실행함)
2. 해당 폴더에 들어가서 ./client를 통해 클라이언트 프로그램 실행.
