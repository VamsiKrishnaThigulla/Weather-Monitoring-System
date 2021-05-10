# Weather-Monitoring-System
 Weather Monitoring System which monitors the temperature and light intensity using analog sensors and plots the changes over a period of time.

## Board
- Texas Instruments TM4C123GH6PM Tiva C Launchpad
![Connection diagram for the TM4C123GH6PM](https://energia.nu/pinmaps/img/EK-TM4C123GXL.jpg)
![Connection diagram for the TM4C123GH6PM](https://energia.nu/pinmaps/img/EK-TM4C123GXL-BACK.jpg)

## Sensors
- LM35 Temperature Sensor

 ![LM35 Analog Temperature Sensor](https://www.electronicwings.com/public/images/user_images/images/Sensor%20%26%20Modules/LM35/LM35%20Pinout.png)
- Photoresistor

  ![Photoresistor](https://d12oja0ew7x0i8.cloudfront.net/image-handler/ts/20190820094913/ri/750/src/images/Article_Images/ImageForArticle_18355(1).jpg)

#### Other Components
- Breadboard
- Jumper Wires
- 2k ohm resistor

## Languages and libraries used
- C
 1. tm4c123gh6pm.h
- Python3
1. Tkinter
2. matplotlib
3. csv
4. datetime

## Circuit Diagrams
![Circuit Diagram for Weather Monitoring System](/Circuit_Diagrams/Circuit_Diagram.jpeg)
![Circuit](/Circuit_Diagrams/Circuit.jpeg)

## Connections
- LM35
1. The LM35 has three pins.
2. The first pin is connected to Vcc of the board.
3. The second pin is the data pin, it is connected to AIN0 i.e. PE3 pin of the board.
4. The third pin is connected to the GND of the board.

- Photoresistor
1. The photoresistor has two pins.
2. The first pin is connected to the Vcc of the board.
3. The second pin is connected to
- The AIN1 i.e. PE2 pin on the board
- The GND pin of the board through a resistor




### Output
![GUI Welcome Screen](/Screenshots/GUI_Open.jpg)
![Display Weather](/Screenshots/Display_Weather.jpg)
![Weather Plot](/Screenshots/Plot.png)
[![Recorded Output](http://img.youtube.com/vi/9_wM76P6ETY/0.jpg)](https://youtu.be/9_wM76P6ETY)

### Instructions
1. Upload the C code to a TM4C123GH6PM board through IAR Workbench or Keil.
2. Make the required connections between the components.
3. Run the code through workbench.
4. Run the GUI.py code.
5. Open the serial connection between the GUI and the board through COM3 port's UART0 terminal, through the 'Open Connection' button.
6. Get the values of the Temperature and Light Intensity through the 'Weather' button.
7. Plot the values and observe the changes over the period of time through the 'Plot' button.
8. Close the connection and the window with the 'Close Connection' button.
