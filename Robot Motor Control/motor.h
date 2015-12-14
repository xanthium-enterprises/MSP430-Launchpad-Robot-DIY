	//----------------------------------------------------------------------------//
	// Function definitions for motor.c                                           //
	//----------------------------------------------------------------------------//
	// www.xanthium.in                                                            //
    // (c) Rahul.S 2015                                                           //
	//----------------------------------------------------------------------------//

	#define OFF 	   0x00
	#define ON  	   0x01
	#define REVERSE    0x02
	#define FORWARD    0x03
	#define STOP       0x04
	#define RIGHT_TURN 0x05
	#define LEFT_TURN  0x06
	
	//----------------------------------------------------------------------------//
	//                                                                            //
	// RightMotor(ON)     - Switch on the Right Motor                             //
	// RightMotor(OFF)    - Stop the Right Motor                                  //
	// RightMotor(REVERSE)- Reverse the direction of rotation of the Right Motor  //
	//                                                                            //
	// LeftMotor(ON),LeftMotor(OFF),LeftMotor(REVERSE)- Similar to Right Motor()  //
	//                                                                            //
	// BotLocomotion(FORWARD)   - Move the Robot Forward(both motors ON)          //
	// BotLocomotion(REVERSE)   - Move the Robot Backward(Both Motors Reverse)    //
	// BotLocomotion(STOP)      - Stop the Robot (Both Motors OFF)                //
	// BotLocomotion(RIGHT_TURN)- Turn the Robot to Right                         //
	// BotLocomotion(LEFT_TURN) - Turn the Robot to Left                          //
	//                                                                            //
	//----------------------------------------------------------------------------//

	void RightMotor(char status);
	void LeftMotor(char status);
	
	void BotLocomotion(char status);
	
	void Delay(int time);
	