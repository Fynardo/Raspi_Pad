#include <linux/input.h>
#include <linux/uinput.h>


int uinput_open();
int uinput_init(int fd);
int uinput_destroy(int fd);
