/**
 *
 *
 */
#include "main.h"
#include "stm32g0xx_hal.h"
//#include "stm32g0xx_hal_i2c.h"
#ifndef __GYRO_L3G4200_H__
#define __GYRO_L3G4200_H__

#define DEVICE_I2C_ADR							0xD2
#define DEVICE_I2C_ADR_READ						0xD3 // when SDO is connected to power supply, 0x68 in case of this pin connect to ground
#define DEVICE_I2C_ADR_WRITE					0xD2
#define DEVICE_NAME								0x0F
#define DEVICE_MODE_SHUTDOWN 					0x00
#define DEVICE_MODE_SLEEP						0x00
//read and write registers
#define DEVICE_CTRL_REG_1						0x20
#define DEVICE_CTRL_REG_2						0x21
#define DEVICE_CTRL_REG_3						0x22
#define DEVICE_CTRL_REG_4						0x23
#define DEVICE_CTRL_REG_5						0x24
#define	DEVICE_REFERENCE						0x25

#define DEVICE_OUT_TEMP							0x26
//FIFO register configuration
//watermark is used to set an specific level of full data and trigger an interupt
//default maximum watermark level
#define 	DEVICE_FIFO_CTRL_REG				0x2E
#define		DEVICE_FIFO_SRC_REG					0x2F

#define 	DEVICE_FIFO_MODE_BYPASS				0b0001111
#define 	DEVICE_FIFO_MODE_FF					0x0011111
#define 	DEVICE_FIFO_MODE_STREAM				0x0101111
#define 	DEVICE_FIFO_MODE_STREAM_TO_FF		0x0111111
#define 	DEVICE_FIFO_MODE_BYPASS_TO_STREAM 	0x04

enum deviceOperationMode
{
	Device_Mode_Normal,
	Device_Mode_Sleep,
	Device_Mode_Shutdown
};

enum bufferOperationMode
{
	Buffer_Mode_Bypass,
	Buffer_Mode_FIFO,
	Buffer_Mode_Stream,
	Buffer_Mode_Bypass_2_Stream,
	Stream_2_FIFO
};

//function to control device
uint8_t readDeviceName(I2C_HandleTypeDef *_hi2c_config);
uint16_t readRegister(I2C_HandleTypeDef *_hi2c_config,
						uint8_t regAddr, uint8_t num);
uint8_t readControlRegister1(I2C_HandleTypeDef *_hi2c_config);
uint8_t readControlRegister2(I2C_HandleTypeDef *_hi2c_config);
uint8_t readControlRegister3(I2C_HandleTypeDef *_hi2c_config);
uint8_t readControlRegister4(I2C_HandleTypeDef *_hi2c_config);
uint8_t readControlRegister5(I2C_HandleTypeDef *_hi2c_config);
uint8_t readReference(void);

//mode operation
void setDeviceMode(enum deviceOperationMode _setDeviceMode,
					I2C_HandleTypeDef *_hi2c_config);
void setDeviceIntoNormal(I2C_HandleTypeDef *_hi2c_config);
void setDeviceIntoModeSleep(void);
void setDeviceIntoModeShutdown(void);
void setWatermarkLevel(uint8_t _levelInput);

//buffer controlling
void setFIFOEnable(I2C_HandleTypeDef *_hi2c_config);
void setBuffferMode(enum bufferOperationMode _setBufferMode,
					I2C_HandleTypeDef *_hi2c_config);
void setBufferModeBypass(void);
void setBufferModeFifo(void);
void setBufferModeStream(void);
void setBufferModeBypass_2_Stream(void);
void setBufferModeStream_2_Fifo(void);
uint8_t readFifoControlReg(void);
uint8_t readFifoSourceReg(void);
uint8_t isFIFOstoreFull(void);
uint8_t isFIFOstoreEmpty(void);

//Temperature
uint8_t readOutputTemperature(I2C_HandleTypeDef *_hi2c_config);


#endif
