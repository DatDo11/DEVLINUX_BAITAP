#include<stdio.h>
 int main( int num, char*argv[]){
    printf("number of argument:%d\n",num);
    for (int i=0; i<num;i++){
        printf("\n argument%d :%s",i,argv[i]);
     }

     return 0;
 }
