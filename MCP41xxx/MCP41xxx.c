/*

  ******************************************************************************
  * @file 			( фаил ):   MCP41xxx.c
  * @brief 		( описание ):  	
  ******************************************************************************
  * @attention 	( внимание ):	author: Golinskiy Konstantin	e-mail: golinskiy.konstantin@gmail.com
  ******************************************************************************
  
*/

/* Includes ----------------------------------------------------------*/
#include "MCP41xxx.h"

/*
	******************************************************************************
	* @brief	 ( описание ):  отправка данных в SPI
	* @param	( параметры ):	данные ( 2 байта )
	* @return  ( возвращает ):	

	******************************************************************************
*/
static inline void MCP41xxx_sendSpi( uint8_t* value ){
	
	#ifdef CS_PORT
		HAL_GPIO_WritePin(CS_GPIO_Port, CS_Pin, GPIO_PIN_RESET );
	#endif
	
	HAL_SPI_Transmit( &MCP41XXX_SPI_HAL, value, 2, HAL_MAX_DELAY );
	
	#ifdef CS_PORT
		HAL_GPIO_WritePin(CS_GPIO_Port, CS_Pin, GPIO_PIN_SET );
	#endif
	
}
//----------------------------------------------------------------------------------

/*
	******************************************************************************
	* @brief	 ( описание ):  отправка данных в потенциометр 
								( от 0 до 255 -> движение происходит от PB0 до PA0 )
	* @param	( параметры ):	1 - номер потонциометра 
										POTENTIOMETER_ONE,POTENTIOMETER_TWO,POTENTIOMETER_BOTH
								2 - данные ( от 0 до 255 -> движение происходит от PB0 до PA0 )
	* @return  ( возвращает ):	

	******************************************************************************
*/
void MCP41xxx_sendValue( Potentiometer num, uint8_t value ){
	
	// переменная где [0] будем хранить настройки потенциометра ( команды )
	// переменная где [1] будем хранить значение данных потенциометра ( данные от 0 до 255 )
	uint8_t MCP41xxx_value[2];
	
	switch( (uint8_t)num ){
		
		case POTENTIOMETER_ONE:
			MCP41xxx_value[0] = MCP41XXX_WRITE_DATA	| MCP41XXX_POTENT_0;
		break;
		
		case POTENTIOMETER_TWO:
			MCP41xxx_value[0] = MCP41XXX_WRITE_DATA	| MCP41XXX_POTENT_1;
		break;
		
		case POTENTIOMETER_BOTH:
			MCP41xxx_value[0] = MCP41XXX_WRITE_DATA	| MCP41XXX_POTENT_0_AND_1;
		break;
		
		default:
			MCP41xxx_value[0] = MCP41XXX_WRITE_DATA	| MCP41XXX_POTENT_0_AND_1;
		break;
		
	}

	MCP41xxx_value[1] = value;
	
	MCP41xxx_sendSpi( MCP41xxx_value );
}
//----------------------------------------------------------------------------------

/*
	******************************************************************************
	* @brief	 ( описание ): 	отключает потенциометр потребление <1 мкА в статическом режиме
								сопротивление ползунка становится в самом начале к контакту PB0
	* @param	( параметры ):	номер потонциометра 
										POTENTIOMETER_ONE,POTENTIOMETER_TWO,POTENTIOMETER_BOTH
	* @return  ( возвращает ):	

	******************************************************************************
*/
void MCP41xxx_potentiometerOff( Potentiometer num ){
	
	// переменная где [0] будем хранить настройки потенциометра ( команды )
	// переменная где [1] будем хранить значение данных потенциометра ( данные от 0 до 255 )
	uint8_t MCP41xxx_off[2];
	
	switch( (uint8_t)num ){
		
		case POTENTIOMETER_ONE:
			MCP41xxx_off[0] = MCP41XXX_OFF | MCP41XXX_POTENT_0;
		break;
		
		case POTENTIOMETER_TWO:
			MCP41xxx_off[0] = MCP41XXX_OFF | MCP41XXX_POTENT_1;
		break;
		
		case POTENTIOMETER_BOTH:
			MCP41xxx_off[0] = MCP41XXX_OFF | MCP41XXX_POTENT_0_AND_1;
		break;
		
		default:
			MCP41xxx_off[0] = MCP41XXX_OFF | MCP41XXX_POTENT_0_AND_1;
		break;
		
	}

	MCP41xxx_off[1] = 0;
	
	MCP41xxx_sendSpi( MCP41xxx_off );
}
//----------------------------------------------------------------------------------

/************************ (C) COPYRIGHT GKP *****END OF FILE****/
