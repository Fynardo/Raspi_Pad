#include <errno.h>
#include <termios.h>
#include <unistd.h>

int serial_open();
int serial_close(int fd);
int serial_init(int fd, char * port, int baud);

/*
 * I -> fd del puerto serial, buffer donde escribe lo leido, tam del buffer
 * O -> numero de bytes leidos (-1 si error), escribe lo leido en buf
 */
int serial_read(int fd, char * buf, int x);
