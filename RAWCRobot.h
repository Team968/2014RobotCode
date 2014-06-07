#ifndef _RAWC_ROBOT_H
#define _RAWC_ROBOT_H
//=============================================================================
// File: RAWCRobot.h
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
#include "RAWCLib.h"


/// This class provides core robot functionality and encapsulates 
/// motors, sensors, relays, etc.
///
class RAWCRobot{
	public: 
	static RAWCRobot * singletonInstance;
	
	enum ShifterPositions{
		SHIFTER_POS_LOW = 0,
		SHIFTER_POS_HIGH
	};
	
	enum RobotModes{
		DRIVE_MODE
	};
	
	enum ShifterStates{
		SHIFTER_STATE_HIGH,
		SHIFTER_STATE_LOW
	};
	
	static RAWCRobot* getInstance();
	
	void driveSpeedTurn(float speed, float turn, bool quickTurn);
	void driveLeftRight(float leftDriveValue, float rightDriveValue);
	void quickTurn(float turn);
	void compressorHandle();
	void smartDashboardHandle();
	void Kill();

		
	void handle();

	void askForShift(ShifterPositions shifterPosition);
	
	bool inHighGear();
	

	/*void setShooter(float value);
	void setConveyer(float value);
	void setCblock(bool value);
	void setRoller(float value);
	
	void setIntakeD(bool value);
	void setLift(bool value);
	void setBBQ(float value);
	
	void setBUTTON(float value);*/
	void setIntake(float value);
	void setWinch(float value);
	void setIntakeArm(bool value);
	void setWinchF(bool value);
	void setBunnyE(bool value);
	void setSTOP(bool value);
	void setNew(bool value);
	void setShifter(bool value);
	void setShifterReverse(bool value);
	
//TODO
	Encoder * getLeftEncoder();
//	Encoder * getShooterEncoder();
	Timer* velTimer;
//Limit Switches
	DigitalInput *LimitA;
	/*DigitalInput *LimitB;
	DigitalInput *LimitC;
	DigitalInput *LimitD;
	DigitalInput *LimitE;
	DigitalInput *LimitF;*/
	/*
	void SetPosition(const float pos);
	void SetSpeed(float speed);
	RAWCRobot(int BBQChan, int pwm);
	*/
	//float position;


private:	
	float velocity;
	//float velocityB;
	double previous_encoder;
	//AnalogChannel * BBQPot;
	
	
	void shift(ShifterPositions shifterPosition);
	void setMode(RobotModes newMode);
	
	// Drive Motors
	Victor *rightDriveA;
	Victor *rightDriveB;
	//Victor *rightDriveC;
	Victor *leftDriveA;
	Victor *leftDriveB;
	//Victor *leftDriveC;
	Victor *WinchA;
	Victor *WinchB;
	Victor *IntakeA;
	Victor *IntakeB;
	
	
	// Drive shifting pistons
	//Solenoid *shifterA;
	Solenoid *IntakeArm;
	Solenoid *WinchF;
	Solenoid *BunnyE;
	Solenoid *Stop;
	Solenoid *New;
	Solenoid *Shifter;
	Solenoid *ShifterReverse;
	//Solenoid *shifterB;
	
	// Compressor
	DigitalInput *compressorSignal;
	//DigitalInput *killSignal;

//TODO
	Encoder *leftDriveEncoder;
	//Encoder *ShooterEncoder;
	Relay *compressorRelay;
	//Relay *killRelay;
	AxisCamera *camera;
//	AnalogChannel * BBQPot;

	Threshold *threshold;
	RobotModes mode;
	
	
	
	ShifterPositions wantedShifterPosition;

	
	//want victors
	float wantedUpperStage;
	float wantedLowerStage;
	
	float wantedLeftDrive;
	float wantedRightDrive;
	
	float wantedWinch;
	float wantedIntake;
	


	
//TODO
	//float wantedBBQEncoder;
	//	float wantedBBQPosition;
	//float wantedBBQSpeed;
	
	//want solenoids
	/*bool wantedCblock;
	bool wantedIntakeD;
	bool wantedLift;*/
	bool wantedIntakeArm;
	bool wantedWinchF;
	bool wantedBunnyE;
	bool wantedStop;
	bool wantedNew;
	bool wantedShifter;
	bool wantedShifterReverse;
	
	int printCount;
	
	int shifterCounts;
	ShifterStates currentShiftState;
	
	
	bool reset;
	
	
	RAWCRobot();
	
	void setLeftMotors(float val);
	void setRightMotors(float val);
	
//	float wantedBBQPosition;
//	float wantedBBQSpeed;
//	AnalogChannel* BBQPosition;
//	int counter;
};
#endif
