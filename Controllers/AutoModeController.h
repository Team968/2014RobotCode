#ifndef _AUTO_CONTROLLER_H
#define _AUTO_CONTROLLER_H
#include "../RAWCRobot.h"
#include "../RAWCLib.h"

using namespace RAWCLib;


// What type of argument?
typedef float cmdArg;

typedef enum RobotCommandNames_e
{
	CMD_NULL = 0,
	CMD_DRIVE,
	CMD_DRIVE_DIST,
	//CMD_RELEASE_TUBE,
	//CMD_INTAKE_TUBE,
	//CMD_TELESCOPE,
	CMD_WAIT,
	CMD_TURN,
	CMD_RELEASE,
	CMD_SHOOT,
	CMD_SHOOT2,
	CMD_SETUP,
	//CMD_INTAKE,
	//CMD_DOWN,
	//CMD_UP
}RobotCommandNames_e;

typedef struct RobotCommand{
	RobotCommandNames_e cmd;
	cmdArg encoderCount;
	cmdArg heading;
	cmdArg armPos;
	cmdArg roller;
	cmdArg timeout;
}RobotCommand;

// A dead command for use later
const RobotCommand cmdNULL =
{
	CMD_NULL,
	0,
	0,
	0
};

class AutoModeController
{
private:
	
	static AutoModeController *singletonInstance;
	
	Timer * timer;
	RAWCRobot *bot;
	deque<RobotCommand> cmdList;
	RobotCommand curCmd;
	
	bool extendArm;
	
	float previousError;
	
	// do nothing
	void doNothing();
	void Drive();
	void doShoot();
	void doRelease();
	void doShoot2();
	void doSetUp();
	void doIntake();
	void downBBQ();
	void upBBQ();
	bool driveDistanceWithHeading(cmdArg distance, cmdArg heading);
	bool driveDistancePWithHeading(cmdArg distance, cmdArg heading);
	bool turnHeading(cmdArg heading);
	
	
	bool m_WinchFire;
	
	
	
public:
	AutoModeController();
	static AutoModeController* getInstance();
	void addCommand(RobotCommandNames_e cmd, cmdArg arg1, cmdArg arg2, cmdArg arg3, cmdArg arg4);

	bool handle();
	void reset();
	
};


#endif

