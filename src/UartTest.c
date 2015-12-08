/*
 * serial.c
 *
 *  Created on: 2015-11-23
 *      Author: xiaxing
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>

#include "serial.h"

//#define DEV_NAME "/dev/ttyS1"
//#define DEV_NAME "/dev/ttyUSB3"
#define DEV_NAME "/dev/ttymxc1"

int set_port_attr(int fd, int baudrate, int databit, const char *stopbit,
		char parity, int vtime, int vmin) {
	struct termios opt;

	tcgetattr(fd, &opt);

	set_baudrate(&opt, baudrate);

	// [Begin] :  write success but read failed
    //	 opt.c_cflag |= CLOCAL | CREAD;
	opt.c_cflag &= ~CRTSCTS;
	//[End]

	/* | CRTSCTS */
	set_data_bit(&opt, databit);
	set_parity(&opt, parity);
	set_stopbit(&opt, stopbit);
	opt.c_oflag = 0;
	opt.c_lflag |= 0;
	opt.c_oflag &= ~OPOST;
	opt.c_cc[VTIME] = vtime;
	opt.c_cc[VMIN] = vmin;
	tcflush(fd, TCIFLUSH);

	return (tcsetattr(fd, TCSANOW, &opt));
}

int main(int argc, char *argv[]) {
	int fd;
	int len, ret;
	char buf[] = "hello heihei";

	// open Uart device
	fd = open(DEV_NAME, O_RDWR | O_NOCTTY);
	if (fd < 0) {
		perror("open uart device error\n");
	}

	ret = set_port_attr(fd, B9600, 8, "1", 'N', 8, 100); /* 115200 8n1     150 255*/
	if (ret < 0) {
		printf("set uart arrt faile \n");
		exit(-1);
	}

	// write data
	len = write(fd, buf, sizeof(buf));
	if (len < 0) {
		printf("write data error!\n");
		return -1;
	}

	printf("The output data :  %s \n", buf);

	// read data
	memset(buf, 0, sizeof(buf));

	len = read(fd, buf, sizeof(buf));
	printf("len :  %d \n", len);

	if (len < 0) {
		printf("read data error!\n");
		return -1;
	}

	// print the data read from tty device
	printf("The read data : %s \n", buf);

	// close device
	//	close(fd);

//	puts("!!!Hello World!!!");
	return (0);
}

