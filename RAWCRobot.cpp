//=============================================================================
// File: RAWCRobot.cpp
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
#include "RAWCRobot.h"
#include <math.h>
#include "RAWCConstants.h"
RAWCRobot* RAWCRobot::singletonInstance = NULL;
#include "CounterBase.h"
#include "RAWCLib.h"

#define DRIVECODELCDDEBUGER 1

using namespace RAWCLib;

/// Creates (if needed) and returns a singleton instance of the RAWCRobot
RAWCRobot * RAWCRobot::getInstance() {
	// If we have not created a robot yet, do so.
	// If we have created a robot, skip this
	if (singletonInstance == NULL) {
		singletonInstance = new RAWCRobot();
	}
	return singletonInstance;
}

/// Constructor for RAWCRobot
RAWCRobot::RAWCRobot() {
	// Set up drive motors
	rightDriveA = new Victor(RIGHT_DRIVE_PWM_A);
	rightDriveB = new Victor(RIGHT_DRIVE_PWM_B);
	//rightDriveC = new Victor(RIGHT_DRIVE_PWM_C);
	leftDriveA = new Victor(LEFT_DRIVE_PWM_A);
	leftDriveB = new Victor(LEFT_DRIVE_PWM_B);
	//leftDriveC = new Victor(LEFT_DRIVE_PWM_C);

	IntakeA = new Victor(INTAKE_A);
	IntakeB = new Victor(INTAKE_B);
	WinchA = new Victor(WINCH_A);
	WinchB = new Victor(WINCH_B);

	//Solenoids
	//shifterA = new Solenoid(SHIFTER_SOLENOID_CHAN);
	//shifterB = new Solenoid(SHIFTER_REVERSE);
	IntakeArm = new Solenoid(INTAKE_ARM);
	WinchF = new Solenoid(WINCH_FIX);
	BunnyE = new Solenoid(BUNNY_EARS);
	Stop = new Solenoid(STOP);
	New = new Solenoid(NEW_PISTON);
	Shifter = new Solenoid(SHIFTER);
	ShifterReverse = new Solenoid(SHIFTER_REVERSE);
	
	compressorSignal = new DigitalInput(COMPRESSOR_SWITCH);
	compressorRelay = new Relay(COMPRESSOR_RELAY, Relay::kForwardOnly);
	//Compressor *compressor = new Compressor(COMPRESSOR_SWITCH, COMPRESSOR_RELAY);
	//compressor->Start();

	//SWITCHES
	LimitA = new DigitalInput(LSWITCH_A);
	/*LimitB = new DigitalInput(LSWITCH_B);
	LimitC = new DigitalInput(LSWITCH_C);
	LimitD = new DigitalInput(LSWITCH_D);
	LimitE = new DigitalInput(LSWITCH_E);*/
	
	//TODO

	leftDriveEncoder = new Encoder(LEFT_ENCODER_A_CHAN, LEFT_ENCODER_B_CHAN,
			true, CounterBase::k1X);
	//leftDriveEncoder->SetDistancePerPulse(0.1007081038552321);
	leftDriveEncoder->SetDistancePerPulse(0.000092259209410);
	cout << "velocity" << velocity;
	//printf("velocity = %f %f\n", velocity);
	leftDriveEncoder->Start();
	leftDriveEncoder->Reset();
	

	/*ShooterEncoder = new Encoder(SHOOTER_ENCODER_A, SHOOTER_ENCODER_B,
				true, CounterBase::k1X);
	ShooterEncoder->SetDistancePerPulse(0.1007081038552321);
	//printf("velocity = %f %f\n", velocity);
	ShooterEncoder->Start();
	ShooterEncoder->Reset();*/
		
	velTimer = new Timer();
	velTimer->Start();
	velocity = 0;
	previous_encoder = 0;

	shifterCounts = 0;
	currentShiftState = SHIFTER_STATE_HIGH;

	wantedUpperStage = 0;
	wantedLowerStage = 0;

	wantedLeftDrive = 0;
	wantedRightDrive = 0;

	wantedIntake = 0;
	wantedWinch = 0;


	//wantedBBQ = 0;


	//TODO
	//wantedBBQPosition = 2;
	//wantedBBQSpeed = 0;

	reset = false;

	// Initially, we are in drive mode
	setMode(DRIVE_MODE);
}

