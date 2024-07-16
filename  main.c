/*
 * Name: Olayiwola David Abraham
 * Date: 2/14/24
 * Pedestrian Crossing Signal System
/* DriverLib Includes */

#include <ti/devices/msp432p4xx/driverlib/driverlib.h>

/* Standard Includes */
#include <stdint.h>
#include <stdbool.h>
#include "lcd_utils.h"
void delay_ms(uint32_t milliseconds) {
    uint32_t i;
    for(i = 0; i < milliseconds*300; i++) {
        ; // Delay loop
    }
}

/* delay in seconds and poll for button press*/
uint8_t delay_and_poll(uint8_t seconds){
    uint8_t press = 0;
    uint32_t i, j, k;

    for(i = 0; i < seconds;i++){
        for(j = 0; j <20;j++){
            for(k =0;k<15000;k++){
            }


            // Check if button is pressed
        if (GPIO_getInputPinValue(GPIO_PORT_P1, GPIO_PIN1) == GPIO_INPUT_PIN_LOW) {
            press = 1;
        }
      }
    }

return press;
}
uint8_t k;
uint8_t i;
uint8_t color;

// Function to control RGB LED output based on the color code
void RGB_Output(uint8_t color){

    switch(color){


           case 1:
           GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_PIN0 |GPIO_PIN1 |GPIO_PIN2);
           GPIO_setOutputLowOnPin(GPIO_PORT_P1, GPIO_PIN0);
           GPIO_setOutputHighOnPin(GPIO_PORT_P2,GPIO_PIN1 |GPIO_PIN0);//yellow
           GPIO_setOutputHighOnPin(GPIO_PORT_P1, GPIO_PIN0);//red

           break;

           case 2:
           GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_PIN0 |GPIO_PIN1 |GPIO_PIN2);
           GPIO_setOutputHighOnPin(GPIO_PORT_P2, GPIO_PIN0);//red
           GPIO_setOutputLowOnPin(GPIO_PORT_P1, GPIO_PIN0);

           break;

           case 3:
           GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_PIN0 |GPIO_PIN1 |GPIO_PIN2);
           GPIO_setOutputHighOnPin(GPIO_PORT_P2, GPIO_PIN1);//green
           GPIO_setOutputHighOnPin(GPIO_PORT_P1, GPIO_PIN0);//red
           break;

           case 4:
           GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_PIN0 |GPIO_PIN1 |GPIO_PIN2);
           GPIO_setOutputLowOnPin(GPIO_PORT_P1, GPIO_PIN0);
           GPIO_setOutputHighOnPin(GPIO_PORT_P2, GPIO_PIN0);//red
           for(i=0;i<2;i++){
           GPIO_toggleOutputOnPin(GPIO_PORT_P1, GPIO_PIN0); //flash red
           delay_ms(500);
           GPIO_toggleOutputOnPin(GPIO_PORT_P1, GPIO_PIN0); //flash red
           delay_ms(500);
           break;}


                     }
          }



int main(void){
    uint8_t press = 0;
    uint8_t j;

    /* Halting the Watchdog */
    WDT_A_hold(WDT_A_BASE);

   LCD_init();


    /* Configuring P1.0 as output */
   GPIO_setAsOutputPin(GPIO_PORT_P1, GPIO_PIN0);
   GPIO_setOutputLowOnPin(GPIO_PORT_P1, GPIO_PIN0);


        GPIO_setAsOutputPin(GPIO_PORT_P2, GPIO_PIN2 | GPIO_PIN1 | GPIO_PIN0);
        GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_PIN2 | GPIO_PIN1 | GPIO_PIN0);
        GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P1, GPIO_PIN1);

    while (1){


        // Set RGB to Green and Red, and display "PEDSTP"
        RGB_Output(3);
        showChar('P',char1);
        showChar('E',char2);
        showChar('D',char3);
        showChar('S',char4);
        showChar('T',char5);
        showChar('P',char6);
        // Wait for button press for up to 8 seconds
        press = delay_and_poll(8);
        while(press != 1){
           press = delay_and_poll(1);
        }

        if(press == 1 ){
            // Set RGB to Yellow and display "PEDSTP"
            RGB_Output(1);
            showChar('P',char1);
            showChar('E',char2);
            showChar('D',char3);
            showChar('S',char4);
            showChar('T',char5);
            showChar('P',char6);
            delay_and_poll(4);

            // Set RGB to Red and display "PEDGO"
            RGB_Output(2);
            showChar('P',char1);
            showChar('E',char2);
            showChar('D',char3);
            clearChar(char4);
            clearChar(char5);
            clearChar(char6);
            showChar('G',char5);
            showChar('O',char6);
                   showNum(press,char6);
            delay_and_poll(4);



            clearChar(char1);
            clearChar(char2);
            clearChar(char3);
            clearChar(char4);
            clearChar(char5);
            clearChar(char6);

            // Clear display and count down from 4 to 1
            for(j = 4; j > 0;j--){
            clearChar(char6);
            showNum(j,char6);
            RGB_Output(4);


        }
            // Clear all characters
            clearChar(char1);
            clearChar(char2);
            clearChar(char3);
            clearChar(char4);
            clearChar(char5);
            clearChar(char6);
            // Reset press variable
            press = 0;
        }

    }
    return 0;
}
