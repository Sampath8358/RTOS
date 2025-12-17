#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

TaskHandle_t task1_handle, task2_handle, task3_handle, task4_handle;

int task1_flag = 0;
int task3_flag = 0;
int task4_flag = 0;
void task1_fun(void *args)
{
    task1_flag = 1;
    if (task1_flag == 1)
    {
        printf("in task1 function\n");
    }
    vTaskSuspend(task2_handle);
    vTaskDelay(pdMS_TO_TICKS(5000));
    vTaskDelete(NULL);
}

void task2_fun(void *args)
{
    while (1)
    {
        printf("in task2 function\n");
        vTaskDelay(pdMS_TO_TICKS(3000));
    }
}

void task3_fun(void *args)
{
    task3_flag = 1;
    if (task3_flag == 1)
    {
        printf("in task3 function\n");
    }
    vTaskResume(task2_handle);
    vTaskDelete(NULL);
}

void task4_fun(void *args)
{
    task4_flag = 1;
    if (task4_flag == 1)
    {
        printf("in task4 function\n");
    }
    vTaskDelay(pdMS_TO_TICKS(6000));
    vTaskSuspend(task2_handle);
    vTaskResume(task1_handle);
    vTaskDelete(NULL);
}
     
void app_main(void)
{
    xTaskCreatePinnedToCore(task1_fun, "task1", 1028, NULL, 10, &task1_handle, 1);
    xTaskCreatePinnedToCore(task2_fun, "task2", 1028, NULL, 9, &task2_handle, 1);
    xTaskCreatePinnedToCore(task3_fun, "task3", 1028, NULL, 8, &task3_handle, 1);
    xTaskCreatePinnedToCore(task4_fun, "task4", 1028, NULL, 7, &task4_handle, 1);
}
