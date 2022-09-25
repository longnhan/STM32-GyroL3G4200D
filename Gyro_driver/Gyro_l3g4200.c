#include "Gyro_l3g4200.h"
uint8_t readDeviceName(I2C_HandleTypeDef *_hi2c_config)
{
	uint8_t _pData=0;;
	HAL_I2C_Mem_Read(_hi2c_config,
			DEVICE_I2C_ADR,
			DEVICE_NAME,
			I2C_MEMADD_SIZE_8BIT,
			&_pData,
			1,
			0xFF);
	return _pData;
}

uint8_t readRegister(I2C_HandleTypeDef *_hi2c_config,
						uint8_t regAddr)
{
	uint8_t _pdata=0;
	HAL_I2C_Mem_Read(_hi2c_config,
					DEVICE_I2C_ADR,
					regAddr,
					I2C_MEMADD_SIZE_8BIT,
					&_pdata,
					1,
					0xFF);
	return _pdata;
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
	uint8_t _pData=0;
	HAL_I2C_Mem_Read(_hi2c_config,
			DEVICE_I2C_ADR,
			DEVICE_CTRL_REG_1,
			I2C_MEMADD_SIZE_8BIT,
			&_pData,
			1,
			0xFF);
	return _pData;
}
uint8_t readControlRegister2(I2C_HandleTypeDef *_hi2c_config)
{
	uint8_t _pData[1]={};
	HAL_I2C_Mem_Read(_hi2c_config, DEVICE_I2C_ADR, DEVICE_CTRL_REG_2, I2C_MEMADD_SIZE_8BIT, _pData, 1, 0xFF);
	return _pData[0];
}
uint8_t readControlRegister3(I2C_HandleTypeDef *_hi2c_config)
{
	uint8_t _pData[1]={};
	HAL_I2C_Mem_Read(_hi2c_config, DEVICE_I2C_ADR, DEVICE_CTRL_REG_3, I2C_MEMADD_SIZE_8BIT, _pData, 1, 0xFF);
	return _pData[0];
}
uint8_t readControlRegister4(I2C_HandleTypeDef *_hi2c_config)
{
	uint8_t _pData[1]={};
	HAL_I2C_Mem_Read(_hi2c_config, DEVICE_I2C_ADR, DEVICE_CTRL_REG_4, I2C_MEMADD_SIZE_8BIT, _pData, 1, 0xFF);
	return _pData[0];
}
uint8_t readControlRegister5(I2C_HandleTypeDef *_hi2c_config)
{
	uint8_t _pData[1]={};
	HAL_I2C_Mem_Read(_hi2c_config, DEVICE_I2C_ADR, DEVICE_CTRL_REG_5, I2C_MEMADD_SIZE_8BIT, _pData, 1, 0xFF);
	return _pData[0];
}

/**
 * ZYXOR	|	ZOR	|	YOR	|	XOR	|	ZYXDA	|	ZDA	|	YDA	|	XDA	|
 */
uint8_t readStatusRegister(I2C_HandleTypeDef *_hi2c_config)
{
	uint8_t _pData[1]={};
	HAL_I2C_Mem_Read(_hi2c_config,
			DEVICE_I2C_ADR,
			DEVICE_STATUS_REG,
			I2C_MEMADD_SIZE_8BIT,
			_pData,
			1,
			0xFF);
	return _pData[0];
}

void setDeviceMode(enum deviceOperationMode _setDeviceMode, I2C_HandleTypeDef *_hi2c_config)
{
	uint8_t readCtrlReg1=readControlRegister1(_hi2c_config);
	uint8_t sendCtrlReg1=0;
	uint8_t _pdBit= (readCtrlReg1 >> 3) & 0x1;
	//setup information to be sent
	switch (_setDeviceMode)
	{
	case Device_Mode_Normal:
		if(_pdBit == 0)
		{
			sendCtrlReg1 = readCtrlReg1 | 0b00001001;
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
						DEVICE_I2C_ADR,
						DEVICE_CTRL_REG_1,
						I2C_MEMADD_SIZE_8BIT,
						&sendCtrlReg1,
						1,
						0xFF);
		//at least device needed 250ms to change from shutdown to normal mode
		//fucntion here to wait for device get into normal mode
		HAL_Delay(300);

	}
}

void setDeviceIntoNormal(I2C_HandleTypeDef *_hi2c_config)
{
	uint8_t _pData=0x0F;
	HAL_I2C_Mem_Write(_hi2c_config,
						DEVICE_I2C_ADR,
						DEVICE_CTRL_REG_1,
						I2C_MEMADD_SIZE_8BIT,
						&_pData,
						1,
						0xFF);
	HAL_Delay(300);
}

void setDeviceIntoModeSleep(void);
void setDeviceIntoModeShutdown(void);
void setWatermarkLevel(uint8_t _levelInput);

//buffer controlling
void setFIFOEnable(I2C_HandleTypeDef *_hi2c_config)
{
	uint8_t readCtrlReg5 = readControlRegister5(_hi2c_config);
	uint8_t sendCtrlReg5 = readCtrlReg5 | 0x40;
	HAL_I2C_Mem_Write(_hi2c_config,
					DEVICE_I2C_ADR,
					DEVICE_CTRL_REG_5,
					I2C_MEMADD_SIZE_8BIT,
					&sendCtrlReg5,
					1,
					0xFF);
}

