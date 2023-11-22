/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"
#include "Grove_LCD_RGB_Backlight.h"

#define WAIT_TIME_MS 1000 
DigitalOut led1(LED1);
Grove_LCD_RGB_Backlight rgbLCD(PB_9,PB_8); //esto no hay que cambiar porque PB_9 y PB_8 son las posiciones del I2C
float NTC, R_t;
AnalogIn V_out(A2);
 float T_o = 298.15; 
 float R_o=100000; //En ohm;
 float beta=4250;
 char cadena[16]; //string en C no; usar char mejor
 float tension;

int main()
{
    printf("This is the bare metal blinky example running on Mbed OS %d.%d.%d.\n", MBED_MAJOR_VERSION, MBED_MINOR_VERSION, MBED_PATCH_VERSION);

    while (true)
    {
        tension=V_out*3.3; // el micro internamente hace en 3.3
        rgbLCD.locate(0,0);
        rgbLCD.setRGB(0xff, 0xff, 0xff);
        NTC=(5.0*100000.0/tension)-100000; // ojo unidades todo en ohmio
        R_t=NTC;
        float T=(beta/(log(R_t/R_o)+beta/T_o))-273.15;
        sprintf(cadena, "La temp es %.2f\n", T);
        rgbLCD.print(cadena);
        

        thread_sleep_for(WAIT_TIME_MS);

        


    }
}
