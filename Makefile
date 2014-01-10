pad: pad.c arduino_serial.o pad_uinput.o
	gcc -o pad -g pad.c arduino_serial.o pad_uinput.o

arduino_serial.o: arduino_serial.c arduino_serial.h
	gcc -o arduino_serial.o -g -c arduino_serial.c

pad_uinput.o: pad_uinput.c pad_uinput.h
	gcc -o pad_uinput.o -g -c pad_uinput.c

clean:
	rm *.o
