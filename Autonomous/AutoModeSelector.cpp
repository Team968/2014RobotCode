#include "AutoModeSelector.h"
#include <string>
#include "../RAWCRobot.h"

// Note:
// This is horrible.
// I want to change it

void AutoModeSelector::increment()
{
	index++;
	if(index == amLast)
		index = amFirst + 1;
	//printf("Auto mode selected: %d\r\n",index);
}

string AutoModeSelector::description()
{
	char str[25];
	memset(str, '.', 25);
	string s = "";

	/*
	amLeft1,
	amLeft2,
	amMiddle1,
	amMiddle2,
	amMiddle3,
	amRight1,
	amRight2,
	
	*/
	
	switch (index)
	{
	case amShoot1:
		sprintf(str,"Auton 1");
		s.assign(str);
		break;
	case amShoot2:
		sprintf(str,"Auton 2");
		s.assign(str);
		break;
	case amDrive:
		sprintf(str,"Auton ");
		s.assign(str);
		break;
		
/*	case amMiddle1:
		sprintf(str,"Middle Lane - 1 Tube  ");
		s.assign(str);
		break;
	case amMiddle2:
		sprintf(str,"Middle Lane - 2 Tube  ");
		s.assign(str);
		break;
	case amMiddle3:
		sprintf(str,"Middle Lane - 3 Tube  ");
		s.assign(str);
		break;
	case amRight1:
		sprintf(str,"Right Lane - 1 Tube   ");
		s.assign(str);
		break;
	case amRight2:
		sprintf(str,"Right Lane - 2 Tube   ");
		s.assign(str);
		break;*/
	case amDoNothing:
		sprintf(str,"Do Nothing (Far Zone) ");
		s.assign(str);
		break;
	default:
		sprintf(str,"It broke              ");
		index = amFirst + 1;
		s.assign(str);
		break;
	}

	return s;
}

void AutoModeSelector::writeToAutoModeController(AutoModeController * autoController)
{
	autoController->reset();
	//autoController->addCommand(CMD_WAIT, 0, 0, ARM_STOP, 1);
	switch(index)
	{
	
	//0.0429296875
	case amShoot1:
		autoController->addCommand(CMD_DRIVE, 0, 0 , 0 ,1);
		autoController->addCommand(CMD_SHOOT, 0, 0, 0, 1);
		autoController->addCommand(CMD_RELEASE, 0, 0, 0, 2);
		autoController->addCommand(CMD_SETUP, 0, 0, 0, 4);
		//autoController->addCommand(CMD_SHOOT2,0, 0 , 0 ,6);
		break;
	case amShoot2:
		autoController->addCommand(CMD_SHOOT2,0, 0 , 0 ,6);
		break;
	case amDrive:
		autoController->addCommand(CMD_DRIVE, 0, 0, 0, 1.25);
		break;

	case amDoNothing:

		break;
	default:
		index = amFirst + 1;
		break;
	}
	
	
	//TDO: Make this
}
