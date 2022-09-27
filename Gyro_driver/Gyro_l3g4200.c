#include "Gyro_l3g4200.h"

/**
 * @brief read default name 0b11010011 from register 0x0F
 * @param _hi2c_config is a pointer received hi2cx configuration
 * @return 0b11010011  
 */
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

/**
 * @brief used to read any 8bit register inside device
 * @param _hi2c_config is a pointer received hi2cx configuration
 * @param regAddr is the register's address to be read
 * @return read register's value
 */
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
 * @brief Control Register 1
 * DR1	|	DR0	|	BW1	|	BW0	|	PD	|	ZEN	|	YEN	|	XEN
 * DR1:0  -> Output Data Rate selection
 * BW1:0 -> Bandwidth selection
 * PD 0: -> power down mode, 1: normal mode or sleep mode
 * ZEN YEN XEN -> enable XYZ axis
 * @param _hi2c_config is a pointer received hi2cx configuration
 * @return value of Control Register 1
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

/**
 * @brief Control Register 2
 * 0	|	0	|	HPM1	|	HPM0	|	HPCF3	|	HPCF2	|	HPCF1	|	HPCF0
 * 0  -> loaded value at boot, do not change
 * HPM1:0  -> High Pass filter Mode Selection. Default value: 00
 * HPCF3:0  -> High Pass filter Cut Off frequency selection
 * @param _hi2c_config is a pointer received hi2cx configuration
 * @return value of Control Register 2 
 */
uint8_t readControlRegister2(I2C_HandleTypeDef *_hi2c_config)
{
	uint8_t _pData= 0;
	HAL_I2C_Mem_Read(_hi2c_config,
			DEVICE_I2C_ADR,
			DEVICE_CTRL_REG_2,
			I2C_MEMADD_SIZE_8BIT,
			&_pData,
			1,
			0xFF);
	return _pData;
}

/**
 * @brief Control Register 3
 * I1_Int1	|	 I1_Boot	|	H_Lactive	|	 PP_OD	|	I2_DRDY	|	 I2_WTM	|	 I2_ORun	|	 I2_Empty
 * I1_Int1  -> Interrupt enable on INT1 pin. Default value 0. (0: Disable; 1: Enable)
 * I1_Boot  ->  Boot status available on INT1. Default value 0. (0: Disable; 1: Enable)
 * H_Lactive  ->  Interrupt active configuration on INT1. Default value 0. (0: High; 1:Low)
 * PP_OD  ->  Push- Pull / Open drain. Default value: 0. (0: Push- Pull; 1: Open drain)
 * I2_DRDY  ->  Date Ready on DRDY/INT2. Default value 0. (0: Disable; 1: Enable)
 * I2_WTM  ->  FIFO Watermark interrupt on DRDY/INT2. Default value: 0. (0: Disable; 1: Enable)
 * I2_ORun  ->  FIFO Overrun interrupt on DRDY/INT2 Default value: 0. (0: Disable; 1: Enable)
 * I2_Empty  ->  FIFO Empty interrupt on DRDY/INT2. Default value: 0. (0: Disable; 1: Enable)
 * @param _hi2c_config is a pointer received hi2cx configuration
 * @return value of Control Register 3 
 */
uint8_t readControlRegister3(I2C_HandleTypeDef *_hi2c_config)
{
	uint8_t _pData= 0;
	HAL_I2C_Mem_Read(_hi2c_config,
			DEVICE_I2C_ADR,
			DEVICE_CTRL_REG_3,
			I2C_MEMADD_SIZE_8BIT,
			&_pData,
			1,
			0xFF);
	return _pData;
}

