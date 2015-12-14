  
  //==========================================================================//
  // Constants and dfunction declarations for motor.c                         //
  //--------------------------------------------------------------------------//
  // (c) Rahul.S                                                              //
  // www.xanthium.in                                                          //
  // BSD License                                                              //
  //==========================================================================//

  #define ON      0x01
  #define OFF     0x02
  #define REVERSE 0x03

  // Function to control the individual motors 
  void Right_Motor(char Command);
  void Left_Motor (char Command);
  
  // Functions to Control both motors together
  void Bot_Forward(void); // Move the bot forward 
  void Bot_Stop(void);    // stop the bot
  void Bot_Reverse(void); // Reverse the bot
  void Bot_RightTurn(void);// Make a Right turn
  void Bot_LeftTurn(void); // Make a left turn
  