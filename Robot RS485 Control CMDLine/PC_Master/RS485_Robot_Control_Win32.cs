
//------------------------------------------------------------------------------------------------------------//
//              Program to Control a MSP430 based Robot using RS485 Protocol (Win32)                          //
//------------------------------------------------------------------------------------------------------------//
// The C# program running on Windows PC will send Commands in the form of ASCII charcters like A,B,C to the   //
// MSP430 Microcontroller on the Robot through RS485 Protocol.                                                //
//                                                                                                            //
// On the PC side a USB to RS485 Converter is used Convert the USB signals to RS485.                          //
// On the Robot Side ,MAX485 chip decodes the RS485 signals and feed them to the MSP430 UART.                 //
//------------------------------------------------------------------------------------------------------------//
// Commands for Controlling the Robot                                                                         //
// **********************************                                                                         //
// You can control the direction of Robot by Pressing the Following Keys on your KeyBoard                     //
//                                                                                                            //
//  		[Q] --> Stops the Robot                                                                           //
//  		[W] --> Moves the Robot Forward                                                                   //
//  		[A] --> Turns the Robot to Left                                                                   //
//  		[D] --> Turns the Robot to Right                                                                  //
//  		[S] --> Reverses the Robot                                                                        //
//  		[F] --> Checks Connectivity Between Robot and PC                                                  //
//  		[X] --> Exit from the Program                                                                     //
//                                                                                                            //
//------------------------------------------------------------------------------------------------------------//
//  |-----------------|                                                                                       //
//  | RS485 Robot-    |                  USB2SERIAL                                                           //
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
//                                                                                /\                          //
//                                                                                \/                          //
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
// Compiler/IDE  :	Microsoft Visual Studio Express 2013 for Windows Desktop(Version 12.0)                    //
//                  C# (Dot net Framework)                                                                    //
// OS            :	Windows(Windows 7)                                                                        // 
// License       :  MIT                                                                                       // 
// Programmer    :	Rahul.S                                                                                   //
// Date	         :	14-Dec-2015                                                                               //
//============================================================================================================//  

//============================================================================================================//
// www.xanthium.in                                                                                            //
// (c) Rahul.S 2015                                                                                           //
//============================================================================================================//


using System;
using System.IO.Ports;   //namespace containing SerialPort class

namespace MSP430_Robot_Control
{
	class Menu
	{
		public static void Main()
		{
			
			string COMPortName;  	 // To store COM port name 
			string Choice;      	 // For selecting the action
			bool Sentry = true;  	 // Used to exit from the loop
			
			SerialPort COMPort = new SerialPort();   // Create a new SerialPort Object 
			
			Choice_Menu(); // Draw a Banner on Top displaying Program name 
			
			Console.WriteLine("\n\t Enter the Serial Port Number eg COM32->"); // Enter the COM port to be used for communication,eg COM32
			COMPortName = Console.ReadLine();                                  // Read the COM port number                             
			COMPortName = COMPortName.Trim();
			
			ConfigureSerial(COMPort,COMPortName);  //Assign Baudrate,databit,start/stop bits to COMPort 
			
			// Loop for Controlling the Robot 
			while(Sentry)
			{
				Choice_Menu();                       // Display Program name Banner 
				SerialSettingsDisplay_Menu(COMPort); // Display Selected COMPort and Baudrate 
				Display_Commands();
				
				Choice = EnterChoice();              // Ask for user input 
				
				Console.WriteLine("\t Choice -->{0}",Choice); //Display selected option
				
				
				switch(Choice)
				{
					case "W":  RS485_Transmit(COMPort,"A");
					           Console.WriteLine("\n\t Robot-Forward,Both Motors ON");
					           Console.Write("\t Press Any Key to Continue....");
					           Console.Read();
						       break;
						       
					case "S":  RS485_Transmit(COMPort,"B");
							   Console.WriteLine("\n\t Robot-Reverse,Both Motors Reverse");
							   Console.Write("\t Press Any Key to Continue....");
					           Console.Read();
						       break;
						       
					case "D":  RS485_Transmit(COMPort,"C");
							   Console.WriteLine("\n\t Robot-Turn Right,Right Motor ON");
							   Console.Write("\t Press Any Key to Continue....");
					           Console.Read();
						       break;	
						       
					case "A":  RS485_Transmit(COMPort,"D");
				        	   Console.WriteLine("\n\t Robot-Turn Left,Left Motor ON");
					           Console.Write("\t Press Any Key to Continue....");
					           Console.Read();
						       break;
						       
				    case "Q":  RS485_Transmit(COMPort,"E");
				               Console.WriteLine("\n\t Robot-Stop,Both Motors OFF");
					           Console.Write("\t Press Any Key to Continue....");
						       break;	
						       
				    case "F":  RS485_Transmit(COMPort,"F");
				    		   Console.WriteLine("\n\t Checking Connectivity");
					           Console.Write("\t Press Any Key to Continue....");	
						       break;	
						       
					case "X":  Sentry = false;
							   RS485_Transmit(COMPort,"E");	
							   Console.WriteLine("\n\t Press Any Key to Quit");
						       break;	
						       
				    default :  Console.WriteLine("Invalid Input");
						       break;
				
				}//end of Switch()
				
			}//end of While() loop
			Console.Read();
			
		}
		
		
		static void ConfigureSerial(SerialPort Serial,string Name)
		{
			Name = Name.ToUpper();
			Serial.PortName = Name;              // Assign the COM port number
            Serial.BaudRate = 9600;              // Set Baud rate = 9600
            Serial.DataBits = 8;                 // Number of data bits = 8
            Serial.Parity   = Parity.None;       // No parity
            Serial.StopBits = StopBits.One;      // One stop bit
		}
		
