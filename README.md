# IntroductionToRobotics
Repository used to implement the laboratory homeworks for the Introduction to Robotics course.  Each homework includes requirements, implementation details, code and image files.

## Homework 1
#### Task Requirements
Use a separate potentiometer in controlling each of the colors of the RGB led. The control must be done with digital electronics.
### Components used
- Arduino uno
- 1 RGB LED
- 3 potentiometers
- 1 breadboard
- 1 330 ohm resistor and 2 220 ohm resistors
- wires
### How to do
First you take a wire and connect the ground of the Arduino Uno with the (-) power rail of the breadboard. Then you take the 3 potentiometers and connect them to the breadboard. Connect the last pin of each potentiometer to the (-) power rail and the first pin to the (+) power rail. Take the RBG LED to determine if the LED is anode or cathode common. In my case, the LED is common cathode. If that's the case connect the cathode to the (-) power rail.  Connect the first pin of the LED with the 330 ohm resistor and a wire that is going to the Arduino board in a Digital PWM pin (I used the 11 pin). Do the same with the third and fourth pin of the LED but use the 220 ohm resistors (I used the 9 and 3 pin).  First pin is for red color, second for green and third for blue. Connect the middle pin of each potentiometer to an analog pin (I used the A0 A1 and A2 pin). First pin is for red color, second for green and third for blue. Connect the 5V pin of the Arduino to the (+) power rail. Make sure you correctly connect each component. 
If you did everything correct you should have something like this:

![20211025_114723](https://user-images.githubusercontent.com/61494964/138664783-76d5cab5-8d5c-472f-93ed-ecb12c038a0c.jpg)

Open Arduino on PC and write this [code](https://github.com/hirneagabriel/IntroductionToRobotics/blob/main/homework1.ino) and try and understand it. Make sure you initialize the digital and analog pins if you didn't use the same pins as I. Check if everything is alright then connect the Arduino to the PC, and upload the code. Pray it works.



[Here](https://www.youtube.com/watch?v=JDddwAnWMO4) is a demo on Youtube of how things should work.


## Homework 2
![cat-loading](https://user-images.githubusercontent.com/61494964/137943557-d82fac86-541b-4c26-8764-5533e1fa59c1.gif)
