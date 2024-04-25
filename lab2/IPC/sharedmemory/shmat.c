#include <sys/shm.h>

int main() {
  // Gắn vùng nhớ dùng chung vào địa chỉ
  void *ptr = shmat(shm_id, NULL, 0);

  // Kiểm tra lỗi
  if (ptr == (void *)-1) {
    perror("shmat");
    exit(1);
  }

  return 0;
}
