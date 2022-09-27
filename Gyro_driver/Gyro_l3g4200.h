/**
 *
 *
 */
#ifndef __GYRO_L3G4200_H__
#define __GYRO_L3G4200_H__

#include "main.h"
#include "stm32g0xx_hal.h"

#define DEVICE_I2C_ADR							0xD2

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
#define DEVICE_STATUS_REG						0x27
//FIFO register configuration
#define 	DEVICE_FIFO_CTRL_REG				0x2E
#define		DEVICE_FIFO_SRC_REG					0x2F

#define 	DEVICE_FIFO_MODE_BYPASS				0b0001111
#define 	DEVICE_FIFO_MODE_FF					0x0011111
#define 	DEVICE_FIFO_MODE_STREAM				0x0101111
#define 	DEVICE_FIFO_MODE_STREAM_TO_FF		0x0111111
#define 	DEVICE_FIFO_MODE_BYPASS_TO_STREAM 	0x04
// 3 axises
#define		DEVICE_OUT_X_L_REG					0x28
#define		DEVICE_OUT_X_H_REG					0x29
#define		DEVICE_OUT_Y_L_REG					0x2A
#define		DEVICE_OUT_Y_H_REG					0x2B
#define		DEVICE_OUT_Z_L_REG					0x2C
#define		DEVICE_OUT_Z_H_REG					0x2D
I2C_HandleTypeDef *_hi2c_config;
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
uint8_t readRegister(I2C_HandleTypeDef *_hi2c_config,
						uint8_t regAddr);
uint8_t readControlRegister1(I2C_HandleTypeDef *_hi2c_config);
uint8_t readControlRegister2(I2C_HandleTypeDef *_hi2c_config);
uint8_t readControlRegister3(I2C_HandleTypeDef *_hi2c_config);
uint8_t readControlRegister4(I2C_HandleTypeDef *_hi2c_config);
uint8_t readControlRegister5(I2C_HandleTypeDef *_hi2c_config);
uint8_t readStatusRegister(I2C_HandleTypeDef *_hi2c_config);
uint8_t readReference(void);

//mode Operating
uint8_t setDeviceMode(enum deviceOperationMode _setDeviceMode,
					I2C_HandleTypeDef *_hi2c_config);
uint8_t setDeviceIntoNormal(I2C_HandleTypeDef *_hi2c_config);
uint8_t setDeviceIntoModeSleep(I2C_HandleTypeDef *_hi2c_config);
uint8_t setDeviceIntoModeShutdown(I2C_HandleTypeDef *_hi2c_config);
uint8_t setWatermarkLevel(I2C_HandleTypeDef *_hi2c_config,
					uint8_t _levelInput);

//buffer controlling
uint8_t setFIFOEnable(I2C_HandleTypeDef *_hi2c_config);
uint8_t setBuffferMode(enum bufferOperationMode _setBufferMode,
					I2C_HandleTypeDef *_hi2c_config);
uint8_t readFifoControlReg(void);
uint8_t readFifoSourceReg(void);
uint8_t isFIFOstoreFull(I2C_HandleTypeDef *_hi2c_config);
uint8_t isFIFOstoreEmpty(I2C_HandleTypeDef *_hi2c_config);

//Temperature
uint8_t readOutputTemperature(I2C_HandleTypeDef *_hi2c_config);

//Read 3 axises roll - pitch - yaw
int16_t readRollValue(I2C_HandleTypeDef *_hi2c_config);
int16_t readPitchValue(I2C_HandleTypeDef *_hi2c_config);
int16_t readYawValue(I2C_HandleTypeDef *_hi2c_config);


#endif
