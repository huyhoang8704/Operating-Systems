#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>


int glo_init_data = 90;
int glo_noninit_data ;

void func (unsigned long number){
    unsigned long local_data = number;

    printf("Process ID = %d\n", getpid());
    printf("Addresses of the process :\n");

    printf("1. glo_init_data = %p\n", &glo_init_data);
    printf("2. glo_noninit_data = %p\n", &glo_noninit_data);
    printf("3. print_func() = %p\n", &func);
    printf("4. local_data = %p\n", &local_data);
}

int main(){
    func(10);

    while (1)   usleep(0);

    return 0;
}

/**
 * Lệnh cat /proc/872/maps được sử dụng trong Linux để hiển thị bố cục bộ nhớ của
 *  một tiến trình cụ thể được xác định bằng ID tiến trình (PID) của nó trong
 *  hệ thống tệp /proc. Đầu ra của lệnh này cung cấp thông tin chi tiết về các vùng bộ nhớ
 *  được sử dụng bởi tiến trình, bao gồm địa chỉ, quyền truy cập và loại truy cập.
*/