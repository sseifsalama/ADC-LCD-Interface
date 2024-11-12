*** Settings ***
Documentation     Embedded Systems Project Test Cases
Setup             Connect Project Circuit
*** Test Cases ***
Test Case 1: Verify Arduino Startup Sequence
    [Documentation] Ensuring the Arduino boots up correctly and displays the expected menu on the LCD.

    [Setup steps]
    Connect Arduino to PC
    Open Serial Monitor

    [Action steps]
    Observe LCD Screen and Serial Monitor
    
    [Assertion steps]
    Check if LCD Screen Printed expected main menu | Expected Menu = "Analog Sensors\n 1:POT 2:LDR"
    Check if Serial Monitor printed expected output | Expected Output = "System Started"

Test Case 2: Verify Menu Navigation
    [Documentation]    Ensuring that the keypad allows seamless navigation between options
    # Arrange (Set up the test environment)
    [Setup steps]
    Connect Arduino to PC
    Open Serial Monitor

    # Act (Perform the action to be tested)
    [Action steps]
    Observe LCD and Serial Monitor
    Press 1 on the Keypad
    Press 9 on the Keypad
    Press 2 on the Keypad
    Press 9 on the Keypad

    # Assert (Verify the expected outcome)
    [Assertion steps]
    After pressing 1 on the Keypad:
      Verify LCD displays the expected menu | Expected Menu = "POT:{POT_VALUE} {STATUS}\n LLM:{LLM_VALUE} HHM:{HHM_VALUE}" 
      Verify if Serial Monitor printed expected output | Expected Output = "Potentiometer Chosen" 
    After pressing 9 on the Keypad:
      Confirm the LCD returns to the main menu.
      Verify if Serial Monitor printed expected output | Expected Output = "System Started"
    After pressing 2 on the Keypad:
       Verify LCD displays the expected menu | Expected Menu = "LDR:{LDR_VALUE} {STATUS}\n LLM:{LLM_VALUE} HHM:{HHM_VALUE}"
       Verify if Serial Monitor printed expected output | Expected Output = "Light Dependent Resistor Chosen"
    After pressing 9 on the Keypad:
      Confirm the LCD returns to the main menu.
      Verify if Serial Monitor printed expected output | Expected Output = "System Started" 

Test Case 3: Verify Potentiometer Values and Status
    [Documentation]    Ensuring Potentiometer value is displayed correctly and verifying correct status changes
    # Arrange (Set up the test environment)
    [Setup steps]
    Connect Arduino to PC
    Open Serial Monitor
    Press 1 on Keypad

    # Act (Perform the action to be tested)
    [Action steps]
    Rotate Potentiometer from minimum to maximum and to minimum again
    Observe Changes on LCD and RED LED
    

    # Assert (Verify the expected outcome)
    [Assertion steps]
    After rotating potentiometer:
     Verify that POT_VALUE in "POT:{POT_VALUE}" is updating correctly, where new value overwrites old value
     If POT_VALUE < LLM:
      Verify that STATUS in "POT:{POT_VALUE} {STATUS}" shows "NOK"
      Verify that RED LED is turned on
     Else if POT_VALUE > LLM and POT_VALUE < HHM:
      Verify that STATUS in "POT:{POT_VALUE} {STATUS}" shows "OK"
      Verify that RED LED is turned off
     Else if POT_VALUE > HHM:
      Verify that STATUS in "POT:{POT_VALUE} {STATUS}" shows "NOK"
      Verify that RED LED is turned on

Test Case 4: Verify Potentiometer Lower Limit Change
    [Documentation]    Ensuring Potentiometer lower limit is changed correctly and status is updated accordingly
    # Arrange (Set up the test environment)
    [Setup steps]
    Connect Arduino to PC
    Open Serial Monitor
    Press 1 on Keypad

    # Act (Perform the action to be tested)
    [Action steps]
    Press 5 on Keypad
    Rotate Potentiometer until POT_VALUE = LLM - 2
    Press 4 on Keypad
    Rotate Potentiometer until POT_VALUE = LLM - 2
   
    

    # Assert (Verify the expected outcome)
    [Assertion steps]
    After Pressing 5 on Keypad:
     Verify that LLM_Value in "LLM:{LLM_VALUE}" has increased by 5
     Verify that Serial Monitor prints "Low Limit Increased"
    After Rotating Potentiometer until POT_VALUE = LLM - 2:
     Verify that STATUS in "POT:{POT_VALUE} {STATUS}" shows "NOK"
     Verify that RED LED is turned on
    After Pressing 4 on Keypad:
     Verify that LLM_Value in "LLM:{LLM_VALUE}" has decreased by 5
     Verify that Serial Monitor prints "Low Limit Decreased"
     Verify that STATUS in "POT:{POT_VALUE} {STATUS}" shows "OK"
     Verify that RED LED is turned off
    After Rotating Potentiometer until POT_VALUE = LLM - 2:
     Verify that STATUS in "POT:{POT_VALUE} {STATUS}" shows "NOK"
     Verify that RED LED is turned on

Test Case 5: Verify Potentiometer Higher Limit Change
    [Documentation]    Ensuring Potentiometer higher limit is changed correctly and status is updated accordingly
    # Arrange (Set up the test environment)
    [Setup steps]
    Connect Arduino to PC
    Open Serial Monitor
    Press 1 on Keypad

    # Act (Perform the action to be tested)
    [Action steps]
    Press 7 on Keypad
    Rotate Potentiometer until POT_VALUE = HHM + 2
    Press 8 on Keypad 
    Rotate Potentiometer until POT_VALUE = HHM + 2
   
    

    # Assert (Verify the expected outcome)
    [Assertion steps]
    After Pressing 7 on Keypad:
     Verify that HHM_VALUE in "HHM:{HHM_VALUE}" has decreased by 5
     Verify that Serial Monitor prints "High Limit Decreased"
    After Rotating Potentiometer until POT_VALUE = HHM + 2
     Verify that STATUS in "POT:{POT_VALUE} {STATUS}" shows "NOK"
     Verify that RED LED is turned on
    After Pressing 8 on Keypad:
     Verify that HHM_VALUE in "HHM:{HHM_VALUE}" has increased by 5
     Verify that Serial Monitor prints "High Limit Increased"
     Verify that STATUS in "POT:{POT_VALUE} {STATUS}" shows "OK"
     Verify that RED LED is turned off
    After Rotating Potentiometer until POT_VALUE = HHM + 2:
     Verify that STATUS in "POT:{POT_VALUE} {STATUS}" shows "NOK"
     Verify that RED LED is turned on

Test Case 6: Verify LDR values and status
    [Documentation]    Ensuring LDR value is displayed correctly and verifying correct status changes
    # Arrange (Set up the test environment)
    [Setup steps]
    Connect Arduino to PC
    Open Serial Monitor
    Press 2 on Keypad

    # Act (Perform the action to be tested)
    [Action steps]
    Expose LDR to low light intensity conditions until LDR_VALUE < LLM
    Expose LDR to medium light intensity conditions until LDR_VALUE > LLM and LDR_VALUE < HHM
    Expose LDR to high light intensity conditions until LDR_VALUE > HHM
    

    # Assert (Verify the expected outcome)
    [Assertion steps]
    After changing light intensity conditions:
     Verify that LDR_VALUE in "LDR:{LDR_VALUE}" is updating correctly, where new value overwrites old value
     If LDR_VALUE < LLM:
      Verify that STATUS in "LDR:{LDR_VALUE} {STATUS}" shows "NOK"
      Verify that RED LED is turned on
     Else if LDR_VALUE > LLM and LDR_VALUE < HHM:
      Verify that STATUS in "LDR:{LDR_VALUE} {STATUS}" shows "OK"
      Verify that RED LED is turned off
     Else if LDR_VALUE > HHM:
      Verify that STATUS in "LDR:{LDR_VALUE} {STATUS}" shows "NOK"
      Verify that RED LED is turned on

Test Case 7: Verify LDR Lower Limit Change
    [Documentation]    Ensuring LDR lower limit is changed correctly and status is updated accordingly
    # Arrange (Set up the test environment)
    [Setup steps]
    Connect Arduino to PC
    Open Serial Monitor
    Press 2 on Keypad

    # Act (Perform the action to be tested)
    [Action steps]
    Press 5 on Keypad 10 times
    Reduce light intensity until LDR_VALUE < LLM and LDR_VALUE > LLM - 50
    Press 4 on Keypad 10 times
    Rotate Potentiometer until LDR_VALUE < LLM
   
    

    # Assert (Verify the expected outcome)
    [Assertion steps]
    After Pressing 5 on Keypad 10 times:
     Verify that LLM_Value in "LLM:{LLM_VALUE}" has increased by 50
     Verify that Serial Monitor prints "Low Limit Increased" 10 times
    After Reducing light intensity until LDR_VALUE < LLM and LDR_VALUE > LLM - 50:
     Verify that STATUS in "LDR:{LDR_VALUE} {STATUS}" shows "NOK"
     Verify that RED LED is turned on
    After Pressing 4 on Keypad 10 times:
     Verify that LLM_Value in "LLM:{LLM_VALUE}" has decreased by 50
     Verify that Serial Monitor prints "Low Limit Decreased" 10 times
     Verify that STATUS in "LDR:{LDR_VALUE} {STATUS}" shows "OK"
     Verify that RED LED is turned off
    After Reducing light intensity until LDR_VALUE < LLM:
     Verify that STATUS in "LDR:{LDR_VALUE} {STATUS}" shows "NOK"
     Verify that RED LED is turned on

 Test Case 8: Verify LDR Higher Limit Change
    [Documentation]   Ensuring LDR higher limit is changed correctly and status is updated accordingly
    # Arrange (Set up the test environment)
    [Setup steps]
    Connect Arduino to PC
    Open Serial Monitor
    Press 2 on Keypad

    # Act (Perform the action to be tested)
    [Action steps]
    Press 7 on Keypad 10 times
    Increase light intensity conditions until LDR_VALUE > HHM and LDR_VALUE < HHM + 50
    Press 8 on Keypad 10 times 
    Increase light intensity until LDR_VALUE > HHM 
   
    

    # Assert (Verify the expected outcome)
    [Assertion steps]
    After Pressing 7 on Keypad 10 times:
     Verify that HHM_VALUE in "HHM:{HHM_VALUE}" has decreased by 50
     Verify that Serial Monitor prints "High Limit Decreased" 10 times
    After increasing light intensity until LDR_VALUE > HHM and LDR_VALUE < HHM + 50
     Verify that STATUS in "LDR:{LDR_VALUE} {STATUS}" shows "NOK"
     Verify that RED LED is turned on
    After Pressing 8 on Keypad 10 times:
     Verify that HHM_VALUE in "HHM:{HHM_VALUE}" has increased by 50
     Verify that Serial Monitor prints "High Limit Increased" 10 times
     Verify that STATUS in "LDR:{LDR_VALUE} {STATUS}" shows "OK"
     Verify that RED LED is turned off
    After increasing light intensity until LDR_VALUE > HHM:
     Verify that STATUS in "POT:{POT_VALUE} {STATUS}" shows "NOK"
     Verify that RED LED is turned on   

Test Case 9:
     


      
     


# ... Add more test cases as needed ...
