#include <stdio.h>
#include <pthread.h>
#include <stdlib.h> 


void *thread_func(void *arg) {
    pthread_t thread_id = pthread_self();
    printf("Thread với ID %lu đang chạy!\n", (unsigned long)thread_id); 
    return NULL;
}

int main() {
    pthread_t thread1, thread2; 
    printf("Luồng chính đang bắt đầu...\n");

    if (pthread_create(&thread1, NULL, thread_func, NULL) != 0) {
        perror("Lỗi tạo luồng 1");
        return 1;
    }

    if (pthread_create(&thread2, NULL, thread_func, NULL) != 0) {
        perror("Lỗi tạo luồng 2");
        return 1;
    }

    printf("Luồng chính đang đợi luồng 1...\n");
    if (pthread_join(thread1, NULL) != 0) {
        perror("Lỗi join luồng 1");
        return 1;
    }

    printf("Luồng chính đang đợi luồng 2...\n");
    if (pthread_join(thread2, NULL) != 0) {
        perror("Lỗi join luồng 2");
        return 1;
    }

    printf("Cả hai luồng con đã hoàn thành. Luồng chính kết thúc.\n");
    return 0;
}
