#define USE_STDPERIPH_DRIVER
#include <string.h>
/*STM Firmware*/
#include "stm32_p103.h" 
#include "stm32f10x.h"
/*Serial IO*/
#include "serial_io.h"
/*FreeRTOS relative */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
/* Filesystem relative */
#include "filesystem.h"
#include "fio.h"
#include "romfs.h"

extern const char _sromfs;
volatile xSemaphoreHandle serial_tx_wait_sem = NULL;
volatile xQueueHandle serial_rx_queue = NULL;

void test_serial_plot()
{
	int roll = 5, pitch = 4, yaw = 0;
	int acc_x = 0, acc_y = 5, acc_z = 2;
	int gyro_x = 0, gyro_y = 2, gyro_z = 5;
	while(1){
		vTaskDelay(20);
		if (roll<90)
			roll++;
		else
			roll = -5;
		if (pitch<80)
			pitch++;
		else
			pitch = -2;

		if (yaw<180)
			yaw += 2;
		else
			yaw = -180;
        printf("Roll,%d ,Pitch,%d,Yaw,%d\r\n",roll,pitch,yaw);
        puts("CH1 3036.0(0.0),CH2 3036.0(0.0),CH3 2074.0(800.0),CH4 3100.0(0.0),CH5 1931.0(On)\r\n");
        puts("PID Roll,0.0,PID PITCH,0.0,PID YAW,1.0\r\n");
        puts("MOTOR 1,798.0,MOTOR 2,802.0,MOTOR 3,798.0,MOTOR 4,802.0\r\n");
	
	}
}
int main()
{
	init_rs232();
	enable_rs232_interrupts();
	enable_rs232();
	
	fs_init();
	fio_init();
	
	register_romfs("romfs", &_sromfs);
	
	/* Create the queue used by the serial task.  Messages for write to
	 * the RS232. */
	vSemaphoreCreateBinary(serial_tx_wait_sem);

	serial_rx_queue = xQueueCreate(1, sizeof(serial_msg));
	/* Create a shell task */
	xTaskCreate(test_serial_plot,
	            (signed portCHAR *) "Shell ENV",
	            512 /* stack size */, NULL, tskIDLE_PRIORITY + 5, NULL);

	/* Start running the tasks. */
	vTaskStartScheduler();

	return 0;
}

void vApplicationTickHook()
{
}
