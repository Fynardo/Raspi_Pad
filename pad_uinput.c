#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "pad_uinput.h"


int uinput_open(){
  int fd;

  if ( (fd  = open("/dev/uinput", O_WRONLY | O_NONBLOCK)) == -1  )
    { perror("Error en uinput_open"); return -1; }

  return fd;
}


int uinput_init(int fd){
  struct uinput_user_dev uidev;
  
  if ( ioctl(fd, UI_SET_EVBIT, EV_KEY) == -1) return -1;  
  if ( ioctl(fd, UI_SET_EVBIT, EV_SYN) == -1) return -1;
  if ( ioctl(fd, UI_SET_KEYBIT, BTN_A) == -1) return -1;
  if ( ioctl(fd, UI_SET_KEYBIT, BTN_START) == -1) return -1;
  if ( ioctl(fd, UI_SET_KEYBIT, KEY_ENTER) == -1) return -1;

  memset(&uidev,0,sizeof(uidev));

  snprintf(uidev.name, UINPUT_MAX_NAME_SIZE, "snes");
  uidev.id.bustype = BUS_USB;
  uidev.id.vendor = 0x1;
  uidev.id.product = 0xa;
  uidev.id.version = 1;
  
  if (write(fd,&uidev,sizeof(uidev)) == -1) return -1;
  if (ioctl(fd,UI_DEV_CREATE) == -1) return -1;

  return 0;
}


int uinput_destroy(int fd){
  return ioctl(fd, UI_DEV_DESTROY);
}
