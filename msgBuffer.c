#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/message_buffer.h"
#include <ctype.h>
#include <string.h>
TaskHandle_t task1, task2;
MessageBufferHandle_t buff_handle;

void my_fun1(void *)
{
    xMessageBufferSend( buff_handle,"hello",5,portMAX_DELAY);
    printf("message sent from task1\n");
    vTaskDelete( task1);
}
void my_fun2(void *)
{
    char buffer[100];
    xMessageBufferReceive(buff_handle,buffer,sizeof(buffer),portMAX_DELAY );
    for(int i =0; i<strlen(buffer); i++){
        buffer[i]= toupper(buffer[i]);
    }
    printf("The received msg is %s\n", buffer);
    vTaskDelete( task2);
}
void app_main(void)
{
    buff_handle = xMessageBufferCreate(100);
    xTaskCreatePinnedToCore(my_fun1, "my_fun1", 1024, NULL, 5, &task1, 1);
    xTaskCreatePinnedToCore(my_fun2, "my_fun2", 1024, NULL, 4, &task2, 1);
}
