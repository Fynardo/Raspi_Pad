#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "arduino_serial.h"
#include "pad_uinput.h"

void handle_btn (char * args, int fd_uinput){
  struct input_event ev;
  
  memset(&ev,0,sizeof(ev));
  ev.type = EV_KEY;

  if ( args[0] == '1' ) ev.code = KEY_Q;
  if ( args[0] == '2' ) ev.code = KEY_W;

  if ( args[1] == '1' ) ev.value = 1; else ev.value = 0;

  if ( write(fd_uinput,&ev,sizeof(ev)) == -1) 
    { perror("error en uinput_write"); return; }
  
  memset(&ev,0,sizeof(ev));
  ev.type = EV_SYN;
  ev.code = SYN_REPORT;
  ev.value = 0;
  if ( write(fd_uinput, &ev, sizeof(ev)) == -1)
    { perror("error en uinput_write"); return; }
}

void handle_jst (char * args, int fd_uinput, int * dirh, int * dirv){
  struct input_event ev;
  
  memset(&ev,0,sizeof(ev));
  ev.type = EV_KEY;

  if ( args[0] == 'X' ) {
    if ( args[1] == '0') { ev.code = KEY_LEFT; ev.value = 1; *dirh = 0; }
    if ( args[1] == '1') { ev.code = KEY_RIGHT; ev.value = 1; *dirh = 1; }
    if ( args[1] == '-') {
      ev.value = 0;
      if (*dirh == 0) ev.code = KEY_LEFT;
      if (*dirh == 1) ev.code = KEY_RIGHT;
      *dirh = -1;
    }
  }
  
  if ( args[0] == 'Y' ) {
    if ( args[1] == '0') { ev.code = KEY_UP; ev.value = 1; *dirv = 0; }
    if ( args[1] == '1') { ev.code = KEY_DOWN; ev.value = 1; *dirv = 1; }
    if ( args[1] == '-') {
      ev.value = 0;
      if (*dirv == 0) ev.code = KEY_UP;
      if (*dirv == 1) ev.code = KEY_DOWN;
      *dirv = -1;
    }
  }

  write(fd_uinput, &ev, sizeof(ev));

  memset(&ev,0,sizeof(ev));
  ev.type = EV_SYN;
  ev.code = SYN_REPORT;
  ev.value = 0;
  write(fd_uinput, &ev, sizeof(ev));

}

int main(int argc, char * argv[]){
  int fd_serial, fd_uinput;
  struct input_event ev;
  int baud = B9600;
  static char * port = "/dev/ttyACM0";
  char buf[4];
  int n;
  int dirh = -1, dirv = -1;

  memset(&ev,0,sizeof(ev));

  if ( (fd_serial = serial_open(port)) == -1) exit(1);
  if ( serial_init(fd_serial,port,baud) == -1) exit(1);

  if ( (fd_uinput = uinput_open()) == -1) exit(1);
  if ( uinput_init(fd_uinput) == -1) exit(1);

  printf("Puerto serie: %i\n",fd_serial);
  printf("uinput: %i\n",fd_uinput);


while(1){

  if ( (n = serial_read(fd_serial,buf,4)) == -1) continue;

  if ( buf[0] == 'b' ) handle_btn(buf+1, fd_uinput);
  if ( buf[0] == 'j' ) handle_jst(buf+1, fd_uinput, &dirh, &dirv);

  if ( tcflush(fd_serial, TCIOFLUSH) == -1)
    { perror("error en tcflush"); break; }

} 
   

  serial_close(fd_serial);
  uinput_destroy(fd_uinput);
  exit(0);
}
