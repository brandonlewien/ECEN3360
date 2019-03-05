/***************************************************************************//**
 * @main.c
 *******************************************************************************
 * # License
 * Copyright 2018 Silicon Laboratories Inc. www.silabs.com
 *******************************************************************************
 *
 * The licensor of this software is Silicon Laboratories Inc. Your use of this
 * software is governed by the terms of Silicon Labs Master Software License
 * Agreement (MSLA) available at
 * www.silabs.com/about-us/legal/master-software-license-agreement. This
 * software is distributed to you in Source Code format and is governed by the
 * sections of the MSLA applicable to Source Code.
 *
 ******************************************************************************/

#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "em_letimer.h"
#include "em_device.h"
#include "em_chip.h"
#include "em_cmu.h"
#include "em_emu.h"
#include "bsp.h"

#include "sleep.h"
#include "main.h"
#include "gpio.h"
#include "timer.h"
#include "cmu.h"
#include "uart.h"
#include "i2c.h"
#include "i2ctemp.h"

volatile uint16_t increment;
volatile char * receiving;
char loopback_buffer[LPBK_BUFFER_SIZE];

int main(void){
    EMU_DCDCInit_TypeDef dcdcInit = EMU_DCDCINIT_DEFAULT;
    CMU_HFXOInit_TypeDef hfxoInit = CMU_HFXOINIT_DEFAULT;
    EMU_EM23Init_TypeDef em23Init = EMU_EM23INIT_DEFAULT;

    CHIP_Init();                                             // Chip errata

    EMU_DCDCInit(&dcdcInit);                                 // init DCDC regulator
    em23Init.vScaleEM23Voltage = emuVScaleEM23_LowPower;     // always start in low noise mode
    EMU_EM23Init(&em23Init);                                 // init DCDC
    CMU_HFXOInit(&hfxoInit);                                 // init HFXO with kit specific parameters

    cmu_init();                                              // initialize clock trees
    //uart_init();
    gpio_init();                                             // sets up LED, I2C, and temp sensor enable pins
    letimer_init();                                          // initialize letimer for LED and I2C operation
    I2C_Setup();                                             // initialize I2C
    //I2C_Interrupt_Enable();                                // Enable Interrupts
    I2C_Reset_Bus();                                         // Reset I2C Bus
    //LEUART0_Interrupt_Enable();

    //LEUART0->CTRL &= ~LEUART_CTRL_LOOPBK;						// receiver gets data from RX pin
    //LEUART0->CTRL |= LEUART_CTRL_LOOPBK;						// receiver gets data from TX pin

//    char* sending = "AT+NAMECHARIZARD\r\n";
//    UART_send_n(sending, strlen(sending)+2);					// +2 becuase strlen views '\n' and '\r' as 1 char

    while (1) {
    	Enter_Sleep();
    	//UART_send_n(sending, 15);							// send many times to view in energy profiler
    	//for(int i = 0; i <1000000; i++); 					// to separate each n-byte transmission for easier view in energy profiler
    }
}
