
	//----------------------------------------------------------------------------//
	//    Functions for controlling the Motors of the MSP430 based Robot          //
	//----------------------------------------------------------------------------//
	// Supported functions                                                        //
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
	


	#include "msp430g2553.h"
	#include "motor.h"
			
			
	//==========================================================================//
	//       Function to Switch ON,Reverse and Stop the Right Motor             //
	//==========================================================================//
	void RightMotor(char status)
	{
	    //Right Motor Control pin Direction settings
		P2DIR |=  BIT0 + BIT1 + BIT2; // P2.0,P2.1,P2.2 all output
		P2OUT &= ~BIT0 + BIT1 + BIT2; // Clear P2.0,P2.1,P2.2  
		
		//Switch() statement for deciding the direction of rotation of Motor
		switch(status)
		{
			case ON:  // Rotate the Right Motor Forward
  				      P2OUT |=  BIT1;              // P2.1 = 1,
		              P2OUT &= ~BIT2;              // P2.2 = 0
		              P2OUT |=  BIT0;              // P2.0 = 1 ,1&2_EN = 1,Motor is started
			          break;
				   
			case OFF: // Stop the Right Motor
				      P2OUT &= ~BIT1;              // P2.1 = 0
		              P2OUT &= ~BIT2;              // P2.2 = 0
		              P2OUT &= ~BIT0;              // P2.0 = 0 ,1&2_EN = 0,Motor is stoped
			          break;
				   
			case REVERSE: // Reverse the Direction of Right Motor
			              P2OUT &= ~BIT1;              // P2.1 = 0,
		                  P2OUT |=  BIT2;              // P2.2 = 1,
		                  P2OUT |=  BIT0;              // P2.0 = 1 ,1&2_EN = 1,Motor is started
					      break;
		  default: //Any other invalid option,Stop the motor
				   P2OUT &= ~BIT1;              // P2.1 = 0
		           P2OUT &= ~BIT2;              // P2.2 = 0
		           P2OUT &= ~BIT0;              // P2.0 = 0 ,1&2_EN = 0,Motor is stoped
				   
		}//End of Switch
	}//End of RightMotor()

	//==========================================================================//
	//       Function to Switch ON,Reverse and Stop the Left Motor              //
	//==========================================================================//
	void LeftMotor(char status)
	{
	    //For Enabling the I/O function of P2.6
	    P2SEL  &= ~BIT6;              // Clear P2.6 in P2SEL  (by default Xin)
		P2SEL2 &= ~BIT6;              // Clear P2.6 in P2SEL2
		
	    //Left Motor Control pin Direction settings
		P2DIR |=  BIT3 + BIT4 + BIT6; // P2.3,P2.4,P2.6 all output
		P2OUT &= ~BIT3 + BIT4 + BIT6; // Clear P2.3,P2.4,P2.6 
		
		//Switch() statement for deciding the direction of rotation of Motor
		switch(status)
		{
			case ON:  // Rotate the Left Motor Forward
  				      P2OUT |=  BIT3;              // P2.3 = 1,
		              P2OUT &= ~BIT4;              // P2.4 = 0
		              P2OUT |=  BIT6;              // P2.6 = 1 ,1&2_EN = 1,Motor is started
			          break;
				   
			case OFF: // Stop the Left Motor
				      P2OUT &= ~BIT3;              // P2.3 = 0
		              P2OUT &= ~BIT4;              // P2.4 = 0
		              P2OUT &= ~BIT6;              // P2.6 = 0 ,3&4_EN = 0,Motor is stoped
			          break;
				   
			case REVERSE: // Reverse the Direction of Left Motor
			              P2OUT &= ~BIT3;              // P2.3 = 0,
		                  P2OUT |=  BIT4;              // P2.4 = 1,
		                  P2OUT |=  BIT6;              // P2.6 = 1 ,3&4_EN = 1,Motor is started
					      break;
		  default: //Any other invalid option,Stop the motor
				   P2OUT &= ~BIT3;              // P2.3 = 0
		           P2OUT &= ~BIT4;              // P2.4 = 0
		           P2OUT &= ~BIT6;              // P2.6 = 0 ,3&4_EN = 0,Motor is stoped
				   
		}//End of Switch
	}//End of RightMotor()

	//===================================================================================//
	// 				Function to control the movement of the robot                        //
	// 				Forward,Reverse Right Turn,Left Turn                                 //
	//===================================================================================//		
	void  BotLocomotion(char status)
	{
	   switch(status)
	   {
	   		case FORWARD:   //Move the Robot Forward
			  				RightMotor(ON); // Switch on the Right Motor in Forward Direction
							LeftMotor(ON);  // Switch on the Left  Motor in Forward Direction
			  			    break;
							
	   		case REVERSE:   //Reverse the Robot
			  				RightMotor(REVERSE); // Reverse the Direction of the Right Motor
							LeftMotor(REVERSE);	 // Reverse the Direction of the Left Motor
			                break;
							
	   		case STOP:      //Stop the Robot  
			  				RightMotor(OFF);	 // Switch off The Right Motor 
							LeftMotor(OFF);      // Switch off The Left Motor 
			                break;
							
	   		case RIGHT_TURN://Turns the Robot Right
			  				RightMotor(OFF); // Switch off The Right Motor 
							LeftMotor(ON);   // Switch on the Left  Motor
			  			    break;
							
	   		case LEFT_TURN: //Turns the Robot Left
			  				LeftMotor(OFF); // Switch off The Left Motor 
							RightMotor(ON); // Switch on the Right Motor
			                break;
					
	   		default:		//Stop the Robot  
			  				RightMotor(OFF);	 // Switch off The Right Motor 
							LeftMotor(OFF);      // Switch off The Left Motor 
			  
		}//end of Switch()
	 }//End of Bot Locomotion
	
	void Delay(int time)
	{
		int i,j;
		for(i=0;i<time;i++)
			for(j=0;j<0xFFFF;j++);
	}
