#include "src/STM32H745_CM7/startup.c"
#include "include/ti/gpio.h"
#include "stdint.h"
#include "stdbool.h"
#include "stddef.h"

    /* File operations */
    #define HOST_OPEN   0x01U //Open a file or stream on the host system.
    #define HOST_ISTTY  0x09U //Check whether a file handle is associated with a file or a stream/terminal such as stdout.
    #define HOST_WRITE  0x05U //Write to a file or stream.
    #define HOST_READ   0x06U //Read from a file at the current cursor position.
    #define HOST_CLOSE  0x02U //Closes a file on the host which has been opened by HOST_OPEN.
    #define HOST_FLEN   0x0CU //Get the length of a file.
    #define HOST_SEEK   0x0AU //Set the file cursor to a given position in a file.
    #define HOST_TMPNAM 0x0DU //Get a temporary absolute file path to create a temporary file.
    #define HOST_REMOVE 0x0EU //Remove a file on the host system. Possibly insecure!
    #define HOST_RENAME 0x0FU //Rename a file on the host system. Possibly insecure!

    /* Terminal I/O operations */
    #define HOST_WRITEC 0x03U //Write one character to the debug terminal.
    #define HOST_WRITE0 0x04U //Write a 0-terminated string to the debug terminal.
    #define HOST_READC  0x07U //Read one character from the debug terminal.

    /* Time operations */
    #define HOST_CLOCK    0x10U //Get the current time in clock ticks.
    #define HOST_ELAPSED  0x30U //Get the elapsed time in clock ticks.
    #define HOST_TICKFREQ 0x31U //Get the frequency of the clock ticks.
    #define HOST_TIME     0x11U //Get the current time in seconds since the Unix epoch.

    /* System/Misc. operations */
    #define HOST_ERRNO       0x13U //Returns the value of the C library errno variable that is associated with the semihosting implementation.
    #define HOST_GET_CMDLINE 0x15U //Get commandline parameters for the application to run with (argc and argv for main())
    #define HOST_HEAPINFO    0x16U //Get heap information
    #define HOST_ISERROR     0x08U //Check if a return value is an error code.
    #define HOST_SYSTEM      0x12U //Execute a command on the host system.

  // Haults execution if the given condition is false
  #define assert(cond) ({ \
    if (!(cond)) { \
      asm volatile ("bkpt #0x0"); \
    } \
  })

  // Executes a command on the host system and returns the result.
  inline uint32_t host_cmd(uint32_t id, uint32_t arg) {
    uint32_t res;
    __asm__ volatile (
      "mov r0, %[id_] \n"
      "mov r1, %[arg_] \n"
      "bkpt #0xAB \n"
      "mov %[res_], r0 \n"
      : [res_] "=r" (res)
      : [id_] "r" (id), [arg_] "r" (arg)
      : "r0", "r1"
    );
    return res;
  }

  // Prints a string to the host terminal
  inline void host_print(const char* msg) {
    host_cmd(HOST_WRITE0, (uint32_t)msg);
  }

  void gpio_test(void) {
    static const int32_t _BUILTIN_LED_PIN = 81;
    tal_set_mode(_BUILTIN_LED_PIN, 1);
    tal_set_pin(_BUILTIN_LED_PIN, 1);
  }

  void main(void) {
    gpio_test();
    host_print("HELLO WORLD");
  }