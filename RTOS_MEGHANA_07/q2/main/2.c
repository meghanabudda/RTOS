#include<stdio.h>
#include<freertos/FreeRTOS.h>
#include<freertos/task.h>
#include<freertos/timers.h>


TaskHandle_t task_h1,task_h2,task_h3;
TimerHandle_t xTimers;
const TickType_t xDelay1=1000 /portTICK_PERIOD_MS;
const TickType_t xDelay2=2000 /portTICK_PERIOD_MS;
const TickType_t xDelay3=5000 /portTICK_PERIOD_MS;
void vTimerCallback(TimerHandle_t xTimers)
{
	printf("\nTimer is fired");
}
void task_1(void *data)
{    
    printf("\nSerial Task 1 : Started\n");
    vTaskDelay(xDelay1);
}
void task_2(void *data)
{     
    printf("\nSerial Task 2 : Started\n");
    vTaskDelay(xDelay2);
}
void task_3(void *data)
{
    int x;
    printf("\nSerial Task 3 : Started\n");
    xTimer=xTimerCreate( "one_s_timers",10000 /portTICK_PERIOD_MS,pdTRUE, 0,vTimerCallback );
    xTimerStart( xTimers, 0 );
    vTaskDelay(xDelay3);
    vTaskDelete(task_h3);

}
void app_main()
{    
	BaseType_t prio,prio1,prio2,mt_prio,serial1,serial2,serial3;
    printf("\nDESD RTOS EXAM");
    serial1=xTaskCreate(task_1,"Serialtask",2048,NULL,5,&task_h1);
    if(serial1==pdPASS)
    {
    	printf("Task 1 is successfully created");
    }
    serial2=xTaskCreate(task_2,"Serialtask",2048,NULL,6,&task_h2);
    if(serial2==pdPASS)
    {
    	printf("Task 2 is successfully created");
    }
    serial3=xTaskCreate(task_3,"Serialtask",2048,NULL,7,&task_h3);
    if(serial3==pdPASS)
    {
    	printf("Task 3 is successfully created");
    }
    prio=uxTaskPriorityGet(task_h1);
	prio1=uxTaskPriorityGet(task_h2);
    prio2=uxTaskPriorityGet(task_h3);
	mt_prio=uxTaskPriorityGet(NULL);
    printf("priority of the serial task : %d\n",prio);
    printf("priority of the serial task : %d\n",prio1);
    printf("priority of the serial task : %d\n",prio2);
    printf("priority of the main task : %d\n",mt_prio);
}

