#include <stdio.h>
#include <fcntl.h> // open file
#include <unistd.h> // for write read lseek close
#include <string.h> // for strlen
#include <stdlib.h> // for exit
int main(){
    int fd;
    char buffer[100];
    ssize_t bytes_read, bytes_written;
    fd= open("text.txt", O_RDWR | O_CREAT, 0644);
    if (fd<0){
        perror("open");
        exit(1);
    }

    const char *text ="0";
    bytes_written = write(fd, text,strlen(text));
    if (bytes_written < 0){
        perror("write");
        close(fd);
        exit(1);
    }
     

    if(lseek(fd,0,SEEK_SET)<0){
        perror("lseek");
        close(fd);
        exit(1);

    }

    bytes_read = read(fd,buffer,sizeof(buffer)-1);
    if(bytes_read <0){
        perror("read");
        close(fd);
        exit(1);
    }
    buffer[bytes_read]='\0';
    printf("this is from text \n %s",buffer);
    close(fd);

    return 0;

}