/// Used to handle the recurring logic funtions inside the robot.
/// Please call this once per update cycle.
void RAWCRobot::handle() {
	printCount++;

	// Default drive
	float tmpLeftMotor = wantedLeftDrive;
	float tmpRightMotor = wantedRightDrive;

	ShifterPositions tmpShiftPos = wantedShifterPosition;
	shift(tmpShiftPos);

	setLeftMotors(tmpLeftMotor);
	setRightMotors(tmpRightMotor);

	/*this->conveyer->Set(this->wantedConveyer);
	this->shooterA->Set(this->wantedShooterP);
	this->shooterB->Set(this->wantedShooterE);
	this->Cblock->Set(this->wantedCblock);
	this->Roller->Set(this->wantedRoller);
	this->IntakeD->Set(this->wantedIntakeD);
	this->Lift->Set(this->wantedLift);
	this->BBQ->Set(this->wantedBBQ);
	this->BUTTOn->Set(this->wantedBUTTON);*/
	this->IntakeA->Set(this->wantedIntake);
	this->IntakeB->Set(this->wantedIntake);
	this->WinchA->Set(this->wantedWinch);
	this->WinchB->Set(this->wantedWinch);
	this->IntakeArm->Set(this->wantedIntakeArm);
	this->WinchF->Set(this->wantedWinchF);
	this->BunnyE->Set(this->wantedBunnyE);
	this->Stop->Set(this->wantedStop);
	this->New->Set(this->wantedNew);
	
	// first off, take care of this stuff
	compressorHandle();
	smartDashboardHandle();
	//TODO make this do PID stuff for drive      
	velocity = (this->leftDriveEncoder->GetRaw() - previous_encoder);
	if (velocity < 0)
		velocity = -velocity;

	velocity /= this->velTimer->Get();
	velocity /= 1000;
	this->velTimer->Reset();
	previous_encoder = this->leftDriveEncoder->GetRaw();

	/*if (printCount % 10 == 0) {
		//printf("Vel: %d, Gyro: %f\r\n", this->leftDriveEncoder->GetRaw(), gyro->GetAngle());
		//printf("Vel: %d", this->rightDriveEncoder->GetRaw());
	};
	if (printCount % 10 == 0) {
		//printf("RAWCRobot: %f, Wanted: %f, Stick: %f", sensorPos, wantedBBQSpeed, wantedBBQPosition);

		//printf("\n");
	}*/
	/*velocityB = (this->ShooterEncoder->GetRaw());
		if (velocityB > 0)
			velocityB = -velocityB;

		velocityB /= this->velTimer->Get();
		velocityB /= 1000;
		this->velTimer->Reset();

		if (printCount % 10 == 0) {
			//printf("Vel: %d, Gyro: %f\r\n", this->leftDriveEncoder->GetRaw(), gyro->GetAngle());
			printf("VelB: %d", this->ShooterEncoder->GetRaw());
		};
		if (printCount % 10 == 0) {
			//printf("RAWCRobot: %f, Wanted: %f, Stick: %f", sensorPos, wantedBBQSpeed, wantedBBQPosition);

			//printf("\n");
		}
*/
	//TODO
	/*if (LimitA->Get() == 1)
	{
		setBBQ(0);
	}*/
	/*if (LimitB->Get() == 1)
	{
		setIntakeD(0);
	}*/
}
//TODO
/*void RAWCRobot::SetSpeed(float speed)
 {
 this->wantedBBQSpeed = speed;
 }
 void RAWCRobot::SetPosition(const float pos)
 {
 this->wantedBBQPosition = pos;
 }*/

/// Allows skid steer robot to be driven using tank drive style inputs
/// @param leftDriveValue
/// @param rightDriveValue
///
void RAWCRobot::driveLeftRight(float leftDriveValue, float rightDriveValue) {
	wantedLeftDrive = leftDriveValue;
	wantedRightDrive = rightDriveValue;
}
void RAWCRobot::setIntake(float value){
	wantedIntake = value *.9;
}
void RAWCRobot::setWinch(float value){
	wantedWinch = value *.75;

}
void RAWCRobot::setIntakeArm(bool value){
	wantedIntakeArm = value;

}
void RAWCRobot::setWinchF(bool value){
	wantedWinchF = value;
}
void RAWCRobot::setBunnyE(bool value){
	wantedBunnyE = value;
}
void RAWCRobot::setSTOP(bool value){
	wantedStop = value;
}
void RAWCRobot::setNew(bool value){
	wantedNew = value;
}
void RAWCRobot::setShifter(bool value){
	wantedShifter = value;
}
void RAWCRobot::setShifterReverse(bool value){
	wantedShifterReverse = value;
}
/*void RAWCRobot::setShooter(float speed) {
	this->wantedShooterP = speed;
	this->wantedShooterE = speed;
}

void RAWCRobot::setConveyer(float value) {
	this->wantedConveyer = value *5;
}

void RAWCRobot::setCblock(bool value) {
	this->wantedCblock = value;
}
void RAWCRobot::setRoller(float value) {
	this->wantedRoller = value;
}

void RAWCRobot::setIntakeD(bool value){
	this->wantedIntakeD = value;
}

void RAWCRobot::setLift(bool value) {
	this->wantedLift = value;
}
void RAWCRobot::setBBQ(float value) {
	this->wantedBBQ = value;
}
*/
/*BBQ * RAWCRobot::getBBQ()
 {
 return bbq;
 }*/
