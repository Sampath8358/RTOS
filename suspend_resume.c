#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

TaskHandle_t task1_handle, task2_handle, task3_handle;

void my_fun1(void *args)
{
    while (1)
    {
        for (int i = 0; i < 5; i++)
        {
            printf("task1\n");
            vTaskDelay(pdMS_TO_TICKS(1000));
        }

        vTaskResume(task2_handle);
        vTaskResume(task3_handle);

        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

void my_fun2(void *args)
{
    while (1)
    {
        vTaskSuspend(NULL);
        printf("task2\n");
    }
}

void my_fun3(void *args)
{
    while (1)
    {
        vTaskSuspend(NULL);
        printf("task3\n");
    }
}

void app_main(void)
{
    xTaskCreatePinnedToCore(my_fun1, "task1", 2048, NULL, 10, &task1_handle, 1);
    xTaskCreatePinnedToCore(my_fun2, "task2", 2048, NULL, 8,  &task2_handle, 1);
    xTaskCreatePinnedToCore(my_fun3, "task3", 2048, NULL, 7,  &task3_handle, 1);
}
