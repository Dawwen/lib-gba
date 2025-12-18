#include "comm.h"
#include <tonc.h>
#include "circular_buffer.h"


char g_rcv_buffer[UART_RCV_BUFFER_SIZE];
struct circ_buff g_uart_rcv_buffer;

int UART_RET_MAX = 256;

void init_uart(u16 uart) {
  // clear out SIO control registers
  REG_RCNT = 0;
  REG_SIOCNT = 0;

  // If you want to enable fifo straight away, enable UART with fifo
  // disabled as it is reset/initialized when off. On another line in the source
  // file, set SIO_USE_FIFO to 1.

  // for if you do or don't have the CTS/RTS wires; see README.md
#if FLOW_CONTROL
  REG_SIOCNT = uart | SIO_CTS | SIO_LENGTH_8 | SIO_SEND_ENABLE
               | SIO_RECV_ENABLE | SIO_USE_UART;
#else
  REG_SIOCNT = uart | SIO_LENGTH_8 | SIO_SEND_ENABLE
               | SIO_RECV_ENABLE | SIO_USE_UART;
#endif

  // With any luck, we should now be able to talk to a PC.
}


// void setCommunicationToUART()
// {
//     // Set to UART mode
//     init_circ_buff(&g_uart_rcv_buffer, g_rcv_buffer, UART_RCV_BUFFER_SIZE);
//     init_uart(SIO_BAUD_115200);

//     // set irqs
//     irq_init(NULL);
//     irq_add(II_SERIAL, handle_console_uart_ret);
//     irq_add(II_VBLANK, NULL);
// }

void snd_uart_ret(const char out[], int len) {
  for(int i = 0; i < len; i++) {
    // Wait until the send queue is empty
    while(REG_SIOCNT & SIO_SEND_DATA);

    // Bung our byte into the data register
    REG_SIODATA8 = out[i];
  }
}

// we collect bytes in `in` until we see a `return`
int rcv_uart_ret(char in[]) {
  // make sure there's no '\n' in `last`
  char last = ' ';
  int i;
  for(i = 0; i < UART_RET_MAX && last != '\n'; i++) {
    // sd is assumed to be low
    // wait until we have a full byte (the recv data flag will go to 0 and sd will
    // go high)
    while(REG_SIOCNT & SIO_RECV_DATA);

    // save the char from the sio data register
    last = (char)REG_SIODATA8;
    in[i] = last;
  }
  return i;
}

char in[4096];
void handle_console_uart_ret() {
  // the error bit is reset when reading REG_SIOCNT
  // if (REG_SIOCNT & SIO_ERROR) {
  //   // write_console_line("SIO error\n");
  // }

  // // receiving data is time-sensitive so we handle this first without wasting CPU
  // // cycles on say writing to the console
  if (!(REG_SIOCNT & SIO_RECV_DATA)) {
    // reserve an arbitrary amount of bytes for the rcv buffer

    uint32_t size = rcv_uart_ret(in);

    // null-terminating so we can write to the console with write_console_line
    in[size] = 0;
    // write_console_line(in);
    for (unsigned int i = 0; i < size+1; i++)
    {
        write_circ_char(&g_uart_rcv_buffer, in[i]);
    }
    
    
    // send line back over serial line
    snd_uart_ret(in, size);
  }

  // if (!(REG_SIOCNT & SIO_SEND_DATA)) {
  //   // do something
  // }
}
ARM_CODE
// void close_uart() {
//   // disable SIO
//   REG_SIOCNT = 0;
// }

// Small helper to read the SPI/SIO data port. We want this function to be
// generated in ARM (32-bit) mode even if the project is compiled with
// -mthumb globally. Use the "target" attribute so the compiler emits ARM
// instructions for this function (GCC/Clang support function multiversioning).
// It simply waits for the receive flag to indicate data is ready and returns
// the 8-bit data register.
// extern "C" unsigned char read_spi_arm(void) __attribute__((target("arm")));
// extern "C" unsigned char read_spi_arm(void) {
//   // Wait until we have a full byte (recv data flag will go to 0 when ready)
//   while (REG_SIOCNT & SIO_RECV_DATA) {
//     ;
//   }

//   return (unsigned char)REG_SIODATA8;
// }


// void waitVBlank() {
//   VBlankIntrWait();
// }

