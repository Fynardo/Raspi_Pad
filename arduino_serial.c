#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <stdint.h>

#include "arduino_serial.h"


int serial_open(char * port){
  int fd;
  
  if ( (fd = open(port, O_RDWR | O_NOCTTY)) == -1 )
    { perror("Error en serial_open"); return -1; }

  printf("Abriendo puerto en fd: %i...\n",fd);
  printf("Iniciando arduino...\n");
  usleep(3500000);
  printf("Arduino listo!\n");

  return fd;
}


int serial_init(int fd, char * port, int baud){
  struct termios tty;

  memset (&tty,0,sizeof(tty));
  if ( tcgetattr(fd,&tty) == -1 )
    { perror("Error en tcgetattr"); return -1; }

  cfsetospeed(&tty,B9600);
  cfsetispeed(&tty,B9600);

  tty.c_cflag &= ~PARENB;
  tty.c_cflag &= ~CSTOPB;
  tty.c_cflag &= ~CSIZE;
  tty.c_cflag |= CS8;

  tty.c_lflag |= ICANON;

  if ( tcsetattr (fd, TCSANOW, &tty) == -1 )
    { perror("error en tcsetattr"); return -1; }

  return 0;  
}


int serial_read(int fd, char * buf, int x){
  int n = 0;

  if ( (n = read(fd,buf,x)) == -1 )
    { perror("error en read"); return -1; }

  if ( n == 1) return -1;

  buf[n] = 0;
  tcflush(fd, TCIOFLUSH);
  return n;
}

int serial_close(int fd){
  return close(fd);
}

/*
int main(){
  int fd;


  if ( (fd = open("/dev/ttyACM0",O_RDWR | O_NOCTTY)) == -1 )
    {perror("esto no va!"); exit(1); }

  printf("Abriendo puerto en fd: %i...\n",fd);
  printf("Iniciando arduino...\n");
  usleep(3500000);
  
  printf("Listo!\n");


  if ( serial_init(fd, "/dev/ttyACM0",B9600) == -1 )
    { perror("error en serial_init"); exit(1); }
  
  char buf[4];
  int n;

while(1){
//  if ( (n = read(fd,buf,4)) == -1 )
//    { perror("error en read"); exit(1); }
 
//  if ( n == 1) continue;  

//  buf[n] = 0;

  n = serial_read(fd,buf,4);

  printf("He leido %i bytes, contenido: %s",n,buf);
  
//  tcflush(fd, TCIOFLUSH);
}
  close(fd);

  exit(0);
}
*/
