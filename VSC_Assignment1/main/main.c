#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <driver/gpio.h>
#include <esp_timer.h>
#include <rom/ets_sys.h>

//#define PRODUCTION
#define DEBUG

#ifdef DEBUG
#define S 1000
#else
#define S 1 
#endif

#define S1_PIN 6
#define S2_PIN 7
#define SIGA_PIN 4
#define SIGB_PIN 5
#define SIG_B_WIDTH 50

#define N_VALUE 13
#define A_VALUE 1
#define D_VALUE 4
#define U_VALUE 6
#define P_VALUE 11

volatile int sw1 = 0, sw2 = 0;
volatile int ts1 = 0, ts2 = 0;
volatile int t1 = 0, t2 = 0;
int a1 = 2, b1 = 0;

void IRAM_ATTR switch1_isr(void *arg) {
    if (t1 == 0) {
        sw1 = !sw1;
        t1 = !t1;
    }
}

void IRAM_ATTR switch2_isr(void *arg) {
    if (t2 == 0) {
        sw2 = !sw2;
        t2 = !t2;
    }
}

void delay_microseconds(unsigned long time) {
    unsigned long start = esp_timer_get_time();
    unsigned long diff = esp_timer_get_time() - start;
    while (diff < time) {
        printf("%d,%d\n", a1, b1);
        diff = esp_timer_get_time() - start;
        ets_delay_us(1);
    }
}

void app_main() {
    gpio_config_t io_conf;

    io_conf.intr_type = GPIO_INTR_POSEDGE;
    io_conf.mode = GPIO_MODE_INPUT;
    io_conf.pin_bit_mask = (1ULL << S1_PIN) | (1ULL << S2_PIN);
    io_conf.pull_down_en = GPIO_PULLDOWN_ENABLE;
    io_conf.pull_up_en = GPIO_PULLUP_DISABLE;
    gpio_config(&io_conf);

    io_conf.intr_type = GPIO_INTR_DISABLE;
    io_conf.mode = GPIO_MODE_OUTPUT;
    io_conf.pin_bit_mask = (1ULL << SIGA_PIN) | (1ULL << SIGB_PIN);
    io_conf.pull_down_en = GPIO_PULLDOWN_DISABLE;
    io_conf.pull_up_en = GPIO_PULLUP_DISABLE;
    gpio_config(&io_conf);

    gpio_install_isr_service(ESP_INTR_FLAG_LEVEL1);
    gpio_isr_handler_add(S1_PIN, switch1_isr, NULL);
    gpio_isr_handler_add(S2_PIN, switch2_isr, NULL);

    while (1) {
        // Calculate Parameters
        int A = N_VALUE * 100;
        int B = A_VALUE * 100;
        int C = D_VALUE + 4;
        int D = U_VALUE * 500;
        //int M = (P_VALUE % 4) + 1;

        // Start with no output at both the signals
        gpio_set_level(SIGA_PIN, 0);
        a1 = 2;
        gpio_set_level(SIGB_PIN, 0);
        b1 = 0;

        // Start signal B
        gpio_set_level(SIGB_PIN, 1);
        b1 = 1;
        delay_microseconds(SIG_B_WIDTH * S);
        gpio_set_level(SIGB_PIN, 0);
        b1 = 0;

        if (ts2 == 0) {
            for (int i = 0; i < C; i++) {
                if (ts1 == 0) {
                    gpio_set_level(SIGA_PIN, 1);
                    a1 = 3;
                }
                delay_microseconds(A * S);
                gpio_set_level(SIGA_PIN, 0);
                a1 = 2;
                delay_microseconds(B * S);
                A += 50;
            }
            delay_microseconds(D * S);
        } else {
            for (int i = 0; i < C; i++) {
                if (ts1 == 0) {
                    gpio_set_level(SIGA_PIN, 1);
                    a1 = 3;
                }
                delay_microseconds(A * S);
                gpio_set_level(SIGA_PIN, 0);
                a1 = 2;
                delay_microseconds((B / 2) * S);
                A += 50;
            }
            delay_microseconds((D / 2) * S);
        }

        ts1 = sw1;
        ts2 = sw2;

        t1 = 0;
        t2 = 0;
    }
}
