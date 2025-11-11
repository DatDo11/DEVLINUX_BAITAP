#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
    int sockfd;
    char buffer[BUFFER_SIZE];
    const char *ping = "PING from UDP Client";
    struct sockaddr_in servaddr;
    
    // Tạo socket
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }
    
    memset(&servaddr, 0, sizeof(servaddr));
    
    // Thông tin server
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
    servaddr.sin_addr.s_addr = INADDR_ANY; // Gửi tới 127.0.0.1
    
    socklen_t len = sizeof(servaddr);

    // Gửi PING (không cần connect)
    sendto(sockfd, ping, strlen(ping), 0, (const struct sockaddr *) &servaddr, len);
    printf("Đã gửi PING.\n");
        
    // Nhận PONG
    recvfrom(sockfd, (char *)buffer, BUFFER_SIZE, MSG_WAITALL, (struct sockaddr *) &servaddr, &len);
    printf("Server nói: %s\n", buffer);
    
    close(sockfd);
    return 0;
}