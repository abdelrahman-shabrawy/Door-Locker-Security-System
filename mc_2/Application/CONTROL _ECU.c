/*
 ============================================================================
 Name        : Final_Project.c
 Author      : Abdelrahman Shabrawy
 Description : CONTROL_ECU
 Date        : 20/08/2023
 ============================================================================
 */

#include "CONTROL_ECU.h"



uint8 g_password[5];
uint8 g_pass2[5];
uint8 savedpass[5];
uint8 command;
uint16 g_tick=0;
uint8 g_wrong=0;

UART_ConfigType uart_config={BIT_8,DISABLED,ONE_BIT,9600};
Timer1_ConfigType timer1_config= {OVERFLOW,0,0,F_CPU_8};

int main()
{
	UART_init(&uart_config);
	SREG |= (1<<7);
	while(1){
		switch(recieveCommand())
		{
		case I_WILL_SEND_A_PASSWORD:
			recievePassword(g_password);
			break;
		case COMPARE_TWO_PASSWORDS:
			recievePassword(g_pass2);
			if(checkMatching(g_password,g_pass2)){
				storePassword();
				getSavedPassword(savedpass);
				sendCommand(PASSWORDS_MATCH);
			}
			else
			{
				sendCommand(PASSWORDS_DONOT_MATCH);
			}
			break;
		case IS_PASSWORD_RIGHT:
			recievePassword(g_password);
			getSavedPassword(savedpass);
			if(checkMatching(g_password,savedpass))
			{
				sendCommand(PASSWORDS_MATCH);
				g_wrong=0;
			}
			else
			{
				sendCommand(PASSWORDS_DONOT_MATCH);
			}
			break;
		case OPEN_DOOR:
			DcMotor_Init();
			Timer1_init(&timer1_config);
			Timer1_setCallBack(g_tickCounterMotor);
			while(g_tick < TICKS_15SECS)
			{
				DcMotor_Rotate(CW, 100);
			}
			DcMotor_Rotate(STOP, 0);
			while(g_tick>=TICKS_15SECS && g_tick<TIMER_TICKS_15SEC_STOP)
			{
			}
			g_tick=0;
			Timer1_deinit();
			Timer1_init(&timer1_config);
			while(g_tick<TICKS_15SECS)
			{
				DcMotor_Rotate(A_CW, 100);
			}
			DcMotor_Rotate(STOP, 0);
			g_tick=0;
			break;
		case WRONG_PASSWORD:
			g_wrong++;
			if(g_wrong==MAX_WRONG_COUNTER)
			{
				Buzzer_init();
				Timer1_init(&timer1_config);
				Timer1_setCallBack(g_tickCounterBuzzer);
				while(g_tick<TIMER_TICKS_1MINUTE)
				{
					Buzzer_on();
				}
				Buzzer_off();
				g_tick=0;
				g_wrong=0;
				_delay_ms(2000);
			}
			break;
		}
	}
}
void recievePassword(uint8 a_arr[])
{
	while(UART_recieveByte() != READY){};
	UART_sendByte(READY);
	for(int i=0 ; i<PASSWORD_SIZE ; i++){
		a_arr[i]=UART_recieveByte();
	}
	UART_sendByte(DONE);
}
uint8 checkMatching(uint8 a_arr1[],uint8 a_arr2[])
{
	uint8 count=0;
	for(uint8 i=0 ; i<PASSWORD_SIZE ; i++)
	{
		if(a_arr1[i]==a_arr2[i])
		{
			count++;
		}
		else
			return 0;
	}
	if(count==PASSWORD_SIZE){
		return 1;
	}
	return 0;
}
void storePassword(void)
{
	EEPROM_init();
	for(uint8 i=0;i<PASSWORD_SIZE;i++){
		EEPROM_writeByte(0x0311+i,g_password[i]);
		_delay_ms(20);
	}

}
uint8 recieveCommand(void)
{
	while(UART_recieveByte() != READY){};
	UART_sendByte(READY);
	command=UART_recieveByte();
	UART_sendByte(DONE);
	return command;
}
void sendCommand(uint8 command)
{
	UART_sendByte(READY);
	while(UART_recieveByte() != READY){};
	UART_sendByte(command);
	while(UART_recieveByte() != DONE){};
}
void getSavedPassword(uint8 a_arr[])
{
	EEPROM_init();
	for(uint8 i=0 ; i<PASSWORD_SIZE ; i++){
		EEPROM_readByte(0x0311+i, &a_arr[i]);
		_delay_ms(20);
	}
}
void g_tickCounterMotor(void)
{
	g_tick++;
	if(g_tick==TIMER_TICKS_15SEC_STOP)
	{
		Timer1_deinit();
	}
}
void g_tickCounterBuzzer(void)
{
	g_tick++;
	if(g_tick==TIMER_TICKS_1MINUTE)
	{
		Timer1_deinit();
	}
}
