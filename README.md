## Embedded Systems Project Report: ADC LCD Interface

## 1. Introduction
This project focuses on developing an ADC LCD Interface system designed to monitor and display real-time analog sensor data on an LCD screen. Its primary goal is to provide a simple, adjustable, and intuitive interface for viewing and managing analog data, such as readings from sensors like potentiometers or light-dependent resistors (LDRs). Users can set customizable threshold limits for the sensor values, with alerts triggered if readings exceed these set boundaries. This system is implemented in native C programming without Arduino-based code or pre-developed libraries, ensuring it meets embedded systems requirements for efficient, low-level control.

### Goals of the Project
The goals of this project include:

* Real-Time Data Display: Showing current analog sensor values on an LCD screen for easy monitoring.
* Threshold-Based Alerts: Providing configurable upper and lower limits that trigger alerts when readings fall outside these boundaries.
* User Interaction via Keypad: Allowing users to input threshold values through a keypad, enabling flexibility in the system without needing to reprogram it.
* Embedded C Code: Using native C to ensure the code is lightweight, efficient, and suitable for embedded environments with limited resources.

### Problem Addressed
Many embedded applications require monitoring analog values from sensors, often with specific thresholds to indicate safe or critical levels. This ADC LCD Interface addresses the need for an adaptable solution to view and manage these analog values in real time. By offering a standalone, easy-to-use interface that integrates with various sensors, it simplifies tasks in fields such as environmental monitoring, robotics, and automation, where quick, visual feedback is essential.

## 2. Project Code

**GitHub Repository:**
[Embedded-Project-2](https://github.com/sseifsalama/Embedded-Project-2)

**Local Root Directory**
[Source_Code](./src/main)

## 3. Test Cases

Test Cases are developed in Robot Framework Test steps:
[Robot_Tests](./test/assignment_test_cases.robot)

## 4. Bill of Materials (BOM)

**BOM**
[BOM](./bom/BOM.csv)

**Optimized BOM**
[Optimized_BOM](./bom/optimized_bom.csv)

## 5. Video Demonstration

[Demo_Video](./video/sample_video.mp4)


## 6. Design
[Design_Report](./design/project_design_tpl.md)
