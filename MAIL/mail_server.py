# mail_server.py
import socket
import threading

def handle_mail_client(conn, addr):
    print(f"[MailServer] Connected with: {addr}")
    while True:
        data = conn.recv(1024)
        if not data:
            break
        print(f"[MailServer] Received SMTP message: {data.decode()}")
        conn.sendall(b"250 OK")  # SMTP 성공 응답
    conn.close()

def run_mail_server():
    HOST = '127.0.0.1'
    PORT = 2525 # SMTP 포트

    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as server:
        server.bind((HOST, PORT))
        server.listen()
        print("[MailServer] Waiting for SMTP connection...")
        while True:
            conn, addr = server.accept()
            threading.Thread(target=handle_mail_client, args=(conn, addr)).start()

if __name__ == '__main__':
    run_mail_server()
