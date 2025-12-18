#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
TaskHandle_t task1, task2;
SemaphoreHandle_t sem1;
int value = 100;
void my_fun(void *)
{
    while (1)
    {
        // xSemaphoreTake(sem1, portMAX_DELAY);
        value++;
        printf("In the task1 %d\n", value);
        vTaskDelay(pdMS_TO_TICKS(500));
        xSemaphoreGive(sem1);
    }
}
void my_fun2(void *)
{
    while (1)
    {
        printf("hello\n");
        xSemaphoreTake(sem1, portMAX_DELAY);
        value--;
        printf("In the task2 %d\n", value);
        vTaskDelay(pdMS_TO_TICKS(1000));
        // xSemaphoreGive(sem1);
    }
}

void app_main(void)
{
    sem1 = xSemaphoreCreateBinary();
    xTaskCreatePinnedToCore(my_fun, "my_fun", 1024, NULL, 4, &task1, 0);
    xTaskCreatePinnedToCore(my_fun2, "my_fun2", 1024, NULL, 5, &task2, 0);
}