/**
 * @brief Control Register 4
 * BDU	|	 BLE	|	 FS1	|	  FS0	|	_	|	  ST1	|	  ST0	|	 SIM
 * BDU  -> Block Data Update. Default 0
			(0: continous update; 1: output registers not updated until MSB and LSB reading)
 * BLE  ->  Big/Little Endian Data Selection. Default value 0.
			(0: Data LSB @ lower address; 1: Data MSB @ lower address)
 * FS1:0  ->   Full Scale selection. Default value: 00
				(00: 250 dps; 01: 500 dps; 10: 2000 dps; 11: 2000 dps)
 * ST1:0  ->  Self Test Enable. Default value: 00 
				(00: Self Test Disabled)
 * SIM  ->  SPI Serial Interface Mode selection. Default value: 0 
			(0: 4-wire interface; 1: 3-wire interface)
 * @param _hi2c_config is a pointer received hi2cx configuration
 * @return value of Control Register 4 
 */
uint8_t readControlRegister4(I2C_HandleTypeDef *_hi2c_config)
{
	uint8_t _pData= 0;
	HAL_I2C_Mem_Read(_hi2c_config,
			DEVICE_I2C_ADR,
			DEVICE_CTRL_REG_4,
			I2C_MEMADD_SIZE_8BIT,
			&_pData,
			1,
			0xFF);
	return _pData;
}

/**
 * @brief Control Register 5
 * BOOT	|	 FIFO_EN	|	 _	|	   HPen	|	 INT1_Sel1	|	  INT1_Sel0	|	   Out_Sel1	|	  Out_Sel0
 * BOOT  -> Reboot memory content. Default value: 0
			(0: normal mode; 1: reboot memory content)
 * FIFO_EN  -> FIFO enable. Default value: 0
				(0: FIFO disable; 1: FIFO Enable)
 * HPen  ->  High Pass filter Enable. Default value: 0
			(0: HPF disabled; 1: HPF enabled
 * INT1_Sel1:0  ->  INT1 selection configuration. Default value: 0
 * Out_Sel1:0  ->  Out selection configuration. Default value: 0
 * @param _hi2c_config is a pointer received hi2cx configuration
 * @return value of Control Register 5 
 */
uint8_t readControlRegister5(I2C_HandleTypeDef *_hi2c_config)
{
	uint8_t _pData= 0;
	HAL_I2C_Mem_Read(_hi2c_config,
			DEVICE_I2C_ADR,
			DEVICE_CTRL_REG_5,
			I2C_MEMADD_SIZE_8BIT,
			&_pData,
			1,
			0xFF);
	return _pData;
}

/**
 * @brief Status_register contains bits to indicate 
 * 		whenever X/Y/Z axis datas are available and  axis data overrun 
 * ZYXOR	|	ZOR	|	YOR	|	XOR	|	ZYXDA	|	ZDA	|	YDA	|	XDA
 * ZYXOR  -> X, Y, Z -axis data overrun. Default value: 0
 * ZOR  -> Z axis data overrun. Default value: 0
 * YOR  -> Y axis data overrun. Default value: 0
 * XOR  -> X axis data overrun. Default value: 0
 * ZYXDA  -> X, Y, Z -axis new data available. Default value: 0
 * ZDA  -> Z axis new data available. Default value: 0
 * YDA  -> Y axis new data available. Default value: 0
 * XDA  -> X axis new data available. Default value: 0
 * @param _hi2c_config is a pointer received hi2cx configuration
 * @return register's value 
 */
uint8_t readStatusRegister(I2C_HandleTypeDef *_hi2c_config)
{
	uint8_t _pData= 0;
	HAL_I2C_Mem_Read(_hi2c_config,
			DEVICE_I2C_ADR,
			DEVICE_STATUS_REG,
			I2C_MEMADD_SIZE_8BIT,
			&_pData,
			1,
			0xFF);
	return _pData;
}

/**
 * @brief change device's mode
 * to change from power-down mode to normal mode, device requires at least 250ms
 * After changing, fucntion return Control_register_1 to check current mode
 * @param _setDeviceMode Operation mode will be change to
 * @param _hi2c_config is a pointer received hi2cx configuration
 * @return  Control_register_1
 */
