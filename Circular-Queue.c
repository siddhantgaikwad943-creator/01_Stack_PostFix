#include <stdio.h>
#define MAX 5

int queue[MAX];
int front = -1;
int rear = -1;

// Enqueue operation
void enqueue()
{
    int value;

    if ((rear + 1) % MAX == front)
    {
        printf("Queue is Full!\n");
        return;
    }

    printf("Enter value: ");
    scanf("%d", &value);

    if (front == -1)
    {
        front = 0;
        rear = 0;
    }
    else
    {
        rear = (rear + 1) % MAX;
    }

    queue[rear] = value;
    printf("%d inserted into queue.\n", value);
}

// Dequeue operation
void dequeue()
{
    int value;

    if (front == -1)
    {
        printf("Queue is Empty!\n");
        return;
    }

    value = queue[front];

    if (front == rear)
    {
        front = -1;
        rear = -1;
    }
    else
    {
        front = (front + 1) % MAX;
    }

    printf("%d deleted from queue.\n", value);
}

// Display operation
void display()
{
    int i;

    if (front == -1)
    {
        printf("Queue is Empty!\n");
        return;
    }

    printf("Circular Queue: ");

    i = front;

    while (1)
    {
        printf("%d ", queue[i]);

        if (i == rear)
            break;

        i = (i + 1) % MAX;
    }

    printf("\n");
}

// Main function
int main()
{
    int choice;

    while (1)
    {
        printf("\n--- CIRCULAR QUEUE ---\n");
        printf("1. Enqueue\n");
        printf("2. Dequeue\n");
        printf("3. Display\n");
        printf("4. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                enqueue();
                break;

            case 2:
                dequeue();
                break;

            case 3:
                display();
                break;

            case 4:
                printf("Program terminated.\n");
                return 0;

            default:
                printf("Invalid choice!\n");
        }
    }

    return 0;
}