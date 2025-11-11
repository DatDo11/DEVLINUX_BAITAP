#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <bits/pthreadtypes.h>

int shared_data = 0; 

pthread_rwlock_t rwlock; 

void *reader_func(void *arg) {
    long id = (long)arg;

    for (int i = 0; i < 3; i++) {
        
        pthread_rwlock_rdlock(&rwlock);
         
       
        printf("Reader %ld: Đang đọc giá trị: %d\n", id, shared_data); 

   
        pthread_rwlock_unlock(&rwlock);
        
        usleep(rand() % 100000); 
    }
    return NULL;
}

void *writer_func(void *arg) {
    long id = (long)arg;

    for (int i = 0; i < 2; i++) {
       
        pthread_rwlock_wrlock(&rwlock);

        
        shared_data++; 
        printf("Writer %ld: Đã ghi giá trị mới: %d\n", id, shared_data); 

       
        pthread_rwlock_unlock(&rwlock);
        
        
        usleep(rand() % 500000); 
    }
    return NULL;
}

int main() {
    pthread_t readers[5], writers[2]; 
    long i;

    if (pthread_rwlock_init(&rwlock, NULL) != 0) {
        perror("Lỗi khởi tạo RW Lock");
        return 1;
    }

    for (i = 0; i < 5; i++) { 
        pthread_create(&readers[i], NULL, reader_func, (void *)(i + 1));
    }

  
    for (i = 0; i < 2; i++) { 
        pthread_create(&writers[i], NULL, writer_func, (void *)(i + 1));
    }

    for (i = 0; i < 5; i++) {
        pthread_join(readers[i], NULL);
    }
    
    for (i = 0; i < 2; i++) {
        pthread_join(writers[i], NULL);
    }
    
    printf("Tất cả Reader và Writer đã hoàn thành.\n");
    printf("Giá trị cuối cùng của tài nguyên: %d\n", shared_data);

    pthread_rwlock_destroy(&rwlock);

    return 0;
}