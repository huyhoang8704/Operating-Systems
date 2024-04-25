#include <sys/msg.h>

int main() {
  // Tạo message
  struct msgbuf msg;
  msg.mtype = 1; // Loại message
  strcpy(msg.mtext, "Hello, world!"); // Nội dung message

  // Gửi message
  int ret = msgsnd(msg_id, &msg, sizeof(msg.mtext), 0);

  // Kiểm tra lỗi
  if (ret == -1) {
    perror("msgsnd");
    exit(1);
  }

  return 0;
}
