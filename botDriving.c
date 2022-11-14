/*
FUNCTIONS STILL NEEDED:
Dispenser stuff
Test mode stuff

ALSO MAKE SURE TO SWITCH ALL SENSOR PORTS TO MATCH OUR ROBOT
*/



// function to configure all sensors
void configureAllSensors () 
{
	SensorType[S1] = sensorEV3_Touch; 
	wait1MSec(50); 
	SensorType[S2] = sensorEV3_Ultrasonic; 
	wait1MSec(50);
	SensorType[S3] = sensorEV3_Color; 
	wait1MSec(50);
	SensorType[S4] = sensorEV3_Gyro; 
	wait1MSec(50);
	SensorMode[S3] = modeEV3Color_Color; 
	wait1MSec(50);
	SensorMode[S4] = modeEV3Gyro_Calibration; 
	wait1MSec(50); 
	SensorMode[S4] = modeEV3Gyro_RateAndAngle; 
	wait1MSec(50);
	return;
}

// drive function
void drivePower(int motorPower) {
	motor[motorA]=motor[motorD]=motorPower;
	return;
}

// drive a certain distance in cm function
void driveDist(float distCM, int motorPow) {
	const int encoderLimit=distCM*180/(PI*2.75);
	nMotorEncoder[motorB]=0;
	motor[motorB]=motor[motorC]=motorPow;
	while (nMotorEncoder[motorB]<encoderLimit)
	{ }
	motor[motorB]=motor[motorC]=0;
}

// stop driving function
void driveStop() {
	motor[motorA]=motor[motorD]=0;
	return;
}

// turn clockwise function
void turnCW(int angle, int motorPower) {
	resetGyro(S1);
motor[motorA] = -motorPower;
motor[motorD] = motorPower;
while(SensorValue[S1] < angle)
{ }
driveStop();
wait1Msec(2000);
return;	
}

// function to choose the mode
int modeChoose() {
// input verification
	int mode=0;
	while(!(mode==1||mode==2)) 
	{
		displayString (5, "Choose your mode:");
		displayString (7, "Press LEFT button for:");
		displayString (8, "Study Mode");
		displayString (10, "Press RIGHT button for:");
		displayString (11, "Test Mode");
// study mode=1, test mode=2
		if (getButtonPress(LEFT_BUTTON)) 
			{
			mode=1;
			}

		if (getButtonPress(RIGHT_BUTTON)) 
			{
			mode=2;
			}
	}
	eraseDisplay();
	return mode;
}

//resets the varables for the skittle menu
void reset_char(string & var1, string & var2, string & var3, string & var4, string & var5)
{
	var1 = ">";
	var2 = " ";
	var3 = " ";
	var4 = " ";
	var5 = " ";
}
//changes the selected menu option for skittles
void change_select(int & choice, string & Yellow_char, string & Red_char, string & Green_char,string & Purple_char,string & Orange_char)
{
	if(choice < 0)
		choice = 4;
	if(choice > 4)
		choice = 0;

	if(choice == 0)
		reset_char(Yellow_char, Red_char, Green_char, Purple_char, Orange_char);
	else if (choice == 1)
		reset_char(Red_char, Green_char, Purple_char, Orange_char, Yellow_char);
	else if (choice == 2)
		reset_char(Green_char, Purple_char, Orange_char, Yellow_char,Red_char);
  else if (choice == 3)
  	reset_char(Purple_char, Orange_char, Yellow_char,Red_char,Green_char);
	else if (choice == 4)
  	reset_char(Orange_char, Yellow_char,Red_char,Green_char,Purple_char);
} 
//menu for selecting the skittles
int skittle_select(){
	int choice = 0; 
	string Yellow_char = " ";
	string Red_char= " ";
	string Green_char = " ";
	string Purple_char = " " ;
	string Orange_char = " ";
	while(!getButtonPress(ENTER_BUTTON))
	{
		if (getButtonPress(DOWN_BUTTON))
		{
			choice++;
			while(getButtonPress(DOWN_BUTTON))
		  {}
		}
		
		if(getButtonPress(UP_BUTTON))
	  {
	  	choice--;
	  	while(getButtonPress(UP_BUTTON))
	  	{}
	  }
	  change_select(choice, Yellow_char, Red_char, Green_char, Purple_char, Orange_char);
		displayString(4,"%s Yellow Skittle", Yellow_char);
		displayString(5,"%s Red Skittle", Red_char);
		displayString(6,"%s Green Skittle", Green_char);
		displayString(7,"%s Purple Skittle", Purple_char);
		displayString(8,"%s Orange Skittle", Orange_char);
		displayString(9,"%d",choice);
		
  }
  return choice;
		
}

