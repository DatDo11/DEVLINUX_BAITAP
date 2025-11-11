#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    pid_t pid;
    pid = fork();
    
    if (pid < 0) {
        perror("Fork failed");
        exit(1);
    }
    else if (pid == 0) {
        
        printf(" PID = %d, PPID  = %d\n", getpid(), getppid());
        sleep(50);
        printf(" PPID  = %d\n", getppid());
        exit(0);
    }
    else {
        exit(0);
    }
    return 0;
}
