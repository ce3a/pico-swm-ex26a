#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "counter.pio.h"

#ifndef PICO_DEFAULT_LED_PIN
# error Pico board with a default LED expected.
#else

#define PIN_LED     PICO_DEFAULT_LED_PIN
#define PIN_CNT     16u

#define N_PULSES    45u     // Number of pulses per liter

int main(void)
{
    stdio_init_all();

    PIO pio = pio0;
    const uint offset = pio_add_program(pio, &counter_program);
    const uint sm = pio_claim_unused_sm(pio, true);

    counter_program_init(pio, sm, offset, PIN_CNT, PIN_LED);

    // Configure number of pulses to count.
    // Fill two slots, in order to not block the PIO.
    counter_reload(pio, sm, 2, N_PULSES);

    uint32_t val = 0;
    while (true) {

        if (!pio_sm_is_rx_fifo_empty(pio, sm)) {
            while (!pio_sm_is_rx_fifo_empty(pio, sm)) {
                // Reload number of pulses to count.
                counter_reload(pio, sm, 1, N_PULSES);
                val = pio_sm_get(pio, sm);
            }

            printf("%05ldl [0x%08lX]\n", val, val);
        }

        sleep_ms(1000);
    }
#endif
}
