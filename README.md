# 387_mid_project
There are two working projects submitted. 
They are: 
1. prep.c
2. feedcat.c

For the prep.c, it shows why callibration is needed in the feedcat project, by comparing analog value of two identical sensors (either photoresistor or flex sensor).
The detailed wiring is in 387_pres1_materials/prep_wiring. 
When comparing flex sensors, please check that the pin value in line ten and eleven in prep.c is set to 2 and 3 repectively.
When comparing photoresistors, please check that the pin value in line ten and eleven in prep.c is set to 0 and 1 repectively.

For compilation, please use command "python compile_script_prep_mac.py 1" "python compile_script_prep_mac.py 2" "python compile_script_prep_mac.py 3" "python compile_script_prep_mac.py 4" one by one. 
Note: these command lines are for macOS. If on windows, need to add “.exe” at the last line and change the port according to your own device in the compile_script_prep_mac.py.

For feedcat.c, If there is enough luminance and the flex sensor is considered straight, one led will light up. It will not light up in any other situation, the flex sensor has to be straight and the environment has to be considered bright. 
The detailed wiring is in 387_pres1_materials/feedcat_wiring.

For compilation, please use command "python compile_script.py 1" "python compile_script.py 2" "python compile_script.py 3" "python compile_script.py 4" one by one. 
Note: these command lines are for macOS. If on windows, need to add “.exe” at the last line and change the port according to your own device in the compile_script_prep_mac.py.

Referrences: 
https://components101.com/asset/sites/default/files/component_datasheet/Flex%20Sensor%20Datasheet.pdf
https://components101.com/sensors/flex-sensor-working-circuit-datasheet
https://cdn.sparkfun.com/datasheets/Sensors/LightImaging/SEN-09088.pdf
https://www.instructables.com/How-to-use-a-Flex-Sensor-Arduino-Tutorial/
https://learn.adafruit.com/photocells/arduino-code
https://stackoverflow.com/questions/43180889/how-to-do-analogread-in-avr-assembly-language
https://hekilledmywire.wordpress.com/2011/03/16/using-the-adc-tutorial-part-5/
https://medium.com/@jrejaud/arduino-to-avr-c-reference-guide-7d113b4309f7
https://learn.sparkfun.com/tutorials/sik-experiment-guide-for-arduino---v32/experiment-6-reading-a-photoresistor
https://learn.adafruit.com/photocells/arduino-code
https://www.electronicshub.org/interfacing-flex-sensor-with-arduino/
https://www.digikey.com/en/resources/conversion-calculators/conversion-calculator-resistor-color-code
https://www.ardumotive.com/how-to-use-a-flex-sensor-en.html

Demonstration of the product: 
https://youtu.be/J1_-P_mOPS0

