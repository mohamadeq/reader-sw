#include "ch.h"
#include "hal.h"
#include "hal_custom.h"
#include "board_devices.h"
#include "main.h"

#include "common-services/logging.h"
#include "common-services/msg-alloc.h"
#include "common-services/init.h"

uint8_t message_heap[DEADLOCK_MESSAGE_HEAP_SIZE];

int main(void) {

    /*
     * System initializations.
     * - HAL initialization, this also initializes the configured device drivers
     *   and performs the board-specific initializations.
     * - Kernel initialization, the main() function becomes a thread and the
     *   RTOS is active.
     */

    halInit();
    halCustomInit();
    chSysInit();

    /*
     * Initialization of Deadlock Common Services
     */

#ifdef DEBUG
    dcsLogInit(DCS_LOG_DEBUG);
#else
    dcsLogInit(DCS_LOG_INFO);
#endif
    dcsCmaInit(message_heap, DEADLOCK_MESSAGE_HEAP_SIZE);

    dcsExecuteInitThread();     // Start the "init" thread which spawns the core, modules
                                // and watches over them and restarts them if needed.

    /*
     * Idle thread loop
     */

    // This function is now the Idle thread. It must never exit and it must implement
    // an infinite loop.
    while(true) {
        // To prevent compiler from optimizing-out the empty loop
        // TODO implement switching MCU to a low-power mode.
        __asm__ __volatile__("");
    }
}