uint8_t setDeviceMode(enum deviceOperationMode _setDeviceMode,
					I2C_HandleTypeDef *_hi2c_config)
{
	uint8_t readCtrlReg1=readControlRegister1(_hi2c_config);
	uint8_t sendCtrlReg1=0;
	uint8_t _pdBit= (readCtrlReg1 >> 3) & 0x1;
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
		//should use osDelay or a timer delay
		HAL_Delay(300);
	}
	readCtrlReg1=readControlRegister1(_hi2c_config);
	return readCtrlReg1;
}

/**
 * @brief Set the Device Into Normal Mode
 * @param _hi2c_config is a pointer received hi2cx configuration
 * @return Control_register_1 
 */
uint8_t setDeviceIntoNormal(I2C_HandleTypeDef *_hi2c_config)
{
	uint8_t readCtrlReg1= 0;
	uint8_t _pData= 0x0F;
	HAL_I2C_Mem_Write(_hi2c_config,
						DEVICE_I2C_ADR,
						DEVICE_CTRL_REG_1,
						I2C_MEMADD_SIZE_8BIT,
						&_pData,
						1,
						0xFF);
	//return CTRL_REG_1 after changing mode
	readCtrlReg1=readControlRegister1(_hi2c_config);
	return readCtrlReg1;
}

/**
 * @brief Set the Device into Sleep Mode by changing 3 bits 0:1:2 in Ctrl_Reg_1 to zero
 * @param _hi2c_config is a pointer received hi2cx configuration
 * @return Control_register_1 
 */
uint8_t setDeviceIntoModeSleep(I2C_HandleTypeDef *_hi2c_config)
{
	uint8_t readCtrlReg1= readControlRegister1(_hi2c_config);
	uint8_t _pData= readCtrlReg1 & 0xF8; //0b11111000
	HAL_I2C_Mem_Write(_hi2c_config,
						DEVICE_I2C_ADR,
						DEVICE_CTRL_REG_1,
						I2C_MEMADD_SIZE_8BIT,
						&_pData,
						1,
						0xFF);
	//return CTRL_REG_1 after changing mode
	readCtrlReg1=readControlRegister1(_hi2c_config);
	return readCtrlReg1;
}

/**
 * @brief Set the Device into Sleep Mode by changing 4 bits 0:1:2:3 in Ctrl_Reg_1 to zero
 * @param _hi2c_config is a pointer received hi2cx configuration
 * @return Control_register_1 
 */
uint8_t setDeviceIntoModeShutdown(I2C_HandleTypeDef *_hi2c_config)
{
	uint8_t readCtrlReg1= readControlRegister1(_hi2c_config);
	uint8_t _pData= readCtrlReg1 & 0xF0; //0b11110000
	HAL_I2C_Mem_Write(_hi2c_config,
						DEVICE_I2C_ADR,
						DEVICE_CTRL_REG_1,
						I2C_MEMADD_SIZE_8BIT,
						&_pData,
						1,
						0xFF);
	//return CTRL_REG_1 after changing mode
	readCtrlReg1=readControlRegister1(_hi2c_config);
	return readCtrlReg1;
}

/**
 * @brief Set the Watermark Level base on the parameter input, max 31 in decimal
 * 
 * @param _hi2c_config is a pointer received hi2cx configuration
 * @param _levelInput is the watermark 5 bits level will be set
 * @return value of FIFO_CONTROL_REGISTER which contains set watermark 
 */
uint8_t setWatermarkLevel(I2C_HandleTypeDef *_hi2c_config, uint8_t _levelInput)
{
	uint8_t _readFifoCtrlReg = readRegister(_hi2c_config, DEVICE_FIFO_CTRL_REG);
	uint8_t _pData = (_readFifoCtrlReg & 0b11100000) | _levelInput;
	HAL_I2C_Mem_Write(_hi2c_config,
							DEVICE_I2C_ADR,
							DEVICE_CTRL_REG_1,
							I2C_MEMADD_SIZE_8BIT,
							&_pData,
							1,
							0xFF);
	_readFifoCtrlReg = readRegister(_hi2c_config, DEVICE_FIFO_CTRL_REG);
	return _readFifoCtrlReg;
}

