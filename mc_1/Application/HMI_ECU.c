/*
 ============================================================================
 Name        : Final_Project.c
 Author      : Abdelrahman Shabrawy
 Description : HMI_ECU
 Date        : 20/08/2023
 ============================================================================
 */
#include"HML_ECU.h"

void (*ptr_states[3])(void)={createandStorePassword,mainFucntion,lockingUnlockingScreen};

static volatile uint8 g_flag=0;
static volatile uint8  g_stateNum;
uint8 g_key;
uint8 g_password[5]={0};
/* uint8 g_password2[5]; */
uint8 command;
uint8 g_wrong=0;
uint16 g_tick=0;

UART_ConfigType uart_config={BIT_8,DISABLED,ONE_BIT,9600};
Timer1_ConfigType timer1_config= {OVERFLOW,0,0,F_CPU_8};
int main()
{
	LCD_init();
	UART_init(&uart_config);
	LCD_clearScreen();
	LCD_displayStringRowColumn(0,0,"DOOR SECURITY");
	LCD_displayStringRowColumn(1,0,"SYSTEM");
	_delay_ms(2000);
	createandStorePassword();
	SREG |= (1<<7);
	while(1){
		(*ptr_states[g_stateNum])();
	}
}

void createandStorePassword(void)
{
	if(g_flag == 0){
		LCD_clearScreen();
		LCD_displayStringRowColumn(0,0,"ENTER NEW PASS:");
		LCD_moveCursor(1,0);
		enterPassword(g_password);
		sendCommand(I_WILL_SEND_A_PASSWORD);
		SendPassword(g_password);
		g_flag = 1;
	}
	if(g_flag == 1)
	{
		LCD_clearScreen();
		LCD_displayStringRowColumn(0,0,"RE-ENTER PASS:");
		LCD_moveCursor(1,0);
		g_password[4]=66;		/* any random number greater than 9 to change the original to avoid similarity if user enters same pass but not 5 num */
		enterPassword(g_password);
		sendCommand(COMPARE_TWO_PASSWORDS);
		SendPassword(g_password);
		g_flag = 2;
	}
	if (g_flag == 2)
	{
		switch(recieveCommand())
		{
		case PASSWORDS_MATCH:
			g_flag =3 ;
			g_stateNum = 1;
			break;

		case PASSWORDS_DONOT_MATCH:
			PasswordDONTMATCHScreen();
			g_flag = 0;
			break;
		}
	}
}
void SendPassword(uint8 a_arr[])
{
	UART_sendByte(READY);
	while(UART_recieveByte() != READY){};

	for(uint8 i = 0;i < PASSWORD_SIZE;i++)
	{
		UART_sendByte(a_arr[i]);
	}
	while(UART_recieveByte() != DONE){};
}
void sendCommand(uint8 command)
{
	UART_sendByte(READY);
	while(UART_recieveByte() != READY){};
	UART_sendByte(command);
	while(UART_recieveByte() != DONE){};

}
uint8 recieveCommand(void)
{
	while(UART_recieveByte() != READY){};
	UART_sendByte(READY);
	command = UART_recieveByte();
	UART_sendByte(DONE);
	return command;
}
void mainFucntion(void)
{
	LCD_clearScreen();
	LCD_displayStringRowColumn(0,0,"(+):OPEN DOOR");
	LCD_displayStringRowColumn(1,0,"(-):CHANGE PASS");
	switch(KEYPAD_getPressedKey())
	{

	case '+':
		LCD_clearScreen();
		LCD_displayStringRowColumn(0,0,"ENTER YOUR PASS");
		LCD_moveCursor(1,0);
		_delay_ms(500);
		g_password[4]=50;
		enterPassword(g_password);
		sendCommand(IS_PASSWORD_RIGHT);
		SendPassword(g_password);
		switch (recieveCommand()){
		case PASSWORDS_MATCH:
			sendCommand(OPEN_DOOR);
			g_stateNum=2;
			g_wrong=0;
			break;
		case PASSWORDS_DONOT_MATCH:
			wrongPasswordScreen();
			break;
		}
		break;
		case '-':
			LCD_clearScreen();
			LCD_displayStringRowColumn(0,0,"ENTER YOUR PASS");
			LCD_moveCursor(1,0);
			_delay_ms(500);
			g_password[4]=50;
			enterPassword(g_password);
			sendCommand(IS_PASSWORD_RIGHT);
			SendPassword(g_password);
			switch (recieveCommand())
			{
			case PASSWORDS_MATCH:
				g_flag=0;
				g_stateNum=0;
				g_wrong=0;
				break;
			case PASSWORDS_DONOT_MATCH:
				wrongPasswordScreen();
				break;
			}
			break;
	}

}
void wrongPasswordScreen(void)
{
	LCD_clearScreen();
	LCD_displayStringRowColumn(0,1,"WRONG PASS!!");
	g_wrong++;
	sendCommand(WRONG_PASSWORD);
	if(g_wrong == MAX_WRONG_COUNTER)
	{
		LCD_clearScreen();
		Timer1_init(&timer1_config);
		Timer1_setCallBack(g_tickCounterAlarm);
		while(g_tick<TIMER_TICKS_1MINUTE)
		{
			LCD_displayStringRowColumn(0,0,"SECURITY ALERT");
		}
		g_tick=0;
		g_wrong=0;
		g_stateNum=1;
	}
	_delay_ms(2000);

}
void enterPassword(uint8 x[])
{
	uint8 i=0;
	while (1)
	{
		g_key=KEYPAD_getPressedKey();
		while(g_key != '=')
		{
			g_key=KEYPAD_getPressedKey();
			if(g_key>= 0 && g_key<= 9)
			{
				if(i < PASSWORD_SIZE)
				{
					x[i]=g_key;
					LCD_displayCharacter('*');
					i++;
				}
			}
			_delay_ms(500);
		}
		if (i < PASSWORD_SIZE  && g_flag == 0)
		{
			LCD_clearScreen();
			LCD_displayStringRowColumn(0, 0, "plz enter FIVE ");
			LCD_displayStringRowColumn(1, 0, "numbers");
			i=0;
			_delay_ms(3000);
			LCD_clearScreen();
			LCD_displayStringRowColumn(0, 0, "ENTER NEW PASS:");
			LCD_moveCursor(1, 0);
		}
		else
			break;
	}

}
void PasswordDONTMATCHScreen(void)
{
	LCD_clearScreen();
	LCD_displayStringRowColumn(0,0,"PASS DONT MATCH..");
	_delay_ms(3000);

}
void lockingUnlockingScreen(void)
{
	LCD_clearScreen();
	Timer1_init(&timer1_config);
	Timer1_setCallBack(g_tickCounterMotor);
	while(g_tick < TICKS_15SECS)
	{
		LCD_displayStringRowColumn(0,0,"DOOR UNLOCKING..");
	}
	LCD_clearScreen();
	while(g_tick>=TICKS_15SECS && g_tick<TIMER_TICKS_15SEC_STOP)////delay 3 seconds
	{
	}
	g_tick=0;
	Timer1_deinit();
	Timer1_init(&timer1_config);
	while(g_tick<TICKS_15SECS)
	{
		LCD_displayStringRowColumn(0,0,"DOOR LOCKING..");
	}
	LCD_clearScreen();
	while(g_tick>=TICKS_15SECS && g_tick<TIMER_TICKS_15SEC_STOP)
	{
		LCD_displayStringRowColumn(0,0,"DOOR ClOSED");
	}
	g_tick=0;
	g_stateNum=1;
}
void g_tickCounterMotor(void)
{
	g_tick++;
	if(g_tick==TIMER_TICKS_15SEC_STOP)
	{
		Timer1_deinit();
	}
}
void g_tickCounterAlarm(void)
{
	g_tick++;
	if(g_tick==TIMER_TICKS_1MINUTE)
	{
		Timer1_deinit();
	}
}

