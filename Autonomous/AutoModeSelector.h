#ifndef _AUTO_SELECTOR_H
#define _AUTO_SELECTOR_H

#include <string>
#include "../Controllers/AutoModeController.h"

using namespace std;


// Note:
// This all sucks.
// I want to change it

class AutoModeSelector
{
	
public:
	enum AutoModes{
		amFirst = 0,
		amShoot1,
		amShoot2,
		amDrive,
		/*amLeft1,
		amLeft2,
		amMiddle1,
		amMiddle2,
		amMiddle3,
		amRight1,
		amRight2,*/
		amDoNothing,
		amLast
	};	
	
	void increment();
	
	// Get a description of this auto mode
	string description();
	void writeToAutoModeController(AutoModeController * ac);
	
	
private:
	int index;
	int secIndex;
};

#endif
