#include <stdio.h>

#define MAX_PROCESSES 100

struct Process {
    int priority;
    int burst_time;
    int remaining_time;
};

struct Queue {
    struct Process processes[MAX_PROCESSES];
    int front, rear;
};

void enqueue(struct Queue *queue, struct Process process) {
    if (queue->rear == MAX_PROCESSES - 1) {
        printf("Queue is full. Cannot enqueue.\n");
        return;
    }
    queue->processes[++queue->rear] = process;
    if (queue->rear == 0) {
        queue->front = 0;
    }
}

struct Process dequeue(struct Queue *queue) {
    if (queue->front == -1) {
        printf("Queue is empty. Cannot dequeue.\n");
        struct Process empty;
        return empty;
    }
    struct Process process = queue->processes[queue->front];
    if (queue->front == queue->rear) {
        queue->front = queue->rear = -1;
    } else {
        queue->front++;
    }
    return process;
}

int main() {
    struct Queue high_priority_queue, medium_priority_queue, low_priority_queue;
    high_priority_queue.front = high_priority_queue.rear = -1;
    medium_priority_queue.front = medium_priority_queue.rear = -1;
    low_priority_queue.front = low_priority_queue.rear = -1;

    int num_processes;
    printf("Enter the number of processes: ");
    scanf("%d", &num_processes);

    for (int i = 0; i < num_processes; i++) {
        struct Process process;
        printf("Enter priority for Process %d: ", i + 1);
        scanf("%d", &process.priority);
        printf("Enter burst time for Process %d: ", i + 1);
        scanf("%d", &process.burst_time);
        process.remaining_time = process.burst_time;

        if (process.priority >= 0 && process.priority <= 3) {
            enqueue(&high_priority_queue, process);
        } else if (process.priority >= 4 && process.priority <= 6) {
            enqueue(&medium_priority_queue, process);
        } else {
            enqueue(&low_priority_queue, process);
        }
    }

    int time = 0;
    while (1) {
        if (high_priority_queue.front != -1) {
            printf("Time %d: Running process from high-priority queue\n", time);
            struct Process process = dequeue(&high_priority_queue);
            if (process.remaining_time <= 10) {
                time += process.remaining_time;
                process.remaining_time = 0;
                printf("Process completed with priority %d\n", process.priority);
            } else {
                time += 10;
                process.remaining_time -= 10;
                enqueue(&high_priority_queue, process);
                printf("Process with priority %d moved to back of high-priority queue\n", process.priority);
            }
        } else if (medium_priority_queue.front != -1) {
            printf("Time %d: Running process from medium-priority queue\n", time);
            struct Process process = dequeue(&medium_priority_queue);
            if (process.remaining_time <= 10) {
                time += process.remaining_time;
                process.remaining_time = 0;
                printf("Process completed with priority %d\n", process.priority);
            } else {
                time += 10;
                process.remaining_time -= 10;
                enqueue(&medium_priority_queue, process);
                printf("Process with priority %d moved to back of medium-priority queue\n", process.priority);
            }
        } else if (low_priority_queue.front != -1) {
            printf("Time %d: Running process from low-priority queue\n", time);
            struct Process process = dequeue(&low_priority_queue);
            if (process.remaining_time <= 10) {
                time += process.remaining_time;
                process.remaining_time = 0;
                printf("Process completed with priority %d\n", process.priority);
            } else {
                time += 10;
                process.remaining_time -= 10;
                enqueue(&low_priority_queue, process);
                printf("Process with priority %d moved to back of low-priority queue\n", process.priority);
            }
        } else {
            break;
        }
    }

    return 0;
}
