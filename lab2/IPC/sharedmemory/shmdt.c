#include <sys/shm.h>

int main() {
  // Gỡ kết nối khỏi vùng nhớ dùng chung
  shmdt(ptr);

  return 0;
}
