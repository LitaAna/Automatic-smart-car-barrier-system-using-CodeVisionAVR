This project involves designing and building an automatic barrier system controlled by an ATmega164A microcontroller.
The barrier system is designed to automatically open and close based on the proximity of an object or vehicle, utilizing infrared distance sensing technology.
When an object is detected within a predefined range, the barrier will automatically lift, and after a specified time, it will lower again. 

Components Used:

1.ATmega164A Microcontroller: The core component responsible for controlling the logic of the barrier system.

2.Servo Motor: Used to physically open and close the barrier. The angle of the servo is adjusted according to the detection signal from the distance sensor.

3.LCD Display:A 16x2 character LCD is used to display the distance between the barrier and the approaching vehicle.

4.GP2Y0A21YK0F Infrared Distance Sensor: This infrared sensor detects objects or vehicles approaching the barrier. 
It sends the signal to the microcontroller, which triggers the servo motor to open or close the barrier.

You can watch the demonstration video [here](https://github.com/LitaAna/Automatic-smart-car-barrier-system-using-CodeVisionAVR/blob/main/video.mp4).
