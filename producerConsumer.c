#include <stdio.h>
#include <stdlib.h>

#define MAX_CHOICES 100

int mutex = 1;
int full = 0;
int empty = 10;
int x = 0;

void producer()
{
    if (mutex == 1 && empty != 0)
    {
        --mutex;
        ++full;
        --empty;
        x++;
        printf("Producer produces item %d\n", x);
        ++mutex;
    }
    else
    {
        printf("Buffer is full!\n");
    }
}

void consumer()
{
    if (mutex == 1 && full != 0)
    {
        --mutex;
        --full;
        ++empty;
        printf("Consumer consumes item %d\n", x);
        x--;
        ++mutex;
    }
    else
    {
        printf("Buffer is empty\n");
    }
}

int main()
{
    int choices[MAX_CHOICES];
    int numChoices;

    printf("Enter the number of choices: ");
    scanf("%d", &numChoices);

    printf("Enter the choices (1 for Producer, 2 for Consumer):\n");
    for (int i = 0; i < numChoices; i++)
    {
        scanf("%d", &choices[i]);
    }

    for (int i = 0; i < numChoices; i++)
    {
        if (choices[i] == 1)
        {
            producer();
        }
        else if (choices[i] == 2)
        {
            consumer();
        }
        else
        {
            printf("Invalid choice!\n");
        }
    }

    return 0;
}