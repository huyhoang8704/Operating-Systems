#include <sys/msg.h>

int main() {
  // Tạo hàng đợi message với khóa 1234
  int msg_id = msgget(1234, 0666);

  // Kiểm tra lỗi
  if (msg_id == -1) {
    perror("msgget");
    exit(1);
  }

  return 0;
}
