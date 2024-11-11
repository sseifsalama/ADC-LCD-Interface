*** Settings ***
Documentation    Embedded Systems Project Test Cases

*** Test Cases ***
Test Case 1: Verify Arduino Startup Sequence
    [Documentation] Ensuring the Arduino boots up correctly and displays the expected menu on the LCD.

    [Setup steps]
    Connect Arduino to PC
    Open Serial Monitor

    [Action steps]
    Observe LCD Screen and Serial Monitor
    
    [Assertion steps]
    Check if LCD Screen Printed Expected menu | Expected Menu = "Analog Sensors\n 1:POT 2:LDR"
    Check if Serial Monitor printed expected output | Expected Output = "System Started"

Test Case 2: [Test Case Name]
    [Documentation]    [Describe the test case]
    # Arrange (Set up the test environment)
    [Setup steps]

    # Act (Perform the action to be tested)
    [Action steps]

    # Assert (Verify the expected outcome)
    [Assertion steps]

Test Case 3: [Test Case Name]
    [Documentation]    [Describe the test case]
    # Arrange (Set up the test environment)
    [Setup steps]

    # Act (Perform the action to be tested)
    [Action steps]

    # Assert (Verify the expected outcome)
    [Assertion steps]

# ... Add more test cases as needed ...
