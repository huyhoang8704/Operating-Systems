#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>  // Included for sleep function

#define SHM_KEY 0x123  // khai báo bộ nhớ chia sẻ

int main(int argc, char *argv[]) {
    int shmid;
    char *shm;

    // Create (or attach to) the shared memory segment
    shmid = shmget(SHM_KEY, 1000, 0644 | IPC_CREAT);
    if (shmid < 0) {
        perror("shmget");
        return 1;
    } else {
        
    //! Shared memory ID: 3
        printf("Shared memory ID: %d\n", shmid);  //! ID phân đoạn của bộ nhớ chia sẻ
    }

    // Attach to the shared memory segment
    shm = (char *)shmat(shmid, 0, 0);
    if (shm == (char *)-1) {
        perror("shmat");
        exit(1);
    }
    //! Shared memory address: 0x7f8d456a1000
    printf("Shared memory address: %p\n", shm);

    // **Assuming you intend to treat the shared memory as a string:**
    // You can access the content of the shared memory here,
    // but be cautious about potential modifications from other processes.
    printf("Shared memory content: %s\n", shm);  // Uncomment if needed

    getc(stdin);

    if (shmdt(shm) == -1) {
        perror("shmdt");
        return 1;
    }

    return 0;
}

//! Shared memory ID: 3
//! Shared memory address: 0x7f8d456a1000