#include "AutoModeController.h"
#include "../RAWCRobot.h"
#include "../RAWCConstants.h"
#include "../accelFilter.h"
#include <math.h>

AutoModeController* AutoModeController::singletonInstance = NULL;

/// Creates (if needed) and returns a sidngleton Control Board instance
AutoModeController* AutoModeController::getInstance()
{
	if( singletonInstance == NULL)
		singletonInstance = new AutoModeController(); 
	return singletonInstance;
}

AutoModeController::AutoModeController()
:
	previousError(0),
	m_WinchFire(false)

{
	bot = RAWCRobot::getInstance();
	timer = new Timer();
	curCmd = cmdNULL;
	
	extendArm = false;
	
	timer->Start();
	
	reset();
}

void AutoModeController::addCommand(RobotCommandNames_e cmd, 
					cmdArg arg1, cmdArg arg2, cmdArg arg3, cmdArg arg4)
{
	// Make the new command
	RobotCommand newCmd;
	newCmd.cmd = cmd;
	newCmd.encoderCount = arg1;
	newCmd.heading = arg2;
	newCmd.armPos = arg3;
	newCmd.timeout = arg4;
	
	
	// add it to the end of the list
	cmdList.push_back(newCmd);
}

void AutoModeController::reset()
{
	//RAWCConstants * rc = RAWCConstants::getInstance();
	cmdList.clear();
	curCmd = cmdNULL;
	bot->askForShift(RAWCRobot::SHIFTER_POS_HIGH);
	
	
}

bool AutoModeController::handle()
{
	bool result = false;
	bool thisIsNull = false;
	bot->setWinchF(m_WinchFire);
	
	// Run the command
	switch(curCmd.cmd)
	{
	case CMD_DRIVE:
		bot->driveSpeedTurn(1, 0, false);
		bot->setIntakeArm(1);
		m_WinchFire = 1;
		result = false;
		break;
	case CMD_SHOOT:
		result = false;
		doShoot();
		break;
	case CMD_SHOOT2:
		result = false;
		doShoot2();
		break;
	case CMD_SETUP:
		result = true;
		doSetUp();
		break;
	case CMD_RELEASE:
		result = true;
		doRelease();
		break;
	/*case CMD_INTAKE:
		result = true;
		doIntake();
		break;
	case CMD_DOWN:
		result = true;
		downBBQ();
		break;
	case CMD_UP:
		result = true;
		upBBQ();
		break;*/
		default :
			doNothing();
			result = true;
			break;
	}
	
	// Check if this command is done
	if(result == true || thisIsNull || timer->Get() > curCmd.timeout){
		// This command is done, go get the next one
		if(cmdList.size() > 0 )
		{
			curCmd = cmdList.front();
			cmdList.pop_front();
			timer->Reset();
		}
		else curCmd = cmdNULL;
	}
	return false;
}

// Drive Functions
void AutoModeController::doNothing()
{
	bot->driveLeftRight(0,0);
	//bot->getArm()->SetMotor(0);  v  
	//bot->getArm()->
}

