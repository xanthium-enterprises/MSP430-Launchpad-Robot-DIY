 
#include "msp430g2553.h"
#include "RS485.h"



void Configure_MSP430_UART_USCI_A()
	{
	  //--------- Setting the UART function for P1.1 & P1.2 ---------//
      
	  P1SEL  |=  BIT1 + BIT2;  		    // P1.1 UCA0RXD input
      P1SEL2 |=  BIT1 + BIT2;  		    // P1.2 UCA0TXD output
	  
	  //------------ Configuring the UART(USCI_A0) ----------------//
	  
	  UCA0CTL1 |=  UCSSEL_2 + UCSWRST;  // USCI Clock = SMCLK,USCI_A0 disabled
      UCA0BR0   =  104;                 // 104 From datasheet table-  
      UCA0BR1   =  0;                   // -selects baudrate =9600,clk = SMCLK
      UCA0MCTL  =  UCBRS_1;             // Modulation value = 1 from datasheet
      UCA0CTL1 &= ~UCSWRST;             // Clear UCSWRST to enable USCI_A0
	  
	  //---------------- Enabling the interrupts ------------------//
	  
	  IE2 |= UCA0RXIE;                  // Enable the  interrupt
	  _BIS_SR(GIE);                     // Enable the global interrupt
	  
	}

	void Configure_MSP430_RS485(char mode)
	{
	    //------------ Configuring MAX485 Control Lines ---------------//
	  
	    P2DIR  |= BIT5; // P2.5 output,P2.5->~RE (MAX485)on RobotShield V1.0
		P1DIR  |= BIT7; // P1.7 output,P1.7-> DE (MAX485)on RobotShield V1.0
		
		switch(mode)
  		{
  			case TRANSMIT:  P2OUT  |= BIT5;   // ~RE -> High 
			                P1OUT  |= BIT7;   //  DE -> High -> Transmit mode enabled
							break;
			case RECEIVE:   P2OUT  &= ~BIT5;  // ~RE -> Low -> Receive mode enabled
			                P1OUT  &= ~BIT7;  //  DE -> Low 
							break;
  		}
	}
  