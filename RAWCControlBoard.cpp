//=============================================================================
// File: RAWCControlBoard.cpp
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
// the software.
//
// This notice shall supercede any other notices contained within the software.
//=============================================================================
#include "RAWCControlBoard.h"
#include "WPILib.h"
#include "RAWCRobot.h"

// Initialize the Singleton instance
RAWCControlBoard* RAWCControlBoard::singletonInstance = NULL;

/// Creates (if needed) and returns a singleton Control Board instance
RAWCControlBoard* RAWCControlBoard::getInstance()
{
	if( singletonInstance == NULL)
		singletonInstance = new RAWCControlBoard(); 
	return singletonInstance;
}

/// Constructor for RAWC Control Board
RAWCControlBoard::RAWCControlBoard()
{
	ds = & DriverStation::GetInstance()->GetEnhancedIO();
	driveStick = new Joystick(1);
	steeringWheel = new Joystick(2);
	operatorPanel = new Joystick(3);
}

/// Returns state of shifter switch
bool RAWCControlBoard::getButtonShifter()
{
	return getDriveButton(SHIFTER_BUTTON);
}

/// Returns the state of the quick turn
bool RAWCControlBoard::getQuickTurn()
{
	return !getDriveButton(8);
}

float RAWCControlBoard::getDriveStickY()
{
	return driveStick->GetRawAxis(LEFT_GAMEPAD_Y);
}

float RAWCControlBoard::getSteeringX()
{
	return steeringWheel->GetRawAxis(STEERING_X);
}

float RAWCControlBoard::getOperatorY()
{
	return operatorPanel->GetRawAxis(LEFT_GAMEPAD_Y);
}
float RAWCControlBoard::getOperatorX(){
	return operatorPanel->GetRawAxis(LEFT_GAMEPAD_X);
}

float RAWCControlBoard::getGamepadLeftY()
{
	return operatorPanel->GetRawAxis(LEFT_GAMEPAD_Y);
}

float RAWCControlBoard::getGamepadRightY()
{
	return operatorPanel->GetRawAxis(RIGHT_GAMEPAD_Y);
}

float RAWCControlBoard::getOperatorDpadX()
{
	return operatorPanel->GetRawAxis(5);
}

float RAWCControlBoard::getOperatorDpadY()
{
	return operatorPanel->GetRawAxis(6);
}
float RAWCControlBoard::getDriveDpadY()
{
	return operatorPanel->GetRawAxis(6);
}
bool RAWCControlBoard::getDriveButton(const int button)
{
	return driveStick->GetRawButton(button);
}

bool RAWCControlBoard::getOperatorButton(const int button)
{
	return operatorPanel->GetRawButton(button);
}

bool RAWCControlBoard::getSteeringButton(const int button)
{
	return steeringWheel->GetRawButton(button);
}
bool RAWCControlBoard::getButtonAutoSelect()
{
	// This will latch on a press and only return true once per press
	// Active Low signal
	//if(getDriveButton(AUTON_BUTTON))
	if(getSteeringButton(7))
	{
		if(!autoLatch)
		{
			autoLatch = true;
			return true;
		}
	}
	else
		autoLatch = false;
	return false;
}