/*void AutoModeController::Drive()
{
	bot->setBunnyE(1);
	Wait(5);
}*/
void AutoModeController::doShoot()
{	
	//bot->driveLeftRight(1,1);
	/*bot->driveLeftRight(0,0);
	Wait(4);*/
	///*bot->driveLeftRight(.5,-.5);
	//bot->setIntakeArm(0);
	//Wait(2);
	//bot->setBunnyE(0);
	//Wait(2.5);
	//bot->setWinchF(-1);
	//Wait(4);*/
	
	//Wait(4);
	//bot->driveLeftRight(0,0);
	/*bot->setBunnyE(1);
	bot->setIntakeArm(1);
	Wait(2);
	bot->driveLeftRight(0,0);
	bot->setWinchF(-1);
	Wait(2.3);*/
	m_WinchFire = 0;
	/*bot->setWinch(-1);
	Wait(4);
	bot->setWinch(0);
	bot->driveLeftRight(1,1);
	Wait(3);
	bot->driveLeftRight(0,0);
	bot->setBunnyE(-1);
	Wait(5.1);
	bot->setIntake(-1);
	bot->setBunnyE(1);
	Wait(3);
	bot->setWinchF(-1);
	Wait(2.3);
	bot->setWinchF(1);
	Wait(3);
	bot->setWinch(-1);
	Wait(4);
	bot->setWinch(0);*/
}
void AutoModeController::doRelease()
{
	m_WinchFire = 1;
}
void AutoModeController::doSetUp()
{
	if (bot->LimitA->Get() == 1)
			{
		bot->setWinch(-1);
			}
	else if (bot->LimitA->Get() == 0)
	{
		bot->setWinch(0);
	}
}
void AutoModeController::doShoot2()
{
	bot->driveLeftRight(1,1);
	bot->setIntake(1);
	Wait(4);
	m_WinchFire = 1;
	bot->setBunnyE(0);
	bot->setIntakeArm(0);
	//bot->driveLeftRight(0,0);
	//this is only for now; gonna needa put a switch or something
		
		/*bot->setWinch(1);
		bot->setBunnyE(0);
		Wait(3);
		bot->setWinch(0);
		bot->setIntakeArm(1);
		bot->setBunnyE(1);
		bot->setWinchF(1);
		Wait(2);
		bot->setWinchF(0);*/
	//bot->setWinch(1);
//	bot->setBunnyE(0);
/*	if(bot->LimitA->Get() == 1)
	{
		bot->setWinch(0);
		bot->setIntakeArm(1);
		bot->setBunnyE(1);
		bot->setWinchF(1);
		Wait(2);
		bot->setWinchF(0);
		
	}*/
}
/*void AutoModeController::doSetUp()
{
	bot->setShooter(1);
	bot->setLift(0);
	//bot->setIntakeD(1);
}*/
/*void AutoModeController::doPyramid()
{
	bot->setShooter(.9);
	bot->setCblock(0);
	Wait(3);
	bot->setCblock(1);
	bot->setConveyer(.15);
	Wait(6);
	bot->setShooter(0);
	bot->setCblock(0);
	bot->setConveyer(0);
	bot->setIntakeD(1);
	Wait(6.5);
	bot->setBBQ(-1);
	Wait(7.5);
	bot->setBBQ(0);
	bot->driveLeftRight(.5,.5)
	bot->setConveyer(1);
	bot->setRoller(1);
	Wait(8.5);
	bot->driveLeftRight(0,0)
	Wait(11);
	bot->setBBQ(1);
	bot->setConveyer(0);
	bot->setRoller(0);
	Wait(12);
	bot->setBBQ(0);
	bot->setShooter(1);
	bot->setCblock(1);
	bot->setConveyer(.15)
}*/
/*void AutoModeController::doIntake()
{
	bot->driveLeftRight(.5,.5);
	bot->setRoller(1);
	bot->setConveyer(1);
}*/
//void AutoModeController::downBBQ()
//{

//	bot->setBBQ(-1);
	
//}
//void AutoModeController::upBBQ()
//{
//	bot->setBBQ(1);
	//bot->setShooter(1);
//}
/*bool AutoModeController::turnHeading(cmdArg heading)
{
	const float pGain = 0.9;
	
	//float currentHeading = bot->getGyro()->GetAngle();
	float turn = heading - currentHeading;
	turn /= 100;
	
	bot->getRightEncoder()->Reset();
	
	previousError = turn;
	
	//printf("%f\r\n", turn);
	
	float output = (LimitMix(turn) * pGain) + (LimitMix(previousError - turn) * 0.3);
	bot->driveLeftRight(output, -output);
	
	if((currentHeading < heading + 1 && currentHeading > heading - 1))
	{
		printf("Done with distance\r\n");
		return false;
	}	
	else
		return false;
}*/
/*bool AutoModeController::driveDistanceWithHeading(cmdArg distance, cmdArg heading)
{
	float distanceP = bot->getLeftEncoder()->GetRaw() - distance;
	float currentDistance = bot->getLeftEncoder()->GetRaw();
	float turn = heading - bot->getGyro()->GetAngle();
	
	turn /= 100;
	distanceP *= 0.005;
	
	//printf("%f\r\n", currentDistance);
		
	bot->driveSpeedTurn(LimitMix(distanceP) * 0.90, LimitMix(-turn)*1.3, true);
	if(currentDistance > distance)
	{
		return true;
	}	
	else
		return false;
}*/

bool AutoModeController::driveDistancePWithHeading(cmdArg distance, cmdArg heading)
{
	float distanceP = bot->getLeftEncoder()->GetRaw() - distance;
	//float currentDistance = bot->getRightEncoder()->GetRaw();
	//float currentHeading = bot->getGyro()->GetAngle();
	//float turn = heading - bot->getGyro()->GetAngle();
		
	distanceP *= 0.005;
	//turn /= 100;
	
	//printf("%f\r\n", currentDistance);
		
	//bot->driveSpeedTurn(LimitMix(distanceP) * 0.9, LimitMix(-turn)*1.3, true);
	bot->driveSpeedTurn(LimitMix(distanceP) * .3, 0, true);
	/*if((currentDistance < distance + 40 && currentDistance > distance - 40) &&
	   (currentHeading < heading + 1 && currentHeading > heading -1))
	{
		printf("Done with distance\r\n");
		return true;
	}	
	else*/
		return false;
}



