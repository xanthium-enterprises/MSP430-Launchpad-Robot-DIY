	
    //----------------------------------------------------------------------------//
	//              Program to move the robot in a pattern                        //      
	//----------------------------------------------------------------------------//
	//                       Stop                                                 //
    //                        ^                                                   //
    //                        |                                                   //
	//                        |                                                   //
	//        +----->---->----+                                                   //
    //        |                                                                   //
    //        ^                                                                   //
    //        |                                                                   //
    //      Start                                                                 //
    //      +---+                                                                 //
    //   []-|   |-[]                                                              //
    //      +---+                                                                 //
	//----------------------------------------------------------------------------//
	// www.xanthium.in                                                            //
    // (c) Rahul.S 2015                                                           //
	//----------------------------------------------------------------------------//
	// More info can be found here                                                //
	// http://www.xanthium.in/programming-msp430-launchpad-robot                  //
	//----------------------------------------------------------------------------//
	
	#include "msp430g2553.h"
	#include "motor.h"
	void main()
	{
		WDTCTL = WDTPW + WDTHOLD; //Stop the WDT 
  
  		Delay(20);
  		BotLocomotion(FORWARD);   // start the robot in forward 
  		Delay(20);                // Keep moving for some time 
		BotLocomotion(RIGHT_TURN);// turn the robot to right 
		Delay(17);                // Keep moving for some time 
		BotLocomotion(FORWARD);   // start the robot in forward
  		Delay(20);				  // Keep moving for some time 
		BotLocomotion(LEFT_TURN); // turn the robot to left
		Delay(17);                // Keep moving for some time 
		BotLocomotion(FORWARD);   // start the robot in forward 
  		Delay(20);				  // Keep moving for some time 
		BotLocomotion(STOP);      // Stop the Robot 
		
	}