		static void RS485_Transmit(SerialPort Serial,String Data)//Transmitting through RS485 
		{
			try
			{
				Serial.Open();                       // Open the serial port
				Serial.DtrEnable = false;            // Since DTR = 0.~DTR = 1 So  DE = 1 Transmit Mode enabled
            	Serial.RtsEnable = false;            // Since RTS = 0,~RTS = 1 So ~RE = 1
				Serial.Write(Data);                  // Write data to opened serial port
				Serial.Close();                      // Close the Serial port  
			}
			catch
			{
				Console.Clear();    // Clear the console Window 
				Console.WriteLine("\n\t Error in Opening Serial Port");
				Console.WriteLine("\n\t Selected Serial Port -> {0}",Serial.PortName);
				Console.ReadLine();
			}
		}
		
		static string EnterChoice()
		{
			string Choice;
			Console.Write("\t Enter Choice ---> ");
			Choice = Console.ReadLine();
			Choice = Choice.Trim();
			Choice = Choice.ToUpper();
			return Choice;
		}
		
		static void Choice_Menu()
		{
			Console.Clear();    //Clear the console Window 
            Console.WriteLine();
            Console.WriteLine("\t+---------------------------------------------------+");
            Console.WriteLine("\t|             MSP430 Robot RS485 Control            |");
            Console.WriteLine("\t|               (c) www.xanthium.in                 |");
            Console.WriteLine("\t+---------------------------------------------------+");
		}
		
		static void SerialSettingsDisplay_Menu(SerialPort Serial)
		{
			Console.WriteLine("\t|   Serial Port-> {0}         BaudRate-> {1}     |",Serial.PortName,Serial.BaudRate);
			Console.WriteLine("\t+---------------------------------------------------+");
		}
		
		static void Display_Commands()
		{
			//Console.WriteLine("\t+---------------------------------------------------+");
			Console.WriteLine("\t|                 \" W \" - Forward                   |");
			Console.WriteLine("\t| \" A \" - Left    \" Q \" - Stop        \" D \" - Right |");
			Console.WriteLine("\t|                 \" S \" - Reverse                   |");
			Console.WriteLine("\t|                                                   |");
			Console.WriteLine("\t| \" F \" - Check Connection       \" X \" - Quit       |");
			Console.WriteLine("\t+---------------------------------------------------+");
		}
	}//end of Class Menu()
}//end of namespace MSP430_Robot_Control