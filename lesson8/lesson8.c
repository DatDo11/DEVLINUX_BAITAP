#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define READ_END 0
#define WRITE_END 1

int main(void) {
    int pipefd[2];
    pid_t pid1, pid2;

    // 1. Tạo Pipe: Trong tiến trình cha, gọi pipe()
    if (pipe(pipefd) == -1) {
        perror("Lỗi tạo pipe");
        exit(EXIT_FAILURE);
    }

    // 2. Tạo Tiến trình con 1 (ls -1)
    pid1 = fork();
    if (pid1 == -1) {
        perror("Lỗi fork con 1");
        exit(EXIT_FAILURE);
    }

    if (pid1 == 0) { // Mã cho Tiến trình con 1 (ls -1)
        // Chuyển hướng stdout (file descriptor 1) sang đầu ghi của pipe
        if (dup2(pipefd[WRITE_END], STDOUT_FILENO) == -1) {
            perror("Lỗi dup2 con 1");
            exit(EXIT_FAILURE);
        }

        // Đóng đầu đọc và đầu ghi ban đầu của pipe (chỉ giữ lại STDOUT_FILENO đã được chuyển hướng)
        close(pipefd[READ_END]);
        close(pipefd[WRITE_END]);

        // Thực thi lệnh ls -1
        execlp("ls", "ls", "-1", (char *)NULL);
        
        // Nếu execlp() trả về, có lỗi
        perror("Lỗi execlp ls");
        exit(EXIT_FAILURE);
    }

    // 3. Tạo Tiến trình con 2 (wc -l)
    pid2 = fork();
    if (pid2 == -1) {
        perror("Lỗi fork con 2");
        exit(EXIT_FAILURE);
    }

    if (pid2 == 0) { // Mã cho Tiến trình con 2 (wc -l)
        // Chuyển hướng stdin (file descriptor 0) sang đầu đọc của pipe
        if (dup2(pipefd[READ_END], STDIN_FILENO) == -1) {
            perror("Lỗi dup2 con 2");
            exit(EXIT_FAILURE);
        }

        // Đóng đầu đọc và đầu ghi ban đầu của pipe (chỉ giữ lại STDIN_FILENO đã được chuyển hướng)
        close(pipefd[WRITE_END]);
        close(pipefd[READ_END]);

        // Thực thi lệnh wc -l
        // Lưu ý: -l (chữ L thường) là đếm số dòng
        execlp("wc", "wc", "-l", (char *)NULL);
        
        // Nếu execlp() trả về, có lỗi
        perror("Lỗi execlp wc");
        exit(EXIT_FAILURE);
    }

    // 4. Trong Tiến trình cha
    // Đóng cả hai đầu của pipe trong tiến trình cha
    // Điều này **rất quan trọng** để wc -l (con 2) biết ls -1 (con 1) đã kết thúc dữ liệu (EOF)
    close(pipefd[READ_END]);
    close(pipefd[WRITE_END]);

    // Chờ cả hai tiến trình con kết thúc
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);

    printf("Hai tiến trình con đã hoàn thành. Kết quả đã hiển thị trên terminal.\n");

    return 0;
}