#include <stdio.h>
#include <pthread.h>

long long counter = 0; 

pthread_mutex_t mutex; 


void *increment_counter(void *arg) {
    for (int i = 0; i < 1000000; i++) {
        pthread_mutex_lock(&mutex);

        counter++;

        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

int main() {
    pthread_t threads[3]; 

    for (int i = 0; i < 3; i++) {
        if (pthread_create(&threads[i], NULL, increment_counter, NULL) != 0) {
            perror("Lỗi tạo luồng");
            return 1;
        }
    }
  
    for (int i = 0; i < 3; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("Tất cả luồng đã hoàn thành.\n");
    printf("Giá trị cuối cùng của counter (mong muốn: %lld)\n", counter);


    return 0;
}