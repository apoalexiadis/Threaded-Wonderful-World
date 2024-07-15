#include <stdio.h>
#include <pthread.h>

// �������������� condition variables ��� ��� ����������� ��� threads ��� �� ���� �������������:
////���������� ���������� ��������� ���������: �� condition variables ���������� ��� threads �� ���������� ������������� �������� ���� ����������, ���� ��� ����������� ��� ���������� ���� ����������� ��������� ������ ��� threads.
//����������� �����������: ���� �������������� condition variables, � ����������� ��� ������������ ����� ��� ���������� ��� ����������, ����� �� threads ��������������� ���� ���� ���������� �� ���������� ��������.
//�������� ���������������: � ����� condition variables ����� ��� ������ ��� ��������� ���� ����� �� ����� ��������� ��� ��� ��������������� ������ ��� threads.


// Mutexes ��� ��� condition variables
pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex2 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex3 = PTHREAD_MUTEX_INITIALIZER;

// Condition variables ��� ���� �������
pthread_cond_t cond1 = PTHREAD_COND_INITIALIZER;
pthread_cond_t cond2 = PTHREAD_COND_INITIALIZER;
pthread_cond_t cond3 = PTHREAD_COND_INITIALIZER;

// ����� flag ��� ��� ��������� ��� threads
int flag = 0;

// ������������ ��� �����������
void* printWhatA(void* );
void* printWonderful(void* );
void* printWorld(void* );

int main() {
    pthread_t thread1, thread2, thread3;

    // ���������� ��� threads
    pthread_create(&thread1, NULL, printWhatA, NULL);
    pthread_create(&thread2, NULL, printWonderful, NULL);
    pthread_create(&thread3, NULL, printWorld, NULL);

    // ������� ����������� ��� threads
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    pthread_join(thread3, NULL);

    return 0;
}

// ���������� ���� thread ��� �������� "What A "
void* printWhatA(void* arg) {
    
	while (1) {
    	
        // �������� ��� mutex1 ��� ��������� ��� ������ flag ��� ��� condition variable cond1
        pthread_mutex_lock(&mutex1);
        
        // �� thread ��������� ����� �� ����� ������ �� ��������� �� ����� ������ ���
        while (flag != 0) {
            pthread_cond_wait(&cond1, &mutex1); // ������������ ��� mutex1 ���� ��� �������
        }
        
        // �������� ��� �������� "What A "
        printf("What A ");
        
        // ������ ��� flag ��� ��� ������� ��������� ��� ������������
        flag = 1;
        
        // ���������� ��� �������� thread (printWonderful) �� ���������
        pthread_cond_signal(&cond2);
        
        // ������������ ��� mutex1 ���� ��� ���������� ��� �������� ������
        pthread_mutex_unlock(&mutex1);
    }
       
    return NULL;
}

// ���������� ���� thread ��� �������� "Wonderful "
void* printWonderful(void* arg) {
    while (1) {
        // �������� ��� mutex2 ��� ��������� ��� ������ flag ��� ��� condition variable cond2
        pthread_mutex_lock(&mutex2);
        
        // �� thread ��������� ����� �� ����� ������ �� ��������� �� ����� ������ ���
        while (flag != 1) {
            pthread_cond_wait(&cond2, &mutex2); // ������������ ��� mutex2 ���� ��� �������
        }
        
        // �������� ��� �������� "Wonderful "
        printf("Wonderful ");
        
        // ������ ��� flag ��� ��� ������� ��������� ��� ������������
        flag = 2;
        
        // ���������� ��� �������� thread (printWorld) �� ���������
        pthread_cond_signal(&cond3);
        
        // ������������ ��� mutex2 ���� ��� ���������� ��� �������� ������
        pthread_mutex_unlock(&mutex2);
    }
    return NULL;
}

// ���������� ���� thread ��� �������� "World! "
void* printWorld(void* arg) {
    while (1) {
        // �������� ��� mutex3 ��� ��������� ��� ������ flag ��� ��� condition variable cond3
        pthread_mutex_lock(&mutex3);
        
        // �� thread ��������� ����� �� ����� ������ �� ��������� �� ����� ������ ���
        while (flag != 2) {
            pthread_cond_wait(&cond3, &mutex3); // ������������ ��� mutex3 ���� ��� �������
        }
        
        // �������� ��� �������� "World! "
        printf("World! ");
        
        // ������ ��� flag ��� ��� ������� ��������� ��� ������������
        flag = 0;
        
        // ���������� ��� �������� thread (printWhatA) �� ���������
        pthread_cond_signal(&cond1);
        
        // ������������ ��� mutex3 ���� ��� ���������� ��� �������� ������
        pthread_mutex_unlock(&mutex3);
        
    }
    return NULL;
}

