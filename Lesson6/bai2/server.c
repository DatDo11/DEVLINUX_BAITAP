#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
    int sockfd;
    char buffer[BUFFER_SIZE];
    const char *pong = "PONG from UDP Server";
    struct sockaddr_in servaddr, cliaddr;
    
    // Tạo socket
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }
    
    memset(&servaddr, 0, sizeof(servaddr));
    memset(&cliaddr, 0, sizeof(cliaddr));
    
    // Thông tin server
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(PORT);
    
    // Bind socket với địa chỉ server
    if (bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    
    printf("UDP Server đang lắng nghe trên port %d...\n", PORT);

    socklen_t len = sizeof(cliaddr);
    
    // Nhận dữ liệu (hàm này sẽ block)
    // recvfrom sẽ lưu thông tin của client vào cliaddr
    recvfrom(sockfd, (char *)buffer, BUFFER_SIZE, MSG_WAITALL, (struct sockaddr *) &cliaddr, &len);
    buffer[strcspn(buffer, "\n")] = 0; // Xóa (nếu có)
    printf("Client nói: %s\n", buffer);
        
    // Gửi PONG lại cho client (dùng thông tin cliaddr)
    sendto(sockfd, pong, strlen(pong), 0, (const struct sockaddr *) &cliaddr, len);
    printf("Đã gửi PONG.\n");
        
    close(sockfd);
    return 0;
}