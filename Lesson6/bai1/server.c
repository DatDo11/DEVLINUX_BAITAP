#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[BUFFER_SIZE] = {0};
    const char *pong = "PONG from TCP Server";

    // Tạo socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Gắn socket vào port 8080
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY; // Chấp nhận kết nối từ mọi IP
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    // Lắng nghe kết nối
    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    printf("TCP Server đang lắng nghe trên port %d...\n", PORT);

    // Chấp nhận một kết nối
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
        perror("accept");
        exit(EXIT_FAILURE);
    }

    printf("Client đã kết nối.\n");

    // Đọc dữ liệu từ client
    read(new_socket, buffer, BUFFER_SIZE);
    printf("Client : %s\n", buffer);

    // Gửi phản hồi
    send(new_socket, pong, strlen(pong), 0);
    printf("sent PONG.\n");

    // Đóng kết nối
    close(new_socket);
    close(server_fd);
    return 0;
}