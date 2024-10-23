#include <stdint.h>

// Forward declaration of the default fault handlers
void Reset_Handler(void);
void Default_Handler(void);

// The vector table
__attribute__((section(".vectors")))
void (* const vector_table[])(void) = {
    Reset_Handler,  // Initial stack pointer (optional; use if needed)
    Default_Handler,  // Reset Handler
    Default_Handler,  // NMI Handler
    Default_Handler   // Hard Fault Handler
};

// Reset handler
void Reset_Handler(void) {
    // Call main or other initialization routines
    extern int main(void);
    main();

    // Trap if main returns
    while (1);
}

// Default handler for unhandled interrupts
void Default_Handler(void) {
    while (1);
}
