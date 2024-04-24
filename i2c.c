#include "i2c.h"
#include "msp430g2553.h"

unsigned char byteToTransmit;
unsigned char byteSent = 0;

void I2cTransmitInit(unsigned char slaveAddress)
{
    P1SEL      |= SDA_PIN + SCL_PIN;               // Assign I2C pins to USCI_B0
    P1SEL2     |= SDA_PIN + SCL_PIN;
    UCB0CTL1    = UCSWRST;                         // Enable SW reset
    UCB0CTL0    = UCMST + UCMODE_3 + UCSYNC;       // I2C Master, synchronous mode
    UCB0CTL1    = UCSSEL_2 + UCSWRST;              // Use SMCLK, keep SW reset
    UCB0BR0     = PRESCALE;                        // Set prescaler - SMCLK = ~1048Khz/12 = 87.3Khz
    UCB0BR1     = 0;
    UCB0I2CSA   = slaveAddress;                    // Set slave address
    UCB0CTL1   &= ~UCSWRST;                        // Clear SW reset, resume operation
    UCB0I2CIE   = UCNACKIE;                        // Interrupt on slave Nack
    IE2         = UCB0TXIE;                        // Enable TX interrupt
}

void I2cTransmit(unsigned char slaveAddress, unsigned char byte)
{
    I2cTransmitInit(slaveAddress);
    byteToTransmit = byte;
    byteSent = 0;
    UCB0CTL1 |= UCTR + UCTXSTT; // Generate start condition
}

unsigned char I2cNotReady()
{
    return (UCB0STAT & UCBBUSY); // Check if I2C bus is busy
}

#pragma vector = USCIAB0TX_VECTOR
__interrupt void USCIAB0TX_ISR(void)
{    
    if (!(IFG2 & UCB0RXIFG))
    {
        if (byteSent == 1) // If the byte was sent...
        {       
            UCB0CTL1 |= UCTXSTP; // Generate stop condition
            IFG2 &= ~UCB0TXIFG;
        }
        else
        {
            UCB0TXBUF = byteToTransmit; // Send the byte 
            byteSent = 1; // Modify the variable accordingly
        }        
    }
}
