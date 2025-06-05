# main_server.py
# port번호 변경 필요
import socket

def run_main_server():
    HOST = '127.0.0.1'
    PORT = 14343  # IMAP 포트

    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as server:
        server.bind((HOST, PORT))
        server.listen(1)
        print("[MainServer] Waiting for IMAP connection...")
        conn, addr = server.accept()
        with conn:
            print(f"[MainServer] Connected by {addr}")
            while True:
                data = conn.recv(1024)
                if not data:
                    break
                print(f"[MainServer] Received from UserAgent: {data.decode()}")
                response = f"OK {data.decode()} received"
                conn.sendall(response.encode())

if __name__ == '__main__':
    run_main_server()
