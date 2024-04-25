#include <sys/msg.h>

int main() {
  // Tạo message
  struct msgbuf msg;

  // Nhận message
  int ret = msgrcv(msg_id, &msg, sizeof(msg.mtext), 1, 0);

  // Kiểm tra lỗi
  if (ret == -1) {
    perror("msgrcv");
    exit(1);
  }

  // In nội dung message
  printf("Message: %s\n", msg.mtext);

  return 0;
}
