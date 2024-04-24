#ifndef LCD_H
#define LCD_H


/* bits 0-3 -> control signals
 * b0 -> RS (reset)
 * b1 -> RW (read/write)
 * b2 -> EN (enable)
 * b3 -> BL (backlight)
 * bits 4-7 -> data 
 */

#define LCD_WAIT_DELAY 2
#define LCD_BL 0x08
#define LCD_EN 0x04
#define LCD_RW 0x02
#define LCD_RS 0x01

#define LCD_INIT_BYTE           0x30  // 0011 0000
#define LCD_BUS_WIDTH_4BIT      0x20  // 0010 0000
#define LCD_BUS_WIDTH_8BIT      0x30  // 0011 0000
#define LCD_CLEAR               0x01  // 0000 0001
#define LCD_HOME                0x02  // 0000 0010
#define LCD_ON                  0x0C  // 0000 1100
#define LCD_OFF                 0x08  // 0000 1000
#define LCD_LINE1               0x80  // 1000 0000
#define LCD_LINE2               0xC0  // 1100 0000
#define LCD_LINE3               0x94  // 1001 0100
#define LCD_LINE4               0xD4  // 1101 0100
#define LCD_CURSOR_OFF          0x0C  // 0000 1100
#define LCD_UNDERLINE_ON        0x0E  // 0000 1110
#define LCD_BLINK_CURSOR_ON     0x0F  // 0000 1111
#define LCD_MOVE_CURSOR_LEFT    0x10  // 0001 0000
#define LCD_MOVE_CURSOR_RIGHT   0x14  // 0001 0100
#define LCD_SHIFT_LEFT          0x18  // 0001 1000
#define LCD_SHIFT_RIGHT         0x1E  // 0001 1110

#define LCD_DISPLAY_ON_CURSOR_OFF               0x0C
#define LCD_DISPLAY_OFF_CURSOR_OFF_BLINK_OFF    0x08
#define LCD_4BITS_2LINES_5x8FONT                0x28
#define LCD_INCREMENT_NO_SHIFT                  0x06

#define LO_NIBBLE(b) (((b) << 4) & 0xF0)
#define HI_NIBBLE(b) ((b) & 0xF0)

void LcdInit();
void LcdWriteCommand(unsigned char data, unsigned char cmdtype);
void LcdWriteChar(unsigned char data);
void LcdWriteString(char *s);
void LcdSetPosition(unsigned char row, unsigned char column);

#endif
