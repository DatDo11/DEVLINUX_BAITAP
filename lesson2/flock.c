#include <stdio.h>
#include <fcntl.h> // open file
#include <unistd.h> // for write read lseek close
#include <string.h> // for strlen
#include <stdlib.h> // for exit
int main(){
    int fd = open("flock.text",O_WRONLY | O_CREAT | O_APPEND, 0644);
    if(fd <0){
        perror("open");
        return 1;
    }
    char buffer[100];
    for(int i = 0; i < 2000;i++)
    {
        sprintf(buffer,"%d \n",i);
        ssize_t bytes_written = write (fd,buffer,strlen(buffer));
        if(bytes_written<0){
            perror("write");
            close(fd);
            exit(1);
        }
        usleep(1000);

    }
    close(fd);
    return 0;

}