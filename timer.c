#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/timers.h"

TimerHandle_t xTimer;
TaskHandle_t task1_handle;

#define TIMER_NAME "mytimer"

void vCallbackFunction(TimerHandle_t xTimer)
{
    printf("in timer function\n");
    // vTaskResume(task1_handle);
}
void task1_fun(void *args)
{
    while (1)
    {
        // vTaskSuspend(task1_handle);
        printf("task1 resumed\n");
        
    }
    // vTaskDelete(task1_handle);
}
void app_main(void)
{
    xTimer = xTimerCreate(TIMER_NAME, pdMS_TO_TICKS(1000), pdTRUE, NULL, vCallbackFunction);
    xTimerStart(xTimer, portMAX_DELAY);
    xTaskCreatePinnedToCore(task1_fun, "task1", 1024, NULL, 10, &task1_handle, 1);
}