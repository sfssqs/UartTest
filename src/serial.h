/*
 * serial.h
 *
 *  Created on: 2015-11-23
 *      Author: ALAN
 */

#ifndef SERIAL_H_
#define SERIAL_H_

#endif /* SERIAL_H_ */

static void set_baudrate(struct termios *opt, unsigned int baudrate) {
	cfsetispeed(opt, baudrate);
	cfsetospeed(opt, baudrate);
}

static void set_data_bit(struct termios *opt, unsigned int databit) {
	opt->c_cflag &= ~CSIZE;
	switch (databit) {
	case 8:
		opt->c_cflag |= CS8;
		break;
	case 7:
		opt->c_cflag |= CS7;
		break;
	case 6:
		opt->c_cflag |= CS6;
		break;
	case 5:
		opt->c_cflag |= CS5;
		break;
	default:
		opt->c_cflag |= CS8;
		break;
	}
}

static void set_parity(struct termios *opt, char parity) {
	switch (parity) {
	case 'N':
		/* 无校验 */
		/* 偶校验 */
		/* 奇校验 */
	case 'n':
		opt->c_cflag &= ~PARENB;
		break;
	case 'E':
	case 'e':
		opt->c_cflag |= PARENB;
		opt->c_cflag &= ~PARODD;
		break;
	case 'O':
	case 'o':
		opt->c_cflag |= PARENB;
		opt->c_cflag |= ~PARODD;
		break;
		/* 其它选择为无校验 */
	default:
		opt->c_cflag &= ~PARENB;
		break;
	}
}

static void set_stopbit(struct termios *opt, const char *stopbit) {
	if (0 == strcmp(stopbit, "1")) {
		opt->c_cflag &= ~CSTOPB;
		/* 1 位停止位 t */
		/* 1.5 位停止位 */
		/* 2 位停止位 */
		/* 1 位停止位 */
	} else if (0 == strcmp(stopbit, "1.5")) {
		opt->c_cflag &= ~CSTOPB;
	} else if (0 == strcmp(stopbit, "2")) {
		opt->c_cflag |= CSTOPB;
	} else {
		opt->c_cflag &= ~CSTOPB;
	}
}

