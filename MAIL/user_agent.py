# user_agent.py

import socket

def run_user_agent():
    HOST = '127.0.0.1'
    PORT = 14343  # MainServer의 IMAP 포트

    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
        s.connect((HOST, PORT))
        print("[UserAgent] Connected to MainServer")
        while True:
            msg = input("[UserAgent] Send IMAP command: ")
            if msg.lower() == "exit":
                break
            s.sendall(msg.encode())
            data = s.recv(1024)
            print(f"[UserAgent] Response from MainServer: {data.decode()}")

if __name__ == '__main__':
    run_user_agent()
