#include<stdio.h>
#include<freertos/FreeRTOS.h>
#include<freertos/task.h>
#include<freertos/queue.h>

#define MQ_SIZE 4
#define MSG_SIZE 64

TaskHandle_t task_h1,task_h2,task_h3,task_h4,task_h5;
QueueHandle_t msg_que;

static int taskcore=1;

void task_1(void *data)
{    
    printf("\nSerial Task 1 : Started\n");
    vTaskDelay(pdMS_TO_TICKS(1000));
}
void task_2(void *data)
{     
    printf("\nSerial Task 2 : Started\n");
    vTaskDelay(pdMS_TO_TICKS(2000));
}
void task_3(void *data)
{
    printf("\nSerial Task 3 : Started\n");
    vTaskDelay(pdMS_TO_TICKS(5000));
}
void task_4(void *data)
{
    int task1_data = 100;
    printf("Task 1 \n");
    while(1)
    {
        task1_data++;
        xQueueSend(msg_que,&task1_data,pdMS_TO_TICKS(5000));
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
    vTaskDelete(NULL);
}
void task_5(void *data)
{
    int buffer=0;
    printf("Task 1 \n");
    while(1)
    {
        xQueueReceive(msg_que,&buffer,portMAX_DELAY);
        //vTaskDelay(1000 / portTICK_PERIOD_MS);
        printf("task 1 received data:%d\n",buffer);
    }
    vTaskDelete(NULL);
}
void app_main()
{    
	    BaseType_t prio,prio3,prio4,prio1,prio2,mt_prio;
    	printf("\nDESD RTOS EXAM");
        printf("\nMain Task\n");
    	xTaskCreate(task_1,"Serialtask",2048,NULL,5,&task_h1);
    	xTaskCreate(task_2,"Serialtask",2048,NULL,6,&task_h2);
    	xTaskCreate(task_3,"Serialtask",2048,NULL,7,&task_h3);
        xTaskCreate(task_4,"Serialtask",2048,NULL,7,&task_h4);
        xTaskCreate(task_5,"Serialtask",2048,NULL,7,&task_h5);
        prio=uxTaskPriorityGet(task_h1);
	    prio1=uxTaskPriorityGet(task_h2);
    	prio2=uxTaskPriorityGet(task_h3);
        prio3=uxTaskPriorityGet(task_h4);
        prio4=uxTaskPriorityGet(task_h5);
	    mt_prio=uxTaskPriorityGet(NULL);
    	printf("priority of the serial task : %d\n",prio);
    	printf("priority of the serial task : %d\n",prio1);
    	printf("priority of the serial task : %d\n",prio2);
        printf("priority of the serial task : %d\n",prio3);
        printf("priority of the serial task : %d\n",prio4);
     	printf("priority of the main task : %d\n",mt_prio);
    	msg_que=xQueueCreate(MQ_SIZE,MSG_SIZE);
    	xTaskCreatePinnedToCore(task_4,"task1",2048,NULL,8,&task_h4,taskcore);
    	xTaskCreatePinnedToCore(task_5,"task1",2048,NULL,9,&task_h5,taskcore);
}

