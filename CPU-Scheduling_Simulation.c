#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define MAX_PROCESSES 25 // The maximum number of process threads.

void *process(void *num);
void *cpu(void *);

// Define the semaphores.
sem_t readyQueue;
sem_t cpuAvailable;
sem_t cpuBusy;
sem_t processComplete;

// Flag to stop the cpu thread when all processes have been serviced.
int allDone = 0;

int main(int argc, char *argv[]) {
    pthread_t cputid;
    pthread_t tid[MAX_PROCESSES];
    int i, x, numProcesses, numCPUs;
    int Number[MAX_PROCESSES];

    printf("Maximum number of processes can only be 25. Enter the number of processes and CPUs:\n");
    scanf("%d", &x);
    numProcesses = x;
    scanf("%d", &x);
    numCPUs = x;

    if (numProcesses > MAX_PROCESSES) {
        printf("The maximum number of processes is %d.\n", MAX_PROCESSES);
        return 0;
    }

    printf("A solution to the CPU scheduling problem using semaphores.\n");

    for (i = 0; i < MAX_PROCESSES; i++) {
        Number[i] = i;
    }

    // Initialize the semaphores with initial values...
    sem_init(&readyQueue, 0, numCPUs);
    sem_init(&cpuAvailable, 0, 1);
    sem_init(&cpuBusy, 0, 0);
    sem_init(&processComplete, 0, 0);

    // Create the CPUs.
    pthread_create(&cputid, NULL, cpu, NULL);

    // Create the processes.
    for (i = 0; i < numProcesses; i++) {
        pthread_create(&tid[i], NULL, process, (void *)&Number[i]);
    }

    // Join each of the threads to wait for them to finish.
    for (i = 0; i < numProcesses; i++) {
        pthread_join(tid[i], NULL);
    }

    // When all of the processes are finished, kill the cpu thread.
    allDone = 1;
    sem_post(&cpuBusy); // Wake the cpu so it will exit.
    pthread_join(cputid, NULL);

    return 0;
}

void *process(void *number) {
    int num = *(int *)number;

    // Start executing the process and take some random amount of time to complete.
    printf("Process %d is executing.\n", num);
    sleep(1 + rand() % 5); // Random sleep duration between 1 and 5 seconds.
    printf("Process %d has completed execution.\n", num);

    // Wait for space to open up in the ready queue.
    sem_wait(&readyQueue);
    printf("Process %d added to the ready queue.\n", num);

    // Wait for a CPU to become available.
    sem_wait(&cpuAvailable);

    // The CPU is free, so give up your spot in the ready queue.
    sem_post(&readyQueue);

    printf("Process %d requesting CPU.\n", num);

    // Request the CPU.
    sem_post(&cpuBusy);

    // Wait for the CPU to finish executing the process.
    sem_wait(&processComplete);

    // Release the CPU.
    sem_post(&cpuAvailable);
    printf("Process %d releases the CPU.\n", num);

    return NULL;
}

void *cpu(void *junk) {
    // While there are still processes to be executed...
    // Our CPU is aware of the number of processes still pending execution.
    while (!allDone) {
        printf("The CPU is idle.\n");
        sem_wait(&cpuBusy); // Wait until a process is added to the ready queue.

        if (!allDone) {
            // Take a random amount of time to execute the process.
            printf("The CPU is executing the process.\n");
            sleep(1 + rand() % 3); // Random sleep duration between 1 and 3 seconds.
            printf("The CPU has completed executing the process.\n");

            // Signal that the process execution is complete.
            sem_post(&processComplete);
        } else {
            printf("The CPU is shutting down.\n");
        }
    }

    return NULL;
}