//TODO
/*Encoder * RAWCRobot::getBBQEncoder()
 {
 return BBQEncoder;
 }*/
void RAWCRobot::driveSpeedTurn(float speed, float turn, bool quickTurn) {
	//Linear degredation of steeering based off of velocity
	//velocity *= 0.003;
	float temp_vel = speed;
	float sensitivity = 0;
	float unscaled_turn = 0;

	if (temp_vel < 0)
		temp_vel = -temp_vel;

	//printf("Velocity: %f, stick: %f\r\n", velocity, temp_vel);
	if (turn > 0.01 && turn < -0.01 || (speed == 0 && !quickTurn))
		turn = 0;

	unscaled_turn = turn;
	//turn = turn * (temp_vel - 0.75);


	if (quickTurn)
		sensitivity = 2;
	/*else if (turn > .75 or turn < -.75)
		sensitivity = .4;*/
	else
		sensitivity = .3;

	turn *= sensitivity;
	//TODO: change turn to positive if wrong turning
	turn = turn;
	//TODO: 
	speed = -speed;
	//change if wrong direction
	//turn = steeringAngle;

	float left_power = LimitMix(speed + turn);
	float right_power = LimitMix(speed - turn);

	float right_power_real = VictorLinearize(right_power);
	float left_power_real = VictorLinearize(left_power);

	driveLeftRight(left_power_real, right_power_real);
}

/// Allows robot to spin in place
/// @param turnRate
///
void RAWCRobot::quickTurn(float turnRate) {
	//when provided with + turn, quick turn right

	float left = -1 * turnRate;
	float right = turnRate;

	driveLeftRight(left, right);
}

// Handles the autmatic turn on/off of the compressor
void RAWCRobot::compressorHandle() {
	if (!compressorSignal->Get()){
			compressorRelay->Set(Relay::kOn);
	}
	else{
		compressorRelay->Set(Relay::kOff);
	}
	
}

void RAWCRobot::smartDashboardHandle(){
	SmartDashboard::PutBoolean("Compressor Switch: ", compressorSignal->Get());
	SmartDashboard::PutNumber("Encoder Value: ", leftDriveEncoder->Get());
	SmartDashboard::PutNumber("Encoder Rate: ", leftDriveEncoder->GetRate());
	SmartDashboard::PutNumber("Encoder Distance: ", leftDriveEncoder->GetDistance());
}

Encoder * RAWCRobot::getLeftEncoder() {
	return leftDriveEncoder;
}
/*Encoder * RAWCRobot::getShooterEncoder()
{
	return ShooterEncoder;
}*/
/* * RAWCRobot::getLeft()
 {
 return leftDrive;
 }*/
/// Shifts drive gears. 
/// @param shifterPosition
void RAWCRobot::shift(ShifterPositions shifterPosition) {
	bool solA = false, solB = false;
	ShifterStates nextShiftState = currentShiftState;
	// It takes lots of logic to shift this year
	switch (currentShiftState) {
	case SHIFTER_STATE_HIGH:
		solA = false;
		solB = false;
		shifterCounts = 0;
		if (shifterPosition == SHIFTER_POS_LOW)
			nextShiftState = SHIFTER_STATE_LOW;
		break;

	case SHIFTER_STATE_LOW:
		solA = true;
		shifterCounts = 0;
		if (shifterPosition == SHIFTER_POS_HIGH)
			nextShiftState = SHIFTER_STATE_HIGH;
		break;
	default:
		nextShiftState = SHIFTER_STATE_HIGH;
		break;
	}

	//shifterA->Set(solA);

	/*if (currentShiftState != nextShiftState) {
		leftDriveA->Set(0);
		leftDriveB->Set(0);
		//leftDriveC->Set(0);
		rightDriveA->Set(0);
		rightDriveB->Set(0);
		//rightDriveC->Set(0);
		Wait(0.125);
	}*/

	//currentShiftState = nextShiftState;
}

//void RAWCRobot::askForShift(ShifterPositions shifterPosition) {
	//wantedShifterPosition = shifterPosition;
//}

/// Sets the robot mode
void RAWCRobot::setMode(RobotModes newMode) {
	mode = newMode;
}

void RAWCRobot::setLeftMotors(float val) {
	val = -.90 * val;

	if (val > 1.0)
		val = 1.00;
	if (val < -1.0)
		val = -1.0;

	leftDriveA->Set(-val);
	leftDriveB->Set(-val);
	//leftDriveC->Set(-val);
}

/// sets the left side motors
void RAWCRobot::setRightMotors(float val) {
	val = .90 * val;
	
	if (val > 1.0)
		val = 1.00;
	if (val < -1.0)
		val = -1.0;

	rightDriveA->Set(-val);
	rightDriveB->Set(-val);
	//rightDriveC->Set(-val);
}

//bool RAWCRobot::inHighGear() {
	//return (currentShiftState == SHIFTER_STATE_HIGH);
//}