/**
 * @brief enable FIFO buffer bit in CONTROL_REGISTER_5
 * @param _hi2c_config is a pointer received hi2cx configuration
 * @return CONTROL_REGISTER_5  
 */
uint8_t setFIFOEnable(I2C_HandleTypeDef *_hi2c_config)
{
	uint8_t _readCtrlReg5 = readControlRegister5(_hi2c_config);
	uint8_t _sendCtrlReg5 = _readCtrlReg5 | 0x40;
	HAL_I2C_Mem_Write(_hi2c_config,
					DEVICE_I2C_ADR,
					DEVICE_CTRL_REG_5,
					I2C_MEMADD_SIZE_8BIT,
					&_sendCtrlReg5,
					1,
					0xFF);
	_readCtrlReg5 = readControlRegister5(_hi2c_config);
	return _readCtrlReg5;
}

/**
 * @brief Set the Bufffer Mode object
 * @param _setBufferMode is the buffer to be set
 * @param _hi2c_config is a pointer received hi2cx configuration
 * @return FIFO_CONTROL_REGISTER 
 */
uint8_t setBuffferMode(enum bufferOperationMode _setBufferMode,
					I2C_HandleTypeDef *_hi2c_config)
{
	uint8_t _setMode=0;
	uint8_t _readFifoCtrlReg=0;
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
	_readFifoCtrlReg = readRegister(_hi2c_config, DEVICE_FIFO_CTRL_REG);
	return _readFifoCtrlReg;
}

/**
 * @brief check full FIFO indicated bit in FIFO_SOURCE_CONTROL_REG
 * @param _hi2c_config is a pointer received hi2cx configuration
 * @return indicated bit 
 */
uint8_t isFIFOstoreFull(I2C_HandleTypeDef *_hi2c_config)
{
	uint8_t _indicateBit=0;
	uint8_t _readData=0;
	_readData=readRegister(_hi2c_config, DEVICE_FIFO_SRC_REG);
	_indicateBit = (_readData & 0b01000000)>>6;
	return _indicateBit;
}

/**
 * @brief check empty FIFO indicated bit FIFO_SOURCE_CONTROL_REG
 * @param _hi2c_config is a pointer received hi2cx configuration
 * @return indicated bit 
 */
uint8_t isFIFOstoreEmpty(I2C_HandleTypeDef *_hi2c_config)
{
	uint8_t _indicateBit=0;
	uint8_t _readData=0;
	_readData=readRegister(_hi2c_config, DEVICE_FIFO_SRC_REG);
	_indicateBit = (_readData & 0b00100000)>>5;
	return _indicateBit;
}

/**
 * @brief read internal temperature
 * @param _hi2c_config is a pointer received hi2cx configuration
 * @return internal temperature 
 */
uint8_t readOutputTemperature(I2C_HandleTypeDef *_hi2c_config)
{
	uint8_t _pData= 0;
	HAL_I2C_Mem_Read(_hi2c_config,
			DEVICE_I2C_ADR,
			DEVICE_OUT_TEMP,
			I2C_MEMADD_SIZE_8BIT,
			&_pData, 
			1,
			0xFF);
	return _pData;
}

/**
 * @brief read value of Y axis
 * @param _hi2c_config is a pointer received hi2cx configuration
 * @return value of Y axis
 */
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

/**
 * @brief read value of X axis
 * @param _hi2c_config is a pointer received hi2cx configuration
 * @return value of X axis
 */
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

/**
 * @brief read value of Z axis
 * @param _hi2c_config is a pointer received hi2cx configuration
 * @return value of Z axis
 */
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
