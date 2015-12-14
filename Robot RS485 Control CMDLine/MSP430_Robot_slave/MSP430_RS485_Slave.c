//===========================================================================================================//
//      Program to Control the Robot according to the Signals send from the PC (Microcontroller Side )       //
//===========================================================================================================//


//------------------------------------------------------------------------------------------------------------//
//  |-----------------|                                                                                       //
//  | RS485 Motor-    |                  USB2SERIAL                                                           //
//  | -Ctrl-Master.exe|                  +==============================================+                     //
//  |                 |                  |	 +-----------+         +---------+          |                     //
//  |-----------------|                  |   |   	  TXD|-------->|DI       |          |                     //
//   \ [][][][][][][]  \    USB       +--|	 |        RXD|---------|RO      A|---+      |                     //
//    \ [] [] [] [] []  \=============|	     |USB        |         |         |   |      |                     //
//     \-----------------\            +--|   |       ~RTS|-------->|~RE     B|---|--+   |                     //
//                                       |   |	     ~DTR|-------->|DE       |   |  |   |                     //
//                                       |   +-----------+         +---------+   |  |   |                     //
//                                       |		FT232RL              MAX485      |  |   |                     //
//                                       +======================================[A]=[B]=+                     //
//                                                                                \/                          //
//                                                                                /\ Twisted Pair             //
//                                                                                \/ RS485                    //
//                                              Robot Shield On MSP430 Launchpad  /\                          //
//                                                       +======================[A]=[B]===+                   //
//                                                       |                       |   |    |                   //
//                                (Motor Right)----------|   +-------+        +--+---+-+  |                   //
//                                                       |   | L293D |        | MAX485 |  |                   //
//                                (Motor  Left)----------|   +-------+        +--------+  |                   //
//                                                       |                                |                   //
//                                                       +================================+                   //
//                                                                                                            //
//============================================================================================================//
// Compiler/IDE  :  IAR Embedded WorkBench for MSP430	                                                      //
//                  Code Composer Studio                                                                      //
//                                                                                                            // 
// License       :  MIT                                                                                       // 
// Programmer    :	Rahul.S                                                                                   //
// Date	         :	14-Dec-2015                                                                               //
//============================================================================================================//  

    #include "msp430g2553.h"
    #include "Motor.h"        // For Motor Control Routines
	#include "RS485.h"        // For RS485 Control Routines
   
    // Control Codes Send by the PC to Control the Robot through RS485 Protocol
	#define RobotPresent   'F'
	#define RobotForward   'A'
	#define RobotReverse   'B'
	#define RobotTurnRight 'C'
	#define RobotTurnLeft  'D'
	#define RobotStop      'E'

    void main(void)
    {
       
        WDTCTL = WDTPW + WDTHOLD; // Stop the watch dog to prevent system reset
		
		//------------------------------------------------------------------//
		// Function declaration                                             //
		//------------------------------------------------------------------//
		void Configure_Clocks();    // Configure DCO Clock @IMHz
		void RobotConnected(void);  //
		void delay(void);
		//------------------------------------------------------------------//
		
		//Main Loop
        Configure_Clocks();              // Configure the clocks of MSP430,DCO@1MHz
		Configure_MSP430_UART_USCI_A();  // Configure the MSP430 UART 
		Configure_MSP430_RS485(RECEIVE); // Put the MSP430 to receive data through RS485 Protocol
		_BIS_SR(GIE + LPM0_bits);        // Go to Sleep
      
    }//end of main() 

	void RobotConnected(void)
	{
	   char i = 0;
	   
	   P2DIR |= BIT0 + BIT1 + BIT2 + BIT3 + BIT4 + BIT6;
	   P2SEL  &= ~BIT6;               // IO function for P2.6
       P2SEL2 &= ~BIT6;               // IO function for P2.6
	   
	   for (i = 0;i < 3;i++)
	   {
		 P2OUT |=   BIT0 + BIT1 + BIT2 + BIT3 + BIT4 + BIT6;
		 delay();
		 P2OUT &= ~(BIT0 + BIT1 + BIT2 + BIT3 + BIT4 + BIT6);
		 delay();
	   }
	}

	void delay(void)
	{
	  char No;
	  int Count = 0xFFFF;
	  for(No = 0;No < 4;No++)
		  for(Count = 0;Count < 0xFFFF;Count++);
	}

	void Configure_Clocks(void)
	{
        //------------------- Configure the Clocks ---------------------------//
        // DC0 @ 1MHz ,SMCLK @1MHz,                                           //  
        //--------------------------------------------------------------------//
        
        if (CALBC1_1MHZ==0xFF)    // If calibration constant erased
            {	
                while(1);         // do not load, trap CPU!!
            } 

         DCOCTL  = 0;             // Select lowest DCOx and MODx settings
         BCSCTL1 = CALBC1_1MHZ;   // Set range
         DCOCTL  = CALDCO_1MHZ;   // Set DCO step + modulation 
         
       //---------------------------------------------------------------------//
         
	}

	//-----------------   USCI_A0 Recieve ISR    --------------------------//

   #pragma vector = USCIAB0RX_VECTOR
   __interrupt void USCI_A0_RecieveInterrupt(void)
  {
	 IFG2 &= ~UCA0RXIFG; // Clear the UCA0RXIFG
			
	 switch(UCA0RXBUF)  // Switch to control P2.1 and P2.2
	 {
					case RobotPresent: RobotConnected();
					                   break;
					case RobotForward: Bot_Forward();
					                   break;
	 				case RobotReverse :Bot_Reverse(); 
					                   break;
		            case RobotTurnRight: Bot_RightTurn();
					                   break;
					case RobotTurnLeft: Bot_LeftTurn();
					                   break;
					case RobotStop: Bot_Stop();
					                   break;
							   
	 }//end of switch
   }//end of ISR
  
  
	  
	  