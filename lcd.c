#include "i2c.h"
#include "lcd.h"
#include "msp430g2553.h"

void LcdInit()
{
    LcdWriteCommand(LCD_INIT_BYTE, 0); 
    __delay_cycles(80000);
    LcdWriteCommand(LCD_INIT_BYTE, 0);
    LcdWriteCommand(LCD_INIT_BYTE, 0);

    LcdWriteCommand(LCD_BUS_WIDTH_4BIT, 0);
    LcdWriteCommand(LCD_4BITS_2LINES_5x8FONT, 1);
    LcdWriteCommand(LCD_DISPLAY_OFF_CURSOR_OFF_BLINK_OFF, 1);
    LcdWriteCommand(LCD_CLEAR, 1);
    LcdWriteCommand(LCD_INCREMENT_NO_SHIFT, 1);
    LcdWriteCommand(LCD_DISPLAY_ON_CURSOR_OFF, 1);
}

void LcdWriteCommand(unsigned char data, unsigned char cmdtype)
{
    unsigned char byte;

    byte = (HI_NIBBLE(data) | LCD_BL) | LCD_EN;
    I2cTransmit(0x27, byte);
    while(I2cNotReady());

    byte = (HI_NIBBLE(data) | LCD_BL) & ~LCD_EN;   
    I2cTransmit(0x27, byte);
    while(I2cNotReady());

    // cmdtype = 0 -> One write cycle
    // cmdtype = 1 -> Two write cycles (4 bit mode)

    if (cmdtype)
    {
        byte = (LO_NIBBLE(data) | LCD_BL) | LCD_EN;
        I2cTransmit(0x27, byte);
        while(I2cNotReady());
        byte = (LO_NIBBLE(data) | LCD_BL) | ~LCD_EN;
        I2cTransmit(0x27, byte);
        while(I2cNotReady());
    }

    __delay_cycles(80000);
}
void LcdWriteChar(unsigned char data)
{
    unsigned char byte;

    byte = (HI_NIBBLE(data) | LCD_BL | LCD_RS) | LCD_EN;
    I2cTransmit(0x27, byte);
    while(I2cNotReady());

    byte = (HI_NIBBLE(data) | LCD_BL | LCD_RS) & ~LCD_EN;
    I2cTransmit(0x27, byte);
    while(I2cNotReady());

    byte = (LO_NIBBLE(data) | LCD_BL | LCD_RS) | LCD_EN;
    I2cTransmit(0x27, byte);
    while(I2cNotReady());

    byte = (LO_NIBBLE(data) | LCD_BL | LCD_RS) & ~LCD_EN;
    I2cTransmit(0x27, byte);
    while(I2cNotReady());

}
void LcdWriteString(char *s)
{
    while (*s != '\0')
        LcdWriteChar(*s++);
}
void LcdSetPosition(unsigned char row, unsigned char column)
{
    switch(row)
    {
        case 1: 
            LcdWriteCommand(LCD_LINE1 + (column - 1), 1); 
            break;
        case 2:
            LcdWriteCommand(LCD_LINE2 + (column - 1), 1);
            break;
        case 3:
            LcdWriteCommand(LCD_LINE3 + (column - 1), 1);
            break;
        case 4:
            LcdWriteCommand(LCD_LINE4 + (column - 1), 1);
            break;
        default:
            LcdWriteCommand(LCD_LINE1 + (column - 1), 1);
    }
}
