#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "arduino_serial.h"
#include "pad_uinput.h"

int main(int argc, char * argv[]){
  int fd_serial, fd_uinput;
  struct input_event ev;
  int baud = B9600;
  static char * port = "/dev/ttyACM0";
  char buf[4];
  int n;
  
  memset(&ev,0,sizeof(ev));

  if ( (fd_serial = serial_open(port)) == -1) exit(1);
  if ( serial_init(fd_serial,port,baud) == -1) exit(1);

  if ( (fd_uinput = uinput_open()) == -1) exit(1);
  if ( uinput_init(fd_uinput) == -1) exit(1);

  //ioctl(fd_uinput,UI_SET_KEYBIT, KEY_D);  


while(1){
  if ( (n = serial_read(fd_serial, buf, 4)) == -1) continue;
  //printf("Leidos %i bytes, contenido: %s",n,buf);
 
  memset(&ev,0,sizeof(ev));
  ev.type = EV_KEY;
  ev.code = KEY_ENTER;
  ev.value = 1;

  write(fd_uinput,&ev,sizeof(ev));

  memset(&ev,0,sizeof(ev));
  ev.type = EV_KEY;
  ev.code = KEY_ENTER;
  ev.value = 0;

  write(fd_uinput,&ev,sizeof(ev));


  memset(&ev,0,sizeof(ev));
  ev.type = EV_SYN;
  ev.code = SYN_REPORT;
  ev.value = 0;
  write(fd_uinput, &ev, sizeof(ev));


  tcflush(fd_serial, TCIOFLUSH);
}


  serial_close(fd_serial);
  uinput_destroy(fd_uinput);
  exit(0);
}
