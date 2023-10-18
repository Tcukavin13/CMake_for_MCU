/*
 ============================================================================
 Name        : main.c
 Author      : Tcukavin
 Version     :
 Copyright   : Your copyright notice
 Description :
 ============================================================================
 */
/* MCU */
#include "at32f435_437.h"
/* Clock */
#include "at32f435_437_clock.h"
/* FreeRTOS */
#include "FreeRTOSConfig.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

/* Daemon Task */
static void daemon_task(void *pvParameters);

int main(void)
{
    /* System Init */
    SystemInit();

    /* System clock config and update system_core_clock (288 MHz) */
    system_clock_config();

    /* Set 4 bits for preemption priority, 0 bits for sub-priority */
    nvic_priority_group_config(NVIC_PRIORITY_GROUP_4);

    /* Daemon task create */
    if(pdPASS != xTaskCreate(daemon_task, "Daemon", configMINIMAL_STACK_SIZE * 4,
                             NULL, tskIDLE_PRIORITY + 1, NULL))
    {
        while(1){};
    }

    /* RTOS Scheduler start */
    vTaskStartScheduler();

    while(1)
    {

    }
  return 0;
}


/* Daemon Task */
static void daemon_task(void *pvParameters)
{
    /* Enable the gpio clock */
    crm_periph_clock_enable(CRM_GPIOD_PERIPH_CLOCK, TRUE);

    /* gpio init */
    gpio_init_type gpio_ini = {GPIO_PINS_13 | GPIO_PINS_14 | GPIO_PINS_15, GPIO_OUTPUT_PUSH_PULL,
                               GPIO_PULL_NONE, GPIO_MODE_OUTPUT, GPIO_DRIVE_STRENGTH_STRONGER};

    gpio_init(GPIOD, &gpio_ini);

    gpio_bits_reset(GPIOD, GPIO_PINS_13 | GPIO_PINS_14 | GPIO_PINS_15);

    for(;;)
    {
        vTaskDelay(500);
        gpio_bits_set(GPIOD, GPIO_PINS_13 | GPIO_PINS_14 | GPIO_PINS_15);
        vTaskDelay(500);
        gpio_bits_reset(GPIOD, GPIO_PINS_13 | GPIO_PINS_14 | GPIO_PINS_15);
    }
}
