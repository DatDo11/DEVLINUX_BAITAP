#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

volatile int timer_count = 0;

void sigalrm_handler(int signum) {
    if (signum == SIGALRM) {
        timer_count++; 

        printf("Timer: %d seconds\n", timer_count); 

        if (timer_count >= 10) { 
            printf("Timer reached 10 seconds. Exiting.\n");
            exit(0);
        }

        alarm(1);
    }
}

int main() {
    printf("Starting the SIGALRM timer (counting to 10 seconds)...\n");
 
    signal(SIGALRM, sigalrm_handler);

    
    alarm(1);

    while (1) {
        pause(); 
    }

    return 0;
}