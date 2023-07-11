#include<stdio.h> 
#include<stdlib.h> 

int count = 0; 
int fullSlots = 0; 
int emptySlot = 5; 
int mutex = 1; 

int producer()
{
    if(mutex==1 && emptySlot!=0)
    {
        mutex--; 
        fullSlots++; 
        emptySlot--; 
        count++; 
        printf("Producer creates process %d\n", count); 
        mutex++; 
    }
    else
    {
        printf("Buffer is full\n"); 
    }

}
int consumer()
{
    if(mutex==1 && emptySlot!=5)
    {
        mutex--; 
        fullSlots--; 
        emptySlot++; 
        printf("Consumer consumer process %d\n", count); 
        count--; 
        mutex++;
    }
    else
    {
        printf("Buffer is empty\n"); 
    }

}

int main()
{
    int n = 0; 
    while(n!=3)
    {
        printf("1 for Producer, 2 for Consumer, 3 to exit\n"); 
        scanf("%d", &n); 
        if(n==1)
        {
            producer(); 
        }
        else if(n==2)
        {
            consumer(); 
        }
        else if(n==3)
        {
            printf("Ending the problem with %d process in buffer", count); 
            exit(0); 
        }
    }
}