/*
 * Title: 4PositionsHomeToHardStop
 *
 * Objective:
 *    This example demonstrates control of the ClearPath-MCPV operational mode
 *    Move To Absolute Position, 4 Positions (Home to Hard Stop)
 *
 * Description:
 *    This example enables, homes, and then moves a ClearPath motor between
 *    preprogrammed absolute positions as defined in the MSP software. During
 *    operation, various move statuses are written to the USB serial port.
 *
 * Requirements:
 * 1. A ClearPath motor must be connected to Connector M-0.
 * 2. The connected ClearPath motor must be configured through the MSP software
 *    for Move To Absolute Position, 4 Positions (Home to Hard Stop) mode (In
 *    MSP select Mode>>Position>>Move to Absolute Position, then with "4
 *    Positions (Home to Hard Stop)" selected hit the OK button).
 * 3. The ClearPath motor must be set to use the HLFB mode "ASG-Position
 *    w/Measured Torque" with a PWM carrier frequency of 482 Hz through the MSP
 *    software (select Advanced>>High Level Feedback [Mode]... then choose
 *    "ASG-Position w/Measured Torque" from the dropdown, make sure that 482 Hz
 *    is selected in the "PWM Carrier Frequency" dropdown, and hit the OK
 *    button).
 * 4. The ClearPath must have defined Absolute Position Selections through
 *    the MSP software (On the main MSP window check the "Position Selection
 *    Setup (cnts)" box and fill in the four text boxes labeled "A off B off",
 *    "A on B off", "A off B on" and "A on B on").
 * 5. Homing must be configured in the MSP software for your mechanical
 *    system (e.g. homing direction, torque limit, etc.). To configure, click
 *    the "Setup..." button found under the "Homing" label on the MSP's main
 *    window.
 * 6. Ensure the Input A & B filters in MSP are both set to 20ms (In MSP
 *    select Advanced>>Input A, B Filtering... then in the Settings box fill in
 *    the textboxes labeled "Input A Filter Time Constant (msec)" and "Input B
 *    Filter Time Constant (msec)" then hit the OK button).
 *
 * Links:
 * ** ClearCore Documentation: https://teknic-inc.github.io/ClearCore-library/
 * ** ClearCore Manual: https://www.teknic.com/files/downloads/clearcore_user_manual.pdf
 * ** ClearPath Manual (DC Power): https://www.teknic.com/files/downloads/clearpath_user_manual.pdf
 * ** ClearPath Manual (AC Power): https://www.teknic.com/files/downloads/ac_clearpath-mc-sd_manual.pdf
 *
 *
 * Copyright (c) 2020 Teknic Inc. This work is free to use, copy and distribute under the terms of
 * the standard MIT permissive software license which can be found at https://opensource.org/licenses/MIT
 */






#include "ClearCore.h"

// The INPUT_A_B_FILTER must match the Input A, B filter setting in
// MSP (Advanced >> Input A, B Filtering...)
#define INPUT_A_B_FILTER 20

// Defines the motor's connector as ConnectorM0
#define motor ConnectorM0

// Select the baud rate to match the target device
#define baudRate 9600

// This example has built-in functionality to automatically clear motor faults. 
//	Any uncleared fault will cancel and disallow motion.
// WARNING: enabling automatic fault handling will clear faults immediately when 
//	encountered and return a motor to a state in which motion is allowed. Before 
//	enabling this functionality, be sure to understand this behavior and ensure 
//	your system will not enter an unsafe state. 
// To enable automatic fault handling, #define HANDLE_MOTOR_FAULTS (1)
// To disable automatic fault handling, #define HANDLE_MOTOR_FAULTS (0)
#define HANDLE_MOTOR_FAULTS (0)

// Declares user-defined helper functions.
// The definition/implementations of these functions are at the bottom of the sketch.
bool MoveToPosition(int positionNum);
void HandleMotorFaults();

//Define switches and variables
//#define inputPin IO0




void setup() {
    // Put your setup code here, it will only run once:




    // Sets all motor connectors to the correct mode for Absolute Position mode
    MotorMgr.MotorModeSet(MotorManager::MOTOR_ALL,
                          Connector::CPM_MODE_A_DIRECT_B_DIRECT);

    // Set the motor's HLFB mode to bipolar PWM
    motor.HlfbMode(MotorDriver::HLFB_MODE_HAS_BIPOLAR_PWM);
    // Set the HFLB carrier frequency to 482 Hz
    motor.HlfbCarrier(MotorDriver::HLFB_CARRIER_482_HZ);

    // Enforces the state of the motor's A and B inputs before enabling the motor
    motor.MotorInAState(false);
    motor.MotorInBState(false);

    // Sets up serial communication and waits up to 5 seconds for a port to open
    // Serial communication is not required for this example to run
    Serial.begin(baudRate);
    uint32_t timeout = 5000;
    uint32_t startTime = millis();
    while (!Serial && millis() - startTime < timeout) {
        continue;
    }

    // Enables the motor; homing will begin automatically
    motor.EnableRequest(true);
    Serial.println("Motor Enabled");

    // Waits for HLFB to assert (waits for homing to complete if applicable)
    Serial.println("Waiting for HLFB...");
    while (motor.HlfbState() != MotorDriver::HLFB_ASSERTED &&
			!motor.StatusReg().bit.MotorInFault) {
        continue;
    }
	// Check if a motor faulted during enabling
	// Clear fault if configured to do so 
    if (motor.StatusReg().bit.MotorInFault) {
		Serial.println("Motor fault detected.");		
		if(HANDLE_MOTOR_FAULTS){
			HandleMotorFaults();
		} else {
			Serial.println("Enable automatic fault handling by setting HANDLE_MOTOR_FAULTS to 1.");
		}
		Serial.println("Enabling may not have completed as expected. Proceed with caution.");		
 		Serial.println();
	} else {
		Serial.println("Motor Ready");	
	}
}



void loop() {

  {

    // Move to Position 1 defined in MSP
    MoveToPosition(2);    // See below for the detailed function definition
    delay(1500);
    MoveToPosition(3);
    delay(150);
    MoveToPosition(4);
    delay(350);
    MoveToPosition(2);
    delay(350);
    MoveToPosition(1);
    delay(50);
    
    
    }

    // Alternatively, if you'd like to control the ClearPath servo's inputs
    // externally using ClearCore inputs, consider doing something like this:
    /*
     motor.MotorInAState(digitalRead(DI6)); // Sets ClearPath's InA to DI6's
                                            // state
     motor.MotorInBState(digitalRead(DI7)); // Sets ClearPath's InB to DI7's
                                            // state
    */
}

/*------------------------------------------------------------------------------
 * MoveToPosition
 *
 *    Move to position number positionNum (defined in MSP)
 *    Prints the move status to the USB serial port
 *    Returns when HLFB asserts (indicating the motor has reached the commanded
 *    position)
 *
 * Parameters:
 *    int positionNum  - The position number to command (defined in MSP)
 *
 * Returns: True/False depending on whether the position was successfully
 * commanded.
 */
bool MoveToPosition(int positionNum) {
    // Check if a motor fault is currently preventing motion
	// Clear fault if configured to do so 
    if (motor.StatusReg().bit.MotorInFault) {
		if(HANDLE_MOTOR_FAULTS){
			Serial.println("Motor fault detected. Move canceled.");
			HandleMotorFaults();
		} else {
			Serial.println("Motor fault detected. Move canceled. Enable automatic fault handling by setting HANDLE_MOTOR_FAULTS to 1.");
		}
        return false;
    }

    Serial.print("Moving to position: ");
    Serial.print(positionNum);

    switch (positionNum) {
        case 1:
            // Sets Input A and B for position 1
            motor.MotorInAState(false);
            motor.MotorInBState(false);
            Serial.println(" (Inputs A Off/B Off)");
            break;
        case 2:
            // Sets Input A and B for position 2
            motor.MotorInAState(true);
            motor.MotorInBState(false);
            Serial.println(" (Inputs A On/B Off)");
            break;
        case 3:
            // Sets Input A and B for position 3
            motor.MotorInAState(false);
            motor.MotorInBState(true);
            Serial.println(" (Inputs A Off/B On)");
            break;
        case 4:
            // Sets Input A and B for position 4
            motor.MotorInAState(true);
            motor.MotorInBState(true);
            Serial.println(" (Inputs A On/B On)");
            break;
        default:
            // If this case is reached then an incorrect positionNum was entered
            return false;
    }

    // Ensures this delay is at least 2ms longer than the Input A, B filter
    // setting in MSP
    delay(2 + INPUT_A_B_FILTER);

    // Waits for HLFB to assert (signaling the move has successfully completed)
    Serial.println("Moving.. Waiting for HLFB");
    while (motor.HlfbState() != MotorDriver::HLFB_ASSERTED &&
			!motor.StatusReg().bit.MotorInFault) {
        continue;
    }
	// Check if a motor faulted during move
	// Clear fault if configured to do so 
    if (motor.StatusReg().bit.MotorInFault) {
		Serial.println("Motor fault detected.");		
		if(HANDLE_MOTOR_FAULTS){
			HandleMotorFaults();
		} else {
			Serial.println("Enable automatic fault handling by setting HANDLE_MOTOR_FAULTS to 1.");
		}
		Serial.println("Motion may not have completed as expected. Proceed with caution.");
		Serial.println();
		return false;
    } else {
		Serial.println("Move Done");
		return true;
	}

    Serial.println("Move Done");
    return true;
}
//------------------------------------------------------------------------------

 
/*------------------------------------------------------------------------------
 * HandleMotorFaults
 *
 *    Clears motor faults by cycling enable to the motor.
 *    Assumes motor is in fault 
 *      (this function is called when motor.StatusReg.MotorInFault == true)
 *
 * Parameters:
 *    requires "motor" to be defined as a ClearCore motor connector
 *
 * Returns: 
 *    none
 */
 void HandleMotorFaults(){
 	Serial.println("Handling fault: clearing faults by cycling enable signal to motor.");
	motor.EnableRequest(false);
	Delay_ms(10);
	motor.EnableRequest(true);
	Delay_ms(100);
}
//------------------------------------------------------------------------------