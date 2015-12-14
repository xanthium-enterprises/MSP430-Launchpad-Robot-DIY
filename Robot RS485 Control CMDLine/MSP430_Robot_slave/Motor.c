  
  //==========================================================================//
  // Functions to Control the motor                                           //
  //--------------------------------------------------------------------------//
  // (c) Rahul.S                                                              //
  // www.xanthium.in                                                          //
  // BSD License                                                              //
  //==========================================================================//

  #include "msp430g2553.h"
  #include "Motor.h"

  //===========================================================================//
  //         Function to Control the right Motor (individually)                //
  //---------------------------------------------------------------------------//
  // eg:-  Right_Motor(ON);      // Starts the right motor                     //
  //       Right_Motor(OFF);     // Stops the right motor                      //
  //       Right_Motor(REVERSE); // Reverses the right motor                   //
  //===========================================================================//
  void Right_Motor(char Command) 
  {  
    //--------------------------------------------------------//
    // Right Motor Connected to P2.0,P2.1,P2.2                //   
    // Right Motor Controlled by 1A,2A and 1A_2A_EN of L293D  //
    //--------------------------------------------------------//
    //          MSP430                L293D                   //
    //       +----------+        +------------+               //
    //       |     P2.0 |--------|EN (1A & 2A)|               //
    //       |     P2.1 |--------|1A          |               //
    //       |     P2.2 |--------|2A          |               //
    //       +----------+        +------------+               //
    //--------------------------------------------------------//
    
   switch(Command)// used to select the operation of right motor 
   {
     case ON: //Forward Motion
              P2DIR |=  BIT0 + BIT1 + BIT2; // P2.0,P2.1,P2.2 all Output 
              P2OUT &= ~BIT0;               // EN (L293D) = 0,Disable the motor drivers (1A & 2A)
              P2OUT |=  BIT1;               // P2.1 = 1,(1A = 1)
              P2OUT &= ~BIT2;               // P2.2 = 0,(2A = 0)
              P2OUT |=  BIT0;               // Enable motor drivers (1A & 2A) EN = 1
              break;
              
     case OFF://Stop
               P2DIR |=  BIT0 + BIT1 + BIT2; // P2.0,P2.1,P2.2 all Output 
               P2OUT &= ~BIT0;               // EN (L293D) = 0,Disable the motor drivers (1A & 2A)
               P2OUT |=  BIT1 + BIT2;        // P2.1 and P2.2 all one,Visual indication
               break;
              
     case REVERSE:// Reverse direction 
                   P2DIR |=  BIT0 + BIT1 + BIT2; // P2.0,P2.1,P2.2 all Output 
                   P2OUT &= ~BIT0;               // EN (L293D) = 0,Disable the motor drivers (1A & 2A)
                   P2OUT &= ~BIT1;               // P2.1 = 0,(1A = 0)
                   P2OUT |=  BIT2;               // P2.2 = 1,(2A = 1)
                   P2OUT |=  BIT0;               // Enable motor drivers (1A & 2A) EN = 1
                   break;
         
      default:
                  P2DIR |=  BIT0 + BIT1 + BIT2; // P2.0,P2.1,P2.2 all Output 
                  P2OUT &= ~BIT0;               // EN (L293D) = 0,Disable the motor drivers (1A & 2A)
                  break;        
   }//end of switch()
 }//end of Right_Motor()

  //===========================================================================//
  //          Function to Control the Left Motor (individually)                //
  //---------------------------------------------------------------------------//
  // eg:-  Left_Motor(ON);      // Starts the Left motor                       //
  //       Left_Motor(OFF);     // Stops the Left motor                        //
  //       Left_Motor(REVERSE); // Reverses the Left motor                     //
  //===========================================================================//

 void Left_Motor(char Command) 
  {  
    //--------------------------------------------------------//
    // Left Motor Connected to P2.3,P2.4,P2.6                 //   
    // Left Motor Controlled by 3A,4A and 3A_4A_EN of L293D   //
    //--------------------------------------------------------//
    //          MSP430                L293D                   //
    //       +----------+        +------------+               //
    //       |     P2.6 |--------|EN (3A & 4A)|               //
    //       |     P2.3 |--------|3A          |               //
    //       |     P2.4 |--------|4A          |               //
    //       +----------+        +------------+               //
    //--------------------------------------------------------//
    
   switch(Command)// used to select the operation of Left motor 
   {
     case ON: //Forward Motion
              P2SEL  &= ~BIT6;               // IO function for P2.6
              P2SEL2 &= ~BIT6;               // IO function for P2.6
              P2DIR  |=  BIT3 + BIT4 + BIT6; // P2.3,P2.4,P2.6 all Output 
              P2OUT  &= ~BIT6;               // P2.6 =0, EN (L293D) = 0,Disable the motor drivers (3A & 4A)
              P2OUT  |=  BIT3;               // P2.3 = 1,(3A = 1)
              P2OUT  &= ~BIT4;               // P2.4 = 0,(4A = 0)
              P2OUT  |=  BIT6;               // P2.6 = 1, Enable motor drivers (1A & 2A) EN = 1
              break;
              
     case OFF: //Stop
              P2SEL  &= ~BIT6;               // IO function for P2.6
              P2SEL2 &= ~BIT6;               // IO function for P2.6
              P2DIR  |=  BIT3 + BIT4 + BIT6; // P2.3,P2.4,P2.6 all Output 
              P2OUT  &= ~BIT6;               // P2.6 =0, EN (L293D) = 0,Disable the motor drivers (3A & 4A)
              P2OUT  |=  BIT3 + BIT4;        // P2.3,P2.4 all one,Visual indication
              break; 
              
     case REVERSE: //Reverse Motion
              P2SEL  &= ~BIT6;               // IO function for P2.6
              P2SEL2 &= ~BIT6;               // IO function for P2.6
              P2DIR  |=  BIT3 + BIT4 + BIT6; // P2.3,P2.4,P2.6 all Output 
              P2OUT  &= ~BIT6;               // P2.6 = 0, EN (L293D) = 0,Disable the motor drivers (3A & 4A)
              P2OUT  &= ~BIT3;               // P2.3 = 0,(3A = 0)
              P2OUT  |=  BIT4;               // P2.4 = 1,(4A = 1)
              P2OUT  |=  BIT6;               // P2.6 = 1, Enable motor drivers (1A & 2A) EN = 1
              break;
              
    default: //Stop
              P2SEL  &= ~BIT6;               // IO function for P2.6
              P2SEL2 &= ~BIT6;               // IO function for P2.6
              P2DIR  |=  BIT3 + BIT4 + BIT6; // P2.3,P2.4,P2.6 all Output 
              P2OUT  &= ~BIT6;               // P2.6 =0, EN (L293D) = 0,Disable the motor drivers (3A & 4A)
              P2OUT  |=  BIT3 + BIT4;        // P2.3,P2.4 all one,Visual indication
              break;         
   }//end of switch()
  }//end of Left_Motor() 


  //===========================================================================//
  //    Function to move the bot forward                                       //
  //===========================================================================//
  void Bot_Forward(void)
  {
    Right_Motor(OFF);Left_Motor(OFF); // Stop both Motors(Right and Left)
    Right_Motor(ON);Left_Motor(ON);   // Start both Motors(Right and Left)
  }

  //===========================================================================//
  //    Function to stop the bot                                               //
  //===========================================================================//
  void Bot_Stop(void)
  {
    Right_Motor(OFF);Left_Motor(OFF); // Stop both Motors(Right and Left)
  }
  
  //===========================================================================//
  //    Function to reverse the bot                                            //
  //===========================================================================//
  void Bot_Reverse(void)
  {
    Right_Motor(OFF);Left_Motor(OFF);           // Stop both Motors(Right and Left)
    Right_Motor(REVERSE);Left_Motor(REVERSE);   // Reverse both Motors(Right and Left)
  }
  
  //===========================================================================//
  //    Function to turn the bot to the right                                  //
  //===========================================================================//
  void Bot_RightTurn(void)
  {
    Right_Motor(OFF);Left_Motor(OFF);  // Stop both Motors(Right and Left)
    Left_Motor(ON);                    // Activate Left motor to make right turn
  }
  
  //===========================================================================//
  //    Function to turn the bot to the left                                   //
  //===========================================================================//
  void Bot_LeftTurn(void)
  {
    Right_Motor(OFF);Left_Motor(OFF);  // Stop both Motors(Right and Left)
    Right_Motor(ON);                   // Activate Right motor to make left turn
  }