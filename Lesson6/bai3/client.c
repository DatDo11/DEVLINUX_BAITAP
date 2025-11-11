#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>

#define SOCKET_PATH "/tmp/my_stream_socket.sock"
#define BUFFER_SIZE 1024

int main() {
    int sock = 0;
    struct sockaddr_un serv_addr;
    const char *ping = "PING from Unix Stream Client";
    char buffer[BUFFER_SIZE] = {0};

    // Tạo socket
    if ((sock = socket(AF_UNIX, SOCK_STREAM, 0)) < 0) {
        printf("\n Socket creation error \n");
        return -1;
    }

    // Thiết lập địa chỉ server
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sun_family = AF_UNIX;
    strncpy(serv_addr.sun_path, SOCKET_PATH, sizeof(serv_addr.sun_path) - 1);

    // Kết nối
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        printf("\nConnection Failed \n");
        return -1;
    }

    // Gửi PING
    send(sock, ping, strlen(ping), 0);
    printf("Đã gửi PING.\n");

    // Đọc PONG
    read(sock, buffer, BUFFER_SIZE);
    printf("Server nói: %s\n", buffer);

    // Đóng
    close(sock);
    return 0;
}