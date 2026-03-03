/*
 * Evar, cooperative message-passing task scheduler.
 * https://github.com/targeted/evar
 *
 * Copyright (c) 2026 Dmitry Dvoinikov <dmitry@targeted.org>
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
 * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE
 * OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "evar_device.h"

volatile evar_timer_ticks_t hardware_timer_ticks;

void SysTick_Handler(void) {
    hardware_timer_ticks += 1;
}

void evar_device__initialize(void) {

    // Enable lazy stacking for interrupt handlers.  This allows floating-point
    // instructions to be used within interrupt handlers, but at the expense of
    // extra stack usage.

    FPULazyStackingEnable();

    // Set the clocking to run directly from the crystal, system clock 80MHz.

    SysCtlClockSet(SYSCTL_SYSDIV_2_5 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ);

    // Disable watchdog timer.

    SysCtlPeripheralEnable(SYSCTL_PERIPH_WDOG0);
    while (!SysCtlPeripheralReady(SYSCTL_PERIPH_WDOG0)) {}
    WatchdogUnlock(WATCHDOG0_BASE);
    WatchdogResetDisable(WATCHDOG0_BASE);
        
    // Enable all peripheral modules that we are going to be using.
        
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    while (!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOA)) {}

    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
    while (!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOB)) {}

    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);
    while (!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOC)) {}

    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
    while (!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOD)) {}

    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
    while (!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOE)) {}

    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    while (!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF)) {}

    // Set RGB pins to output.

    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3);

    // Configure UART 0 to be the serial link.
        
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
    while (!SysCtlPeripheralReady(SYSCTL_PERIPH_UART0)) {}
    
    GPIOPinConfigure(GPIO_PA0_U0RX);
    GPIOPinConfigure(GPIO_PA1_U0TX);
    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);

    UARTClockSourceSet(UART0_BASE, UART_CLOCK_PIOSC);
    UARTStdioConfig(0, 115200, 16000000);

    UARTFIFOEnable(UART0_BASE);

    // Unlock one pin that we need to use for an output UART.

    HWREG(GPIO_PORTD_BASE + GPIO_O_LOCK) = GPIO_LOCK_KEY;
    HWREG(GPIO_PORTD_BASE + GPIO_O_CR) |= GPIO_PIN_7;
    HWREG(GPIO_PORTD_BASE + GPIO_O_LOCK) = 0;    

    // Configure timer.
        
    hardware_timer_ticks = 0;

    SysTickPeriodSet(SysCtlClockGet() / EVAR_TIMER_FREQUENCY);
    SysTickIntEnable();
    SysTickEnable();
}

evar_timer_ticks_t evar_device__get_timer_ticks(void) {
    return hardware_timer_ticks;
}

void evar_device__crash(unsigned short error, char* message) {
    UARTprintf("crash %04x: %s\n", error, message);
    evar_device__crashed_pin_on();
    evar_device__halt();
}

void evar_device__halt(void) {
    evar_device__halted_pin_on();
    while (1) {
        evar_device__disable_interrupts();
        evar_device__cpu_idle();
    }
}

/*
 * If any of the remaining board-specific things were declared in
 * evar_device_<board>.h as functions, they should be implemented here.
 */
