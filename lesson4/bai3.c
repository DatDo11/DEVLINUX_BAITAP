#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h> 

int data = 0; 
int data_ready = 0; 

pthread_mutex_t sync_mutex; 
pthread_cond_t data_cond; 


void *producer_func(void *arg) {
    for (int i = 0; i < 10; i++) {
        
        pthread_mutex_lock(&sync_mutex);

        data = rand() % 100; 
        printf("Producer: Đã sản xuất dữ liệu: %d\n", data);
        data_ready = 1; 

        pthread_cond_signal(&data_cond);

        pthread_mutex_unlock(&sync_mutex);

        sleep(1); 
    }
    return NULL;
}

void *consumer_func(void *arg) {
    for (int i = 0; i < 10; i++) {
      
        pthread_mutex_lock(&sync_mutex);

       
        while (data_ready == 0) {
            printf("Consumer: Đang chờ tín hiệu...\n");
            pthread_cond_wait(&data_cond, &sync_mutex);
        }

       
        printf("Consumer: Đã nhận dữ liệu: %d\n", data);

       
        data_ready = 0;

        
        pthread_mutex_unlock(&sync_mutex);
        
        sleep(1);
    }
    return NULL;
}

int main() {
    pthread_t producer_thread, consumer_thread;

    pthread_create(&producer_thread, NULL, producer_func, NULL);
    pthread_create(&consumer_thread, NULL, consumer_func, NULL);

  
    pthread_join(producer_thread, NULL);
    pthread_join(consumer_thread, NULL);

    printf("Chương trình Producer-Consumer đã hoàn thành.\n");


    return 0;
}