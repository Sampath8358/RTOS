#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

TaskHandle_t task1_handle;

typedef struct
{
    int a;
    int b;
} SwapArgs;

void swap(void *args)
{
    SwapArgs *ptr = (SwapArgs *)args;
    int temp = ptr->a;
    ptr->a = ptr->b;
    ptr->b = temp;
    printf("a = %d\nb = %d\n", ptr->a, ptr->b);
    vTaskDelete(task1_handle);
}

void app_main(void)
{
    SwapArgs *args = malloc(sizeof(SwapArgs));
    args->a = 10;
    args->b = 20;
    xTaskCreate(swap, "task1", 1028, args, 2, &task1_handle);
    UBaseType_t ret = uxTaskPriorityGet(task1_handle);
    printf("Priority of task1 is %d\n",ret);
}
