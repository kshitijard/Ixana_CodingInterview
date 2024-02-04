# Ixana_CodingInterview

## Challenge:

Write code to implement Modes 0, 1, and 2. Each mode must have an example function showing how this code would be used in an application.

## Approach:

Based on the information provided, I have implemented the code while making certain assumptions due to the open-ended nature of some points in the challenge.

I have interpreted the challenge with the following assumptions:
1. The connection between the MCU and one device.
2. MCU is controlling the device, and with Externel control, Device is controlling the other device.
3. There are three modes to configure the device: Mode 0, Mode 1, and Mode 2.
4. For Mode 0:
   - Set CTRL as an input pin with a low level.
   - Set Done pin as an output pin with a low level.
   - Set NRST as an input IRQ pin with a high level.
   After this initialization:
   - Make the NRST pin low for four clock cycles (20ms).
   - Then, make it high to generate an interrupt.
   - Once the interrupt is generated, after 10ms, communication will send the configuration data to the device.
   - After successful data transmission, set the DONE pin high, and the SUCCESS pin to 1 to indicate configuration completion without errors.

5. For Mode 1:
   - Set CTRL as an input pin with a low level.
   - Set Done pin as an output pin with a low level.
   - Set NRST as an input IRQ pin with a high level.
   After this initialization:
   - Make CTRL pin high after 3 clock cycles (15ms).
   - Make the NRST pin low for four clock cycles (20ms from the start).
   - Once the NRST pin is high, it will generate an interrupt.
   - The ISR will execute and set the CTRL pin as an output pin for external control.
   - I have added some delay, and after that, changed the DONE pin state to high, and SUCCESS pin to 1 to indicate configuration completion without errors.

Note: The assumption is made regarding CTRL line acting as an output pin for external control due to the lack of information provided for external control.
  
6. For Mode 2:
   - Set CTRL as an output pin with a high level.
   - Set Done pin as an output pin with a low level.
   - Set NRST as an output pin with a high level.
   After this initialization:
   - As information is not provided for external control, I have assumed that CTRL line will act as an output pin to control other devices.
   - I have added some delay, and after that, changed the DONE pin state to high, and SUCCESS pin to 1 to indicate configuration completion without errors.

Note: The assumption is made regarding CTRL line acting as an output pin for external control due to the lack of information provided for external control.

## Time Estimation:
The main challenge in this task was understanding the provided information. Due to the limited data, it took a significant amount of time to grasp the big picture and formulate a clear idea of the requirements. The breakdown of time spent on different stages is as follows:

1.Understanding Requirements: 3 hours.
- Understanding the given information and forming a comprehensive understanding of the task.

2.Designing Solution: 1 hour.
- Creating a high-level design for implementing Modes 0, 1, and 2 based on the understood requirements.

3.Development: 2 hours.
- Writing and testing the code for the designed solution.

4.Code Beautification and Documentation: 1 hour.
- Improving code readability and adding documentation for better understanding.

Total Time Spent: 7 hours
