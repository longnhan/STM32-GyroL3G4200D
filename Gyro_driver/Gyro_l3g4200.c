#include "Gyro_l3g4200.h"
uint8_t readDeviceName(I2C_HandleTypeDef *_hi2c_config)
{
	uint8_t _pData[1];
	HAL_I2C_Mem_Read(_hi2c_config, DIVICE_I2C_ADR, DEVICE_NAME, I2C_MEMADD_SIZE_8BIT, _pData, 1, 0xFF);
	return _pData[0];
}

/**
 * Control Register 1
 * DR1	|	DR0	|	BW1	|	BW0	|	PD	|	ZEN	|	YEN	|	XEN
 * DR1:0  -> Output Data Rate selection
 * BW1:0 -> Bandwidth selection
 * PD 0: -> power down mode, 1: normal mode or sleep mode
 * ZEN YEN XEN -> enable XYZ axis
 */
uint8_t readControlRegister1(I2C_HandleTypeDef *_hi2c_config)
{
	uint8_t _pData[1];
	HAL_I2C_Mem_Read(_hi2c_config, DIVICE_I2C_ADR, DEVICE_CTRL_REG_1, I2C_MEMADD_SIZE_8BIT, _pData, 1, 0xFF);
	return _pData[0];

}
uint8_t readControlRegister2(I2C_HandleTypeDef *_hi2c_config)
{
	uint8_t _pData[1];
	HAL_I2C_Mem_Read(_hi2c_config, DIVICE_I2C_ADR, DEVICE_CTRL_REG_2, I2C_MEMADD_SIZE_8BIT, _pData, 1, 0xFF);
	return _pData[0];
}
uint8_t readControlRegister3(I2C_HandleTypeDef *_hi2c_config)
{
	uint8_t _pData[1];
	HAL_I2C_Mem_Read(_hi2c_config, DIVICE_I2C_ADR, DEVICE_CTRL_REG_3, I2C_MEMADD_SIZE_8BIT, _pData, 1, 0xFF);
	return _pData[0];
}
uint8_t readControlRegister4(I2C_HandleTypeDef *_hi2c_config)
{
	uint8_t _pData[1];
	HAL_I2C_Mem_Read(_hi2c_config, DIVICE_I2C_ADR, DEVICE_CTRL_REG_4, I2C_MEMADD_SIZE_8BIT, _pData, 1, 0xFF);
	return _pData[0];
}
uint8_t readControlRegister5(I2C_HandleTypeDef *_hi2c_config)
{
	uint8_t _pData[1];
	HAL_I2C_Mem_Read(_hi2c_config, DIVICE_I2C_ADR, DEVICE_CTRL_REG_5, I2C_MEMADD_SIZE_8BIT, _pData, 1, 0xFF);
	return _pData[0];
}

uint8_t readReference(void)
{

}

void setDeviceMode(enum deviceOperationMode _setDeviceMode, I2C_HandleTypeDef *_hi2c_config)
{
	uint8_t readCtrlReg1=readControlRegister1(_hi2c_config);
	uint8_t sendCtrlReg1=0;
	uint8_t _pdBit= (readCtrlReg1 >> 3) & 0x1;
	switch (_setDeviceMode)
	{
	case Device_Mode_Normal:
		if(_pdBit == 0)
		{
			sendCtrlReg1 = readCtrlReg1 | 0b00001000;
		}
		else
		{
			sendCtrlReg1 = readCtrlReg1 & 0xFF;
		}
		break;
	case Device_Mode_Sleep:
		if(_pdBit == 0)
		{
			sendCtrlReg1 = (readCtrlReg1 | 0b00001000) & 0b11111000;
		}
		else
		{
			sendCtrlReg1 = readCtrlReg1 & 0b11111000;
		}
		break;
	case Device_Mode_Shutdown:
		sendCtrlReg1 = readCtrlReg1 & 0b11110111;
		break;
		HAL_I2C_Mem_Write(_hi2c_config,
						DIVICE_I2C_ADR,
						DEVICE_CTRL_REG_1,
						I2C_MEMADD_SIZE_8BIT,
						&sendCtrlReg1,
						1,
						0xFF);
	}
}
void setWatermarkLevel(uint8_t _levelInput);
void setDeviceIntoModeSleep(void);
void setDeviceIntoModeShutdown(void);

void setBuffferMode(enum bufferOperationMode _setBufferMode)
{
	switch (_setBufferMode)
	{
	case Buffer_Mode_Bypass:
		break;
	case Buffer_Mode_FIFO:
		break;
	case Buffer_Mode_Stream:
		break;
	case Buffer_Mode_Bypass_2_Stream:
		break;
	case Stream_2_FIFO:
		break;
	}
}
void setBufferModeBypass(void)
{

}
void setBufferModeFifo(void)
{

}
void setBufferModeStream(void)
{

}
void setBufferModeBypass_2_Stream(void);
void setBufferModeStream_2_Fifo(void);
