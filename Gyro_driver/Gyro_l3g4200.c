#include "Gyro_l3g4200.h"
uint8_t readDeviceName(I2C_HandleTypeDef *_hi2c_config)
{
	uint8_t _pData[1];
	HAL_I2C_Mem_Read(_hi2c_config, DIVICE_I2C_ADR, DEVICE_NAME, I2C_MEMADD_SIZE_8BIT, _pData, 1, 0xFF);
	return _pData[0];
}
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
uint8_t readReference(void);

void setDeviceMode(enum deviceOperationMode setDeviceMode)
{
	switch (setDeviceMode)
	{
	case Mode_Normal:
		break;
	case Mode_Shutdown:
		break;
	case Mode_Sleep:
		break;
	}
}
void setWatermarkLevel(uint8_t _levelInput);
void setDeviceIntoModeSleep(void);
void setDeviceIntoModeShutdown(void);

void setBuffferMode(uint8_t _bufferMode)
{

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
