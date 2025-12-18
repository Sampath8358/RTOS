#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
SemaphoreHandle_t sem;
TaskHandle_t task1;
TaskHandle_t task2;
TaskHandle_t task3;
TaskHandle_t task4;
int value = 100;

void my_fun1(void *)
{
    while (1)
    {
        xSemaphoreTake(sem, portMAX_DELAY);
        value++;
        printf("in the fun1 %d done\n", value);
        xSemaphoreGive(sem);
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
    vTaskDelete(task1);
}
void my_fun2(void *)
{
    while (1)
    {
        xSemaphoreTake(sem, portMAX_DELAY);
        value++;
        printf("in the fun2 %d done\n", value);
        xSemaphoreGive(sem);
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
    vTaskDelete(task2);
}
void my_fun3(void *)
{
    while (1)
    {
        xSemaphoreTake(sem, portMAX_DELAY);
        printf("in the fun3 reading %d\n", value);
        xSemaphoreGive(sem);
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
    vTaskDelete(task3);
}
void my_fun4(void *)
{
    while (1)
    {
        xSemaphoreTake(sem, portMAX_DELAY);
        printf("in the fun4 reading %d\n", value);
        xSemaphoreGive(sem);
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
    vTaskDelete(task4);
}
    void app_main(void)
{
    sem = xSemaphoreCreateCounting(4,4);
    xTaskCreatePinnedToCore(my_fun1, "my_fun1", 1024, NULL, 2, &task1, 1);
    xTaskCreatePinnedToCore(my_fun2, "my_fun2", 1024, NULL, 3, &task2, 1);
    xTaskCreatePinnedToCore(my_fun3, "my_fun3", 1024, NULL, 4, &task3, 1);
    xTaskCreatePinnedToCore(my_fun4, "my_fun4", 1024, NULL, 5, &task4, 1);
}
