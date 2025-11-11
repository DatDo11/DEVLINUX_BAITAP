#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

volatile int sigint_count = 0;

void sigint_handler(int signum) {
    if (signum == SIGINT) {
        sigint_count++; 
        printf("\nSIGINT received. (Count: %d)\n", sigint_count); 

        if (sigint_count >= 3) {
            printf("Received SIGINT 3 times. Exiting program.\n");
            exit(0); 
        }
    }
}

int main() {
    printf("Program is running. Press Ctrl+C to send SIGINT signal.\n");
    printf("The program will exit after receiving SIGINT 3 times.\n");

    
    if (signal(SIGINT, sigint_handler) == SIG_ERR) {
        perror("Could not set up signal handler");
        return 1;
    }

   
    while (1) {
        sleep(1); 
    }

    return 0;
}