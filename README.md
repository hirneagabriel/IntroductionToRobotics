# IntroductionToRobotics
Repository used to implement the laboratory homeworks for the Introduction to Robotics course.  Each homework includes requirements, implementation details, code and image files.

<details>
<summary>Homework 1</summary>
  
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

</details>

<details>
  <summary>Homework 2</summary>
  
  #### Task Requirements
   Building the traffic lights for a  crosswalk. Use 2 LEDs to represent the traffic lights for people (red and green) and 3 LEDs to represent the traffic lights for cars (red, yellow and green). The system has the following states:
  1. **State 1** (default, reinstated after state 4 ends): green light for cars, red light for people, no sounds. Duration: indefinite, changed by pressing the button.
  2. **State 2** (initiated by counting down 10 seconds after a button press): the light should be yellow for cars,  red for people, and no sounds.
  Duration:  3 seconds.
  3. **State 3** (initiated after state 2 ends): red for cars, green for people and beeping sound from the buzzer at a constant interval.  
  Duration: 10 seconds.
  4. **State 4** (initiated after state 3 ends):  red for cars, blinking green for people and a beeping sound from the buzzer, at a constant interval, faster than the beeping in state 3.
  
### Components used
- Arduino uno
- 2 Red LED
- 2 Green LED
- 1 Yellow LED
- 1 breadboard
- 1 button
- 1 buzzer
- 2 220 ohm resistors and 1 100 ohm resistor
- wires
  
 Picture of the setup:
  
  ![20211102_092814](https://user-images.githubusercontent.com/61494964/139807115-f44d8ccb-ed77-457e-a3e0-39e4746d6f34.jpg)
  
  The code for this setup can be found [here](https://github.com/hirneagabriel/IntroductionToRobotics/blob/main/homework2.ino)
  
  
  [Here](https://youtu.be/aLjNWYBl6ws) is a demo on Youtube of how things work.
  </details>
  
<details>
  <summary> Homework 3 </summary>
  
  ![cat-loading](https://user-images.githubusercontent.com/61494964/137943557-d82fac86-541b-4c26-8764-5533e1fa59c1.gif)
  
  </details>
