#include<stdio.h>
#include<stdlib.h>
#include"queue.h"

void print_menu()
{
    printf("1. Enqueue element\n");
    printf("2. Peek head\n");
    printf("3. Dequeue element\n");
    printf("4. Queue empty\n");
    printf("5. Queue full\n");
    printf("6. Display Queue\n");
    printf("0. Exit\n");
    printf("\n");
}

int main(void)
{
    queue Q;
    int queue_size = 3;
    printf("Enter size for queue: ");
    scanf("%d", &queue_size);

    init_queue(&Q, queue_size);
    int input;

    do
    {
        print_menu();
        scanf("%d", &input);

        switch(input)
        {
            case 1:
            {
                if(!is_full(Q))
                {
                    int val;
                    printf("Enter value to enqueue: ");
                    scanf("%d", &val);

                    enqueue(&Q, val);
                    printf("Value enqueued.");
                }
                else
                    printf("Queue is full.");

                break;
            }

            case 2:
            {
                if(!is_empty(Q))
                    printf("Front: %d", front(Q));
                else
                    printf("Queue is empty.");

                break;
            }

            case 3:
            {
                if(!is_empty(Q))
                {
                    dequeue(&Q);
                    printf("Value dequeued.");
                }
                else
                    printf("Queue is empty.");

                break;
            }

            case 4:
            {
                if(is_empty(Q))
                    printf("Queue is empty.");
                else
                    printf("Queue is not empty.");

                break;
            }

            case 5:
            {
                if(is_full(Q))
                    printf("Queue is full.");
                else
                    printf("Queue is not full.");

                break;
            }

            case 6:
            {
                if(!is_empty(Q))
                    print_queue(Q);
                else
                    printf("Queue is empty.");

                break;
            }

            case 0:
                break;

            default:
                printf("Enter a valid option.");
        }

        printf("\n\n");
    } while(input);

    destruct(&Q);
    return 0;
}
