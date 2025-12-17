#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

TaskHandle_t task1_handle, task2_handle, task3_handle;

void task1_fun(void *args)
{
    while (1)
    {
        printf("in the task1\n");
        vTaskDelay(pdMS_TO_TICKS(1000));
        vTaskResume(task2_handle);
        vTaskSuspend(task1_handle);
    }

    // printf("in task1 function\n");
        // vTaskDelay(pdMS_TO_TICKS(5000));
    // vTaskResume(task2_handle);
    // vTaskResume(task3_handle);
    // vTaskDelete(NULL);
}

void task2_fun(void *args)
{
    vTaskSuspend(task2_handle);
    while (1)
    {
        printf("in the task2\n");
        vTaskDelay(pdMS_TO_TICKS(1000));
        vTaskResume(task3_handle);
        vTaskSuspend(task2_handle);
    }
    // vTaskSuspend(NULL);
    // printf("in task2 function\n");
    // vTaskDelete(NULL);
}

void task3_fun(void *args)
{
    vTaskSuspend(task3_handle);
    while (1)
    {
        printf("in the task3\n");
        vTaskDelay(pdMS_TO_TICKS(1000));
        vTaskResume(task1_handle);
        vTaskSuspend(task3_handle);
    }
    // vTaskSuspend(NULL);
    // printf("in task3 function\n");
    // vTaskDelete(NULL);
}
void app_main(void)
{
    xTaskCreatePinnedToCore(task1_fun, "task1", 1028, NULL, 7, &task1_handle, 1);
    xTaskCreatePinnedToCore(task2_fun, "task2", 1028, NULL, 9, &task2_handle, 1);
    xTaskCreatePinnedToCore(task3_fun, "task3", 1028, NULL, 8, &task3_handle, 1);
}
