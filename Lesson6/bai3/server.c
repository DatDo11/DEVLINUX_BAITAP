#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>

#define SOCKET_PATH "/tmp/my_stream_socket.sock"
#define BUFFER_SIZE 1024

int main() {
    int server_fd, new_socket;
    struct sockaddr_un address;
    int addrlen = sizeof(address);
    char buffer[BUFFER_SIZE] = {0};
    const char *pong = "PONG from Unix Stream Server";

    // Xóa file socket cũ nếu tồn tại
    unlink(SOCKET_PATH);

    // Tạo socket
    if ((server_fd = socket(AF_UNIX, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Thiết lập địa chỉ (là một file path)
    memset(&address, 0, sizeof(address));
    address.sun_family = AF_UNIX;
    strncpy(address.sun_path, SOCKET_PATH, sizeof(address.sun_path) - 1);

    // Bind
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    // Listen
    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    printf("Unix Stream Server đang lắng nghe trên %s...\n", SOCKET_PATH);

    // Accept
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
        perror("accept");
        exit(EXIT_FAILURE);
    }

    printf("Client đã kết nối.\n");

    // Đọc
    read(new_socket, buffer, BUFFER_SIZE);
    printf("Client nói: %s\n", buffer);

    // Gửi
    send(new_socket, pong, strlen(pong), 0);
    printf("Đã gửi PONG.\n");

    // Đóng
    close(new_socket);
    close(server_fd);
    unlink(SOCKET_PATH); // Xóa file socket khi server tắt
    return 0;
}