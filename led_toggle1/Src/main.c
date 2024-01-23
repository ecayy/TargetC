#include<stdint.h>

int main(void)
{
    uint32_t *pClkCtrlReg =   (uint32_t*)0x40023830;
    uint32_t *pPortDModeReg = (uint32_t*)0x40020C00;
    uint32_t *pPortDOutReg =  (uint32_t*)0x40020C14;

    // 1. Enable the clock for GPIOD peripheral in the AHB1ENR (SET the 3rd bit position)
    *pClkCtrlReg |= (1 << 3);

    // 2. Configure the mode of the IO pin as output
    // a. Clear the 28th and 29th bit positions (CLEAR)
    *pPortDModeReg &= ~(3 << 28);
    // b. Make 28th bit position as 1 (SET)
    *pPortDModeReg |= (1 << 28);

    while(1)
    {
        // 3. Set 14th bit of the output data register to make I/O pin-14 as HIGH
        *pPortDOutReg |= (1 << 14);

        // Introduce a small delay
        // This loop executes for 10K times
        for(uint32_t i = 0; i < 10000; i++);

        // Turn OFF the LED
        *pPortDOutReg &= ~(1 << 14);

        for(uint32_t i = 0; i < 10000; i++);
    }

    return 0;
}
