#include <sys/shm.h>

int main() {
  // Tạo vùng nhớ dùng chung với kích thước 1024 byte
  int shm_id = shmget(IPC_PRIVATE, 1024, 0666);

  // Kiểm tra lỗi
  if (shm_id == -1) {
    perror("shmget");
    exit(1);
  }

  return 0;
}
