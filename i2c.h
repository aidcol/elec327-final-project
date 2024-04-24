#ifndef I2C_H
#define I2C_H

#define SDA_PIN BIT7
#define SCL_PIN BIT6
#define PRESCALE 12

void I2cTransmitInit(unsigned char slaveAddress);
void I2cTransmit(unsigned char slaveAddress, unsigned char byte);

unsigned char I2cNotReady();

#endif
