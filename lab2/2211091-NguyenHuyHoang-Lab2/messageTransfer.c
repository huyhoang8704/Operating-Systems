#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define MAX_MSG_SIZE 256

struct msgbuf
{
    long mtype;
    char mtext[MAX_MSG_SIZE];
};

#define QUEUE_KEY 1234

void *sender(void *arg)
{
    int msqid;
    struct msgbuf message;
    size_t msg_size;

    msqid = msgget(QUEUE_KEY, IPC_CREAT | 0666);
    if (msqid == -1)
    {
        perror("msgget");
        exit(EXIT_FAILURE);
    }

    while (1)
    {
        fgets(message.mtext, MAX_MSG_SIZE, stdin);
        msg_size = strlen(message.mtext);
        message.mtype = 1;
        if (msgsnd(msqid, &message, msg_size, 0) == -1)
        {
            perror("msgsnd");
            exit(EXIT_FAILURE);
        }
    }

    return NULL;
}

void *receiver(void *arg)
{
    int msqid;
    struct msgbuf message;

    msqid = msgget(QUEUE_KEY, 0666);
    if (msqid == -1)
    {
        perror("msgget");
        exit(EXIT_FAILURE);
    }

    while (1)
    {
        if (msgrcv(msqid, &message, MAX_MSG_SIZE, 1, 0) == -1)
        {
            perror("msgrcv");
            exit(EXIT_FAILURE);
        }

        system("clear");
        printf("Received message: %s", message.mtext);
    }

    return NULL;
}

int main()
{
    system("clear");

    pthread_t sender_thread, receiver_thread;

    pthread_create(&sender_thread, NULL, sender, NULL);
    pthread_create(&receiver_thread, NULL, receiver, NULL);

    pthread_join(sender_thread, NULL);
    pthread_join(receiver_thread, NULL);

    return 0;
}
