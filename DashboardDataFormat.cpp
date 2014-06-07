/* File Name: DashboardDataFormat.cpp
 * Function: code for sending data to the dashboard during competition
 * 
 * Author: unknown
 *  
 * SVN Repository: windriver examples
 */
#include "DashboardDataFormat.h"
#include "RAWCRobot.h"

#include "RAWCConstants.h"

void sendVisionData() {
	Dashboard &dash = DriverStation::GetInstance()->GetHighPriorityDashboardPacker();
	dash.AddCluster(); // wire (2 elements)
	{
		dash.AddCluster(); // tracking data
		{
			dash.AddDouble(1.0); // Joystick X
			dash.AddDouble(135.0); // angle
			dash.AddDouble(3.0); // angular rate
			dash.AddDouble(5.0); // other X
		}
		dash.FinalizeCluster();
		dash.AddCluster(); // target Info (2 elements)
		{
			dash.AddCluster(); // targets
			{
				dash.AddDouble(100.0); // target score
				dash.AddCluster(); // Circle Description (5 elements)
				{
					dash.AddCluster(); // Position (2 elements)
					{
						dash.AddDouble(30.0); // X
						dash.AddDouble(50.0); // Y
					}
					dash.FinalizeCluster();
				}
				dash.FinalizeCluster(); // Position
				dash.AddDouble(45.0); // Angle
				dash.AddDouble(21.0); // Major Radius
				dash.AddDouble(15.0); // Minor Radius
				dash.AddDouble(324.0); // Raw score
			}
			dash.FinalizeCluster(); // targets
		}
		dash.FinalizeCluster(); // target Info
	}
	dash.FinalizeCluster(); // wire
	
	dash.Finalize();
}

void sendIOPortData() {
	Dashboard &dash = DriverStation::GetInstance()->GetLowPriorityDashboardPacker();
	
	
	dash.AddCluster();
	{
		//dash.AddFloat(RAWCRobot::getInstance()->getGyro->GetAngle());
		
		//dash.AddFloat(RAWCRobot::getInstance()->getLeftEncoder()->Get());
		dash.AddFloat(RAWCConstants::getInstance()->getValueForKey("SensitivityHigh"));
		dash.AddFloat(RAWCConstants::getInstance()->getValueForKey("SensitivityLow"));	
	}
	dash.FinalizeCluster();
	dash.Finalize();
}