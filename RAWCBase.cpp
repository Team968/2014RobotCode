//=============================================================================
// File: RAWCBase.cpp
//
// COPYRIGHT 2011 Robotics Alliance of the West Coast(RAWC)
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
// the software.
//
// This notice shall supercede any other notices contained within the software.
//=============================================================================

#include "WPILib.h"
#include "RAWCRobot.h"
#include "DashboardDataFormat.h"
#include "Vision/AxisCamera.h"
#include "Controllers/OperatorController.h"
#include "Controllers/AutoModeController.h"
#include "Autonomous/AutoModeSelector.h"
#include "RAWCConstants.h"


// Uncomment this to make the camera work
#define USE_CAMERA

DriverStationLCD *m_dsLCD;

class RAWCBase : public IterativeRobot
{
	DriverStation *m_ds;
	RAWCRobot *bot;
	OperatorController * opController;
	AutoModeController * autoController;
	AutoModeSelector * autoSelector;
	int autoIndex;
	RAWCConstants * constants;
	
public:
	RAWCBase(void)	{
		GetWatchdog().SetEnabled(false);
	
		m_dsLCD = DriverStationLCD::GetInstance();
		
		bot = RAWCRobot::getInstance();	
		opController = new OperatorController();
		autoController = AutoModeController::getInstance();
		autoSelector = new AutoModeSelector();
		autoSelector->increment();
		
		constants = RAWCConstants::getInstance();
		constants->restoreData();		
	}
	void RobotInit(void) {	
	}
	void DisabledInit(void) {
		RAWCLib::PrintToLCD::print(true, 1, 0, "968 2012");
		RAWCLib::PrintToLCD::finalizeUpdate();
		
		constants->restoreData();
		autoIndex = 1;
	}
	void AutonomousInit(void) {
		// Commit the selected auto mode to the controller
		//printf("In auto init\r\n");
		constants->restoreData();
		autoController->reset();
		autoSelector->writeToAutoModeController(autoController);
		RAWCRobot::getInstance()->getLeftEncoder()->Reset();
		
		/*{		bot->setShooter(1);
				bot->setIntakeD(1);
				bot->handle();
				Wait(.5);
				bot->setConveyer(.5);
				bot->setCblock(1);
				bot->handle();
				Wait(3);
				bot->setShooter(0);
				bot->setConveyer(0);
				bot->setCblock(0);
				bot->driveLeftRight(-.5,-.5);
				bot->handle();
				Wait(1.25);
				bot->driveLeftRight(0,0);
				//bot->setBBQ(1); 		
				bot->handle();
				Wait(.5);
				//bot->setBBQ(0);
				bot->driveLeftRight(0,.4);
				bot->setRoller(1);
				bot->setConveyer(.5);
				bot->handle();
				Wait(.45);
				bot->driveLeftRight(0,0);
				bot->handle();
				Wait(.2);
				bot->driveLeftRight(.4,.35);
				bot->handle();
				Wait(2);
				bot->driveLeftRight(0,0);
				bot->handle();
				Wait(.5);
				bot->driveLeftRight(.6,.2);
				//bot->setBBQ(-1);
				bot->setShooter(1);
				bot->handle();	
				Wait(1);
				//bot->setBBQ(0);
				bot->handle();
				Wait(.25);
				bot->driveLeftRight(0,0);
				bot->handle();
				Wait(.1);
				bot->setCblock(1);
				bot->handle();
				Wait(3);
				bot->setCblock(0);
				bot->setConveyer(0);
				bot->setShooter(0);
				bot->handle();
				return;*/
				/*Wait(.1);
				delete bot;
				bot->handle();
				}*/
		
	}
	void TeleopInit(void) 
	{
	}
	void DisabledContinuous(void) 
	{
		Wait(0.01);
	}
	void AutonomousContinuous(void)	
	{
		Wait(0.01);
	}
	void TeleopContinuous(void) {
		Wait(0.01);
	}
	void DisabledPeriodic(void)  
	{
		autoController->reset();	
		if( opController->cb->getButtonAutoSelect())
		{
			autoSelector->increment();
		}
		//Print it
		PrintToLCD::print(true, 1, 1, "Auto Mode: ");
		PrintToLCD::print(true, 2, 1, autoSelector->description().c_str());
		PrintToLCD::finalizeUpdate();
	}
	void AutonomousPeriodic(void) {
		autoController->handle();
				bot->handle();
				
		/*{bot->setShooter(1);
		bot->setIntakeD(1);
		bot->handle();
		Wait(.5);
		bot->setConveyer(.5);
		bot->setCblock(1);
		bot->handle();
		Wait(3);
		bot->setShooter(0);
		bot->setConveyer(0);
		bot->setCblock(0);
		bot->driveLeftRight(-.5,-.5);
		bot->handle();
		Wait(.75);
		bot->driveLeftRight(0,0);
		bot->setBBQ(1); 		
		bot->handle();
		Wait(.5);
		bot->setBBQ(0);
		bot->driveLeftRight(0,.4);
		bot->setRoller(1);
		bot->setConveyer(.5);
		bot->handle();
		Wait(.25);
		bot->driveLeftRight(0,0);
		bot->handle();
		Wait(.2);
		bot->driveLeftRight(.5,.4);
		bot->handle();
		Wait(.75);
		bot->driveLeftRight(0,0);
		bot->handle();
		Wait(.5);
		bot->driveLeftRight(.3,0);
		bot->setBBQ(-1);
		bot->setShooter(1);
		bot->handle();	
		Wait(.2);
		bot->setBBQ(0);
		bot->handle();
		Wait(.25);
		bot->driveLeftRight(0,0);
		bot->handle();
		Wait(.1);
		bot->setCblock(1);
		bot->handle();
		Wait(.1);
		bot->handle();
		}
		*/
		/*bot->setShooter(-1);
		bot->handle();
		Wait(3);	
		bot->setConveyer(1);
		bot->setCblock(1);
		bot->handle();
		Wait(4); 
		bot->setShooter(0);
		bot->setConveyer(0);
		bot->handle();
		Wait(.5);-
		bot->driveLeftRight(1,1);
		bot->handle();
		Wait(1.5);
		bot->setBBQ(.5);
		bot->handle();
		Wait(2);
		bot->driveLeftRight(0,0);
		bot->handle();		
		Wait(1);
		bot->setBBQ(0);
		bot->handle();
		bot->setConveyer(1);
		bot->handle();
		Wait(4);
		bot->setBBQ(.5);
		bot->setConveyer(0);
		bot->handle();
		*/
		//bot->handle();
		//sendIOPortData();
	}
		//sendIOPortData();

	void TeleopPeriodic(void) {
		opController->handle();
		bot->handle();
		
		//sendIOPortData();
	}
	
	
};

START_ROBOT_CLASS(RAWCBase);
