Embedded Systems - Track following tank

This project was done at Florida Atlantic University in the Intro to Embedded Systems class tau

Prerequisites
With regards to software the only thing that will be needed is the Code Composer Studio IDE that I will explain how to install in the installing tab.
With regards to the hardware components: 2 tcrt5000 sensors, 1 msp430g2553, resistors varying from 220 ohm to 10 kohms, plenty of wire,
                                         a car with 5v motors and a power supply, usb cable male to female wires, male to male wires.
                                        
Installing
In order to properly run and test the code a version of Code Composer Studio (CCS) by texas instruments will be needed to be installed on yor computer. This IDE will allow you to work with all variants of the msp430. A link for information on installing CCS can be found here: http://processors.wiki.ti.com/index.php/Compiler_Installation_and_Selection. 

Once the IDE is set up, you can go ahead and deploy my code onto CCS. Make sure to have your msp430 hooked up via the usb cable to your PC. Initially the code will compile and run correctly, however in order to properly achieve the desired results, you will have to wire up the msp430 to a breadboard which will communicate with the 2 motors and tcrt5000 line sensors. I will attach pictures of the schematic for full details.

Once everything is wired up based on the schematic, then you will be able to see the code at work! Although this is easier said then done, it will be well worth the work.

Running the tests
Now, that everything is running correctly, some tests that could be done to further validate would be to put the line sensors under a white sheet of paper. Doing this will cause the motor to stop running because when I did the Analog to Digital Conversion (ADC) in my code, I placed if else statements to shut off the motor if the line sensor was given high readings. The high readings pertain to the design of the tcrt5000 line sensors that cause a voltage spike when they encounter white and a voltage drop when they encounter a black color.

A second test would be to check the opposite case which is where the line sensors are placed above a black sheet of paper, this should cause the motors to start to run based on the same explanation that I gave about the line sensors encountering a white path.

Built With
Code Composer Studio
MSP430G2553

Authors
Syed Hammad Haque

Acknowledgments
Dr. Bassem Al-Halabi
Umran Al-Abd-AlRazzak