void setBuffferMode(enum bufferOperationMode _setBufferMode,
					I2C_HandleTypeDef *_hi2c_config)
{
	uint8_t _setMode=0;
	switch (_setBufferMode)
	{
	case Buffer_Mode_Bypass:
		_setMode = 0b00011111;
		break;
	case Buffer_Mode_FIFO:
		_setMode = 0b00111111;
		break;
	case Buffer_Mode_Stream:
		_setMode = 0b01011111;
		break;
	case Buffer_Mode_Bypass_2_Stream:
		_setMode = 0b01111111;
		break;
	case Stream_2_FIFO:
		_setMode = 0b10011111;
		break;
	}
	HAL_I2C_Mem_Write(_hi2c_config,
					DEVICE_I2C_ADR,
					DEVICE_FIFO_CTRL_REG,
					I2C_MEMADD_SIZE_8BIT,
					&_setMode,
					1,
					0xFF);
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
void setBufferModeBypass_2_Stream(void)
{

}
void setBufferModeStream_2_Fifo(void)
{

}

uint8_t isFIFOstoreFull(I2C_HandleTypeDef *_hi2c_config)
{
	uint8_t _indicateBit=0;
	uint8_t _readData=0;
	_readData=readRegister(_hi2c_config, DEVICE_FIFO_SRC_REG);
	_indicateBit = (_readData & 0b01000000)>>6;
	return _indicateBit;
}
uint8_t isFIFOstoreEmpty(I2C_HandleTypeDef *_hi2c_config)
{
	uint8_t _indicateBit=0;
	uint8_t _readData=0;
	_readData=readRegister(_hi2c_config, DEVICE_FIFO_SRC_REG);
	_indicateBit = (_readData & 0b00100000)>>5;
	return _indicateBit;
}
uint8_t readOutputTemperature(I2C_HandleTypeDef *_hi2c_config)
{
	uint8_t _pData[1];
	HAL_I2C_Mem_Read(_hi2c_config,
			DEVICE_I2C_ADR,
			DEVICE_OUT_TEMP,
			I2C_MEMADD_SIZE_8BIT,
			_pData, 1,
			0xFF);
	return _pData[0];
}

//Y axis
int16_t readRollValue(I2C_HandleTypeDef *_hi2c_config)
{
	uint8_t _bitDataAvailable=0;
	uint8_t _bitDataOverrun=0;
	uint8_t _upperData=0;
	uint8_t _lowerData=0;
	int16_t _rollValue=0;
	//check if Y-axis data is available
	_bitDataAvailable = (readStatusRegister(_hi2c_config) & 0x2) >> 1;
	// check when overrun occurs
	_bitDataOverrun = (readStatusRegister(_hi2c_config) & 0x20) >>5;
	if(_bitDataAvailable == 1 && _bitDataOverrun == 1)
	{
		_upperData = readRegister(_hi2c_config, DEVICE_OUT_Y_H_REG);
		_lowerData = readRegister(_hi2c_config, DEVICE_OUT_Y_L_REG);
		//data proccessing
		_rollValue = ((uint16_t)_upperData << 8) | (uint16_t)_lowerData;

	}
	return _rollValue;
}
//X axis
int16_t readPitchValue(I2C_HandleTypeDef *_hi2c_config)
{
	uint8_t _bitDataAvailable=0;
	uint8_t _bitDataOverrun=0;
	uint8_t _upperData=0;
	uint8_t _lowerData=0;
	int16_t _pitchValue=0;
	//check if X-axis data is available
	_bitDataAvailable = (readStatusRegister(_hi2c_config) & 0x1);
	// check when overrun occurs
	_bitDataOverrun = (readStatusRegister(_hi2c_config) & 0x10) >>4;
	if(_bitDataAvailable == 1 && _bitDataOverrun == 1)
	{
		_upperData = readRegister(_hi2c_config, DEVICE_OUT_X_H_REG);
		_lowerData = readRegister(_hi2c_config, DEVICE_OUT_X_L_REG);
		//data proccessing
		_pitchValue = ((uint16_t)_upperData << 8) | (uint16_t)_lowerData;

	}
	return _pitchValue;
}
//Z axis
int16_t readYawValue(I2C_HandleTypeDef *_hi2c_config)
{
	uint8_t _bitDataAvailable=0;
	uint8_t _bitDataOverrun=0;
	uint8_t _upperData=0;
	uint8_t _lowerData=0;
	int16_t _yawValue=0;
	//check if X-axis data is available
	_bitDataAvailable = (readStatusRegister(_hi2c_config) & 0x4)>>2;
	// check when overrun occurs
	_bitDataOverrun = (readStatusRegister(_hi2c_config) & 0x40) >>6;
	if(_bitDataAvailable == 1 && _bitDataOverrun == 1)
	{
		_upperData = readRegister(_hi2c_config, DEVICE_OUT_Z_H_REG);
		_lowerData = readRegister(_hi2c_config, DEVICE_OUT_Z_L_REG);
		//data proccessing
		_yawValue = ((uint16_t)_upperData << 8) | (uint16_t)_lowerData;

	}
	return _yawValue;
}
