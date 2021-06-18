#include <kernel/kcore.h>

char* panic_msgs[] = {"Division by zero",
                      "Debug exception",
                      "Non-maskable interrupt",
                      "Breakpoint exception",
                      "Detected overflow",
                      "Out of bounds",
                      "Invalid opcode",
                      "No co-processor",
                      "Double fault",
                      "Co-processor segment overrun",
                      "Bad TSS",
                      "Segment not present",
                      "Stack fault",
                      "General protection fault",
                      "Page fault",
                      "Unknown interrupt",
                      "Co-processor fault",
                      "Alignment check exception",
                      "Machine check exception"};

void rkpanic(int err_code)
{
           rk_statusprint("Kernel panic: ", YELLOW);
           rk_print(panic_msgs[err_code], 28);
           rk_kill();
}
 