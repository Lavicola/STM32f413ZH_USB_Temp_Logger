# STM32f413ZH_Project


STM32 object oriented Temperature and Humidity Logger.
Every 5 Minutes via interrupt both values will be saved to an usb stick and a Display(hd44780) will update its values.
the following USB were successfully tested:

* Intenso Rainbow Line 4 GB USB-Stick USB 2.0 blau
* Kingston DataTraveler DT20 32GB USB Flash Drive
* SanDisk 16GB Cruzer Blade USB Flash Drive

Main.c is actually a cpp file but since the cubemx32(code generation) always destroys it I decided to just leave it with the .c ending.

Structure:
The Componentsmanager is like a facade and has the most important functions to get the value(s) from the sensors or for displaying these on the display. The Componentsmanager is also implemented as a singleton.
Every Sensor should inerhit from ISensor and should implement those functions.

The Project almost reached the allowed Codesize of 32kb if you want to change the display to a SSD1306 I would expect that you have to change/remove Code (or change the toolchain) . 
If you are looking for the Code I recommend this Repo: https://github.com/4ilo/ssd1306-stm32HAL . 
I tried it out and it pretty easy to integrate into the Project.

Since it was my first Project the folder structure is a bit unusual... The whole Custom Code is/should be in the "Custom" folder. 
