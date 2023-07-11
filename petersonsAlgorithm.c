#include<stdio.h> 
#include<stdbool.h> 
#include<pthread.h> 

#define NUM_THREADS 2 
bool flag[2]; 
int turn; 

void thread_func(int thread_id)
{
    int other_thread_id = 1 - thread_id; 
    flag[thread_id] = true; 
    turn = other_thread_id; 

    while(flag[other_thread_id] && turn == other_thread_id)
    ; //wait  
    //Critical Section 
    printf("Thread %d is in Critical Section\n", thread_id); 

    flag[thread_id] = false; 
}

void* thread_entry(void* arg)
{
    int thread_id = (int) arg; 
    thread_func(thread_id); 
    return NULL; 
}

int main()
{
    pthread_t thread[NUM_THREADS]; 
    flag[0] = false; 
    flag[1] = false; 

    for(int i = 0; i<NUM_THREADS; i++)
    {
        pthread_create(&thread[i], NULL, thread_entry, (void*)i ); 
    }
    for(int i = 0; i<NUM_THREADS; i++)
    {
        pthread_join(thread[i], NULL); 
    }
    return 0; 
}