#ifndef COMM__H
#define COMM__H

// #include <types.h>
// #include "types.h"

// UART settings
#define SIO_USE_UART      0x3000

// Baud Rate
#define SIO_BAUD_9600     0x0000
#define SIO_BAUD_38400    0x0001
#define SIO_BAUD_57600    0x0002
#define SIO_BAUD_115200   0x0003

#define SIO_CTS           0x0004
#define SIO_PARITY_ODD    0x0008
#define SIO_SEND_DATA     0x0010
#define SIO_RECV_DATA     0x0020
#define SIO_ERROR         0x0040
#define SIO_LENGTH_8      0x0080
#define SIO_USE_FIFO      0x0100
#define SIO_USE_PARITY    0x0200
#define SIO_SEND_ENABLE   0x0400
#define SIO_RECV_ENABLE   0x0800
#define SIO_REQUEST_IRQ   0x4000

// rcv buffer things
#define UART_RCV_BUFFER_SIZE 256
extern char g_rcv_buffer[UART_RCV_BUFFER_SIZE];
extern struct circ_buff g_uart_rcv_buffer;

void init_uart(unsigned short uart);
// void setCommunicationToUART();
void snd_uart_ret(const char out[], int len);
int rcv_uart_ret(char in[]);
void handle_console_uart_ret();
// Read one byte from the SPI/SIO data port using ARM instruction set
unsigned char read_spi_arm(void);
void setInterupt();
void waitVBlank();//

#endif