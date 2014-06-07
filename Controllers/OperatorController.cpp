//=============================================================================
// File: OperatorController.cpp
//
// COPYRIGHT 2010 Robotics Alliance of the West Coast(RAWC)
// All rights reserved.  RAWC proprietary and confidential.
//             
// The party receiving this software directly from RAWC (the "Recipient")
// may use this software and make copies thereof as reasonably necessary solely
// for the purposes set forth in the agreement between the Recipient and
// RAWC(the "Agreement").  The software may be used in source code form
// solely by the Recipient's employees/volunteers.  The Recipient shall have 
// no right to sublicense, assign, transfer or otherwise provide the source
// code to any third party. Subject to the terms and conditions set forth in
// the Agreement, this software, in binary form only, may be distributed by
// the Recipient to its users. RAWC retains all ownership rights in and to
// the software.d
//
// This notice shall supercede any other notices contained within the software.
//=============================================================================
#include "OperatorController.h"
#include "WPILib.h"
#include "../RAWCLib.h"
#include "../RAWCControlBoard.h"
#include "../RAWCRobot.h"
#include "../Declarations.h"


// Constructor
// TODO: We might not need to pass in Joysticks, if they come from the ControlBoard
OperatorController::OperatorController()
{
	bot = RAWCRobot::getInstance();
	cb = RAWCControlBoard::getInstance();
}

// call this when you want to update the bot from a driver
void OperatorController::handle()
{	
	// Drive shifting
	/*if( cb->getButtonShifter() )
		bot->askForShift(RAWCRobot::SHIFTER_POS_HIGH);
	else
		bot->askForShift(RAWCRobot::SHIFTER_POS_LOW);*/
	if( cb->getButtonShifter() )
		{bot->setShifter(1);
		bot->setShifterReverse(0);}
	else
		{bot->setShifter(0);
		bot->setShifterReverse(1);}
	

	
	//THIS MAKES IT DRIVE!
	{if( cb->getDriveButton(SHIFTER_BUTTON))
	bot->driveSpeedTurn(cb->getDriveStickY(), cb->getSteeringX(), cb->getSteeringButton(FAST_TURN));
	else
	bot->driveSpeedTurn(cb->getDriveStickY(), cb->getSteeringX(), cb->getSteeringButton(FAST_TURN));
	}
	//actual controls
	bot->setIntake(cb->getDriveButton(3));
	if (cb->getDriveButton(2))
	{
		bot->setIntake(-1);
		bot->setNew(0);
	}
	else 
		{
		bot->setNew(0);
		}
	if(cb->getOperatorButton(6))
	{
		bot->setIntake(-1);
		
	}
	if(cb->getOperatorButton(7))
	{
		bot->setIntake(1);
	}
	
	//bot->setWinch(cb->getOperatorButton(5));
	//if(cb->getOperatorButton(5))
	{
		//bot->setWinch(-1);
	}
	/*if (cb->getOperatorButton(5))
	{
		bot->setWinch(1);
		if (bot->LimitA->Get() == 1)
		if (bot->LimitA->Get()==1)
	{bot->setWinch(0);}
	}*/
	bot->setBunnyE(cb->getOperatorButton(4));
		
		//bot->setNew(1);
	bot->setWinchF(cb->getOperatorButton(3));
		if (cb->getOperatorButton(3))
		{
			bot->setWinchF(-1);
			Wait(0);
			//bot->setWinchF(0);
		}
		
	if (bot->LimitA->Get() == 0)
		{
		bot->setWinch(0);
		}
	else if(bot->LimitA->Get() == 1)
		{	
		//bot->setWinch(cb->getOperatorButton(5));
		if(cb->getOperatorButton(5))
			{
				bot->setWinch(-1);
			}
		}
	
	bot->setSTOP(cb->getOperatorButton(7));
		if (cb->getOperatorButton(7))
		{
			bot->setSTOP(-1);
		}
	bot->setIntakeArm(cb->getOperatorButton(1));
	bot->setNew(cb->getOperatorButton(2));}
	
/*	bot->setShooter(cb->getOperatorButton(3));
	bot->setLift(cb->getSteeringButton(3));
	bot->setCblock(cb->getOperatorButton(3));
	bot->setBBQ(cb->getOperatorY());
	bot->setIntakeD(cb->getOperatorButton(1));*/
	/*if (cb->getOperatorButton(1))
	{
		if(cb->getOperatorButton(4))
			bot->setRoller(-1);
		else bot->setRoller(0);
	}*/
/*	if (cb->getOperatorButton(3))		
	{
			if(cb->getOperatorButton(4))	
			{
				bot->setConveyer(.4);
			}
			}
	bot->setConveyer(cb->getOperatorButton(4));
	if (cb->getOperatorButton(2))
	{
		bot->setConveyer(-1);
	}
*/
//}