void open_flap(int time_open)
{
	time1[T1] = 0;
	
}

void displence()
{
	const TIME_OPEN_FLAP_M = 2000;
	bool dispencing = true;
	while(dispencing == true)
	{
		int skittle_selected = skittle_select();
		int rotate = -1*skittle_selected*60;
		nMotorEncoder(motorA) = 0;
		motor[motorA]= -15;
		while(nMotorEncoder(motorA) >  rotate)
	  {}
		motor[motorA]=0;
		open_flap(TIME_OPEN_FLAP_M);
		motor[motorA]= 15;
		while(nMotorEncoder(motorA) <0)
	  {}
		motor[motorA]=0;
	}
}


// study mode
void studyMode (int tapeColour, int turnColour, int &lapCount) 
{
	lapCount++;
	for (int count=0; count<4; count++) 
	{
		drivePower(5);
		if (SensorValue[touchPort]==0) 
		{
			driveStop();
			dispense();
			lapCount=0;
		}
		drivePower(20);
		while(SensorValue[S1] == tapeColour && SensorValue[S1] != turnColour)
		{
			playSoundFile("fixSound.rsf");
		}
		driveStop();
		wait1Msec(1000);
		driveStop(); 
		turnCW(90,5);
		nMotorEncoder[motorA] = 0; 
		drivePower(5); 
		while(nMotorEncoder[motorA] < CORNER_DIST_CORRECTION)
		{
		}
		driveStop();
	}
	return;
}

void fireBullet() 
{

}

float timer() 
{
	displayString (5,"Press up to begin the timer");
	displayString (7,"Press up again to stop it");
	while(!getButtonPress(UP_BUTTON)) 
	{
	}
    while(getButtonPress(UP_BUTTON)) 
	{
	}
	time1[T1]=0;
	while(!getButtonPress(UP_BUTTON)) 
	{
	}
    while(getButtonPress(UP_BUTTON)) 
	{
	}
	eraseDisplay();
	displayString (5, "Your time is %f minutes", time1[T1]/1000.0/60);
	wait1Msec(5000);
}

// test mode function
void testMode() 
{ 
// timer
timer();

// file for answers
	TFileHandle fileIn;
	bool fileOkay = openReadPC(fileIn, “answers.txt”);
	if (!fileOkay) 
	{
		displayString(5,”Error!”);
		wait1Msec(5000);
	}
	else 
	{
		int questionNum=0;
		int score = 0;
		readCharPC (fileIn,questionNum);
		// putting answers into an array
		char answers[questionNum]={};
		int j=0
		while (readCharPC (fileIn,answer[j]))
		{
			j++
		}
		//drive and scan
		driveStop();
		float grade=float(score)/questionNum;
		displayString (5, “You scored %d/%d, score, questionNum);
			displayString( (6, “%f”, grade)
			if (grade<60) 
			{
				fireBullet(); // need to create this function
			}
	}
return;
}


// main function .....
#include “PC_FileIO.c”

task main ()
{
	configureAllSensors();

	int done=1;

	while (done!=0) 
	{
		bool modeInterface=true;
		while (modeInterface==true) 
		{
			int mode = modeChoose();
			modeInterface=false;
		}

		while (mode==1) {
			// something is defo wrong its not making sense in my head
			int lapCount=0;
			studyMode(int(colorRed), lapCount);
			if (lapCount>2) {
				done=0;
			}
		}

		while (mode==2) 
		{
			testMode();
			time1[T2]=0;
			if ((time1[T2]/1000.)>120) 
			{
				done=0;
			}
			
		}

		// press enter button to go back to the menu this defo doesnt work like i want it so that at any point if u ress it it goes back to the 
		// main menu!  wowza gfbaiybfia
		if (getButtonPress==ENTER_BUTTON) 
		{
			modeInterface=true;
		}
	}
	return;
}
