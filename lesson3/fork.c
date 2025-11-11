#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid;
    int status;
    
    pid = fork();
    
    if (pid < 0) {
        
        perror("Fork error");
        exit(1);
    }
    else if (pid == 0) {
        
        printf("PID của con: %d\n", getpid()); 
        sleep(1);
        exit(10); 
    }
    else {
        printf("PID của cha: %d\n", getpid());
        printf("PID của con : %d\n", pid);
        wait(&status);
    
        if (WIFEXITED(status)) {
            int exit_code = WEXITSTATUS(status);
            printf("Mã thoát của tiến trình con: %d\n", exit_code);
        }
        else {
            printf("con fail\n");
        }
        printf("Tiến trình cha kết thúc\n");
    }
    
    return 0;
}