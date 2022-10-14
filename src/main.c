#include <stdio.h>
#include "pico/stdlib.h"

#define LED_PIN PICO_DEFAULT_LED_PIN

int main(void)
{
    stdio_init_all();

    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

    for (;;) {
        printf("LED on\n");
        gpio_put(LED_PIN, 1);
        sleep_ms(100);
        printf("LED off\n");
        gpio_put(LED_PIN, 0);
        sleep_ms(100);
    }

    return 0;
}
