#include "vofa_task.h"

#include "cmsis_os.h"
#include "main.h"

#include "usart.h"
#include "dma.h"

#include "vofa.h"

#include "imu901.h"
#include "height.h"

float send_message[channel];

void Vofa_task(void const * argument)
{
  Vofa_tail_init();
	while(1)
	{
		message_send_buf();
		
		Vofa_send_justfloat(send_message);
		
		HAL_UART_Transmit_DMA(&huart1, Vofa.message, sizeof(Vofa.message));
		
		vTaskDelay(VOFA_TASK_TIME_MS);
		
	}
}

#include "math.h"

void message_send_buf(void)
{
	/*!< �û�4ͨ�� */
	send_message[0] = height.baro;
	send_message[1] = 0;
	send_message[2] = 0;
	send_message[3] = 0;
	
	/*!< ��̬�ǡ� */
	send_message[4] = attitude.roll;
	send_message[5] = attitude.pitch;
	send_message[6] = attitude.yaw;
	
	/*!< ������ת�١�/S */
	send_message[7] = gyroAccData.fgyroD[0];
	send_message[8] = gyroAccData.fgyroD[1];
	send_message[9] = gyroAccData.fgyroD[2];
	
	/*!< ���ٶ����� G */
	send_message[10] = gyroAccData.faccG[0];
	send_message[11] = gyroAccData.faccG[1];
	send_message[12] = gyroAccData.faccG[2];
	
	/*!< �ų����� */
	send_message[13] = magData.mag[0];
	send_message[14] = magData.mag[1];
	send_message[15] = magData.mag[2];
	/*!< �������¶� */
	send_message[16] = magData.temp;
	
	/*!< ��ѹֵPa */
	send_message[17] = baroData.pressure;
	/*!< ���θ߶�cm */
	send_message[18] = baroData.altitude;
	/*!< ��ѹ���¶� */
	send_message[19] = baroData.temp;
	
	/*!< ����������ٶ����� m/ss  */
	send_message[20] = height.ax;
	send_message[21] = height.ay;
	send_message[22] = height.az;
}
