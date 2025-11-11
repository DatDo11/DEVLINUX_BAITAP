#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>

pid_t child_pid = -1;

void child_sigusr1_handler(int signum) {
    if (signum == SIGUSR1) {
     
        printf("Child Process (PID %d): Received signal from parent.\n", getpid());
    }
}

void parent_process(pid_t pid) {
    int send_count = 0;
    printf("Parent Process (PID %d) started. Child PID: %d\n", getpid(), pid);
    
    child_pid = pid; 

    
    while (send_count < 5) {  
        sleep(2); 

        send_count++;
        printf("Parent Process (PID %d): Sending SIGUSR1 (Count %d) to child %d\n", 
               getpid(), send_count, child_pid);

       
        if (kill(child_pid, SIGUSR1) == -1) {
            perror("Parent: Error sending signal");
            break;
        }
    }

    printf("Parent Process: Finished sending 5 signals. Terminating child and exiting.\n");
   
    kill(child_pid, SIGTERM); 
    wait(NULL); 

    exit(0);
}


void child_process() {
    printf("Child Process (PID %d) started. Waiting for SIGUSR1...\n", getpid());

     
   signal(SIGUSR1, child_sigusr1_handler);
   
    while (1) {
        pause(); 
    }
    
}


int main() {
    pid_t pid;

    pid = fork(); 

    if (pid < 0) {
        perror("fork failed");
        return 1;
    } else if (pid == 0) {
        child_process();
    } else {
        parent_process(pid);
    }

    return 0;
}