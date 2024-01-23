#include<stdint.h>

int main(void)
{
    uint32_t *pClkCtrlReg =   (uint32_t*)0x40023830;
    uint32_t *pPortDModeReg = (uint32_t*)0x40020C00;
    uint32_t *pPortDOutReg =  (uint32_t*)0x40020C14;

    // 1. Enable the clock for GPIOD peripheral in the AHB1ENR (SET the 3rd bit position)
    *pClkCtrlReg |= (1 << 3);

    // 2. Configure the mode of the IO pin as output
    // a. Clear the 30th and 31st bit positions (CLEAR)
    *pPortDModeReg &= ~(3 << 30);
    // b. Make 30th bit position as 1 (SET)
    *pPortDModeReg |= (1 << 30);

    while(1)
    {
        // 3. Set 15th bit of the output data register to make I/O pin-15 as HIGH
        *pPortDOutReg |= (1 << 15);

        // Introduce a small delay
        // This loop executes for 10K times
        for(uint32_t i = 0; i < 1000; i++);

        // Turn OFF the LED
        *pPortDOutReg &= ~(1 << 15);

        for(uint32_t i = 0; i < 1000; i++);
    }

    return 0;
}
