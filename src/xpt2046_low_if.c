////////////////////////////////////////////////////////////////////////////////
/**
*@file      xpt2046_low_if.c
*@brief     Low level interface with XPT2046 chip
*@author    Ziga Miklosic
*@date      29.06.2021
*@version	V1.0.0
*/
////////////////////////////////////////////////////////////////////////////////
/**
*@addtogroup XPT2046_LOW_IF
* @{ <!-- BEGIN GROUP -->
*
* 	Low level interface with XPT2046 chip.
*/
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Includes
////////////////////////////////////////////////////////////////////////////////
#include "stm32f7xx_hal.h"

#include "xpt2046_low_if.h"
#include "../../xpt2046_cfg.h"

#include "drivers/peripheral/spi/spi.h"
#include "drivers/peripheral/gpio/gpio.h"

// For memcpy
#include "string.h"

////////////////////////////////////////////////////////////////////////////////
// Definitions
////////////////////////////////////////////////////////////////////////////////

// Control frame
typedef union
{
	struct
	{
		uint8_t pd 			: 2;	// Power down
		uint8_t ser_dfr 	: 1;	// Reference mode
		uint8_t mode		: 1;	// ADC resolution
		uint8_t addr		: 3;	// Address
		uint8_t source		: 1;	// Source (always 1)
	} bits;
	uint8_t U;
} xpt2046_control_t;

// Conversion result
typedef union
{
	struct
	{
		uint16_t res0	 	: 3;
#if ( 0 == XPT2046_ADC_RESOLUTION )
		uint16_t adc_result	: 12;	// ADC result
		uint16_t res1		: 1;
#else
		uint16_t adc_result	: 8;	// ADC result
		uint16_t res1		: 7;
#endif
	} bits;
	uint16_t U;
} xpt2046_result_t;

// SPI interface status
typedef enum
{
	eXPT2046_SPI_OK = 0,
	eXPT2046_SPI_ERROR,
} xpt2046_spi_status_t;

// SPI interface
typedef xpt2046_spi_status_t (*pf_spi_exchange_t) (const uint8_t * p_tx_data, uint8_t * const p_rx_data, const uint32_t size);

// CS
#define XPT2046_LOW_IF_CS_LOW()			( HAL_GPIO_WritePin( XPT2046_CS__PORT, XPT2046_CS__PIN, GPIO_PIN_RESET ))
#define XPT2046_LOW_IF_CS_HIGH()		( HAL_GPIO_WritePin( XPT2046_CS__PORT, XPT2046_CS__PIN, GPIO_PIN_SET ))


////////////////////////////////////////////////////////////////////////////////
// Variables
////////////////////////////////////////////////////////////////////////////////

/*// Spi exchange function
static pf_spi_exchange_t gpf_spi_exchange;*/

/*// SPI handler
static SPI_HandleTypeDef gh_touch_spi;*/

////////////////////////////////////////////////////////////////////////////////
// Function prototypes
////////////////////////////////////////////////////////////////////////////////
/*static void 				xpt2046_low_if_gpio_init	(void);
static xpt2046_status_t 	xpt2046_low_if_spi_init		(void);*/

//static xpt2046_spi_status_t	xpt2046_low_if_spi_exchange	(const uint8_t * p_tx_data, uint8_t * const p_rx_data, const uint32_t size);

////////////////////////////////////////////////////////////////////////////////
// Functions
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
/**
*		Low level interface initialization
*
* @return 	status - Status of operation
*/
////////////////////////////////////////////////////////////////////////////////
xpt2046_status_t xpt2046_low_if_init(void)
{
	xpt2046_status_t status = eXPT2046_OK;

/*
	// Init GPIOs
	xpt2046_low_if_gpio_init();

	// Init SPI
	if ( eXPT2046_OK != xpt2046_low_if_spi_init())
	{
		status = eXPT2046_ERROR;
	}
*/

	return status;
}

////////////////////////////////////////////////////////////////////////////////
/**
*		Spi GPIO init
*
* @return 	void
*/
////////////////////////////////////////////////////////////////////////////////
/*
static void xpt2046_low_if_gpio_init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};

	// Enable clock
	XPT2046_SCK_CLK_EN();
	XPT2046_MOSI_CLK_EN();
	XPT2046_MISO_CLK_EN();
	XPT2046_CS_CLK_EN();
	XPT2046_INT_CLK_EN();

	// SPI pins
    GPIO_InitStruct.Pin 		= XPT2046_SCK__PIN;
    GPIO_InitStruct.Mode 		= GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull 		= XPT2046_SCK__PULL;
    GPIO_InitStruct.Speed 		= GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate 	= GPIO_AF6_SPI3;
    HAL_GPIO_Init( XPT2046_SCK__PORT, &GPIO_InitStruct );

    GPIO_InitStruct.Pin 		= XPT2046_MOSI__PIN;
    GPIO_InitStruct.Mode 		= GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull 		= XPT2046_MOSI__PULL;
    GPIO_InitStruct.Speed 		= GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate 	= GPIO_AF6_SPI3;
    HAL_GPIO_Init( XPT2046_MOSI__PORT, &GPIO_InitStruct );

    GPIO_InitStruct.Pin 		= XPT2046_MISO__PIN;
    GPIO_InitStruct.Mode 		= GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull 		= XPT2046_MISO__PULL;
    GPIO_InitStruct.Speed 		= GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate 	= GPIO_AF6_SPI3;
    HAL_GPIO_Init( XPT2046_MISO__PORT, &GPIO_InitStruct );

	// CS pin
	GPIO_InitStruct.Pin			= XPT2046_CS__PIN;
	GPIO_InitStruct.Mode		= GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull		= XPT2046_CS__PULL;
	GPIO_InitStruct.Speed		= GPIO_SPEED_MEDIUM;
	HAL_GPIO_Init( XPT2046_CS__PORT, &GPIO_InitStruct );
	XPT2046_LOW_IF_CS_HIGH();

	// INT pin
	GPIO_InitStruct.Pin 		= XPT2046_INT__PIN;
	GPIO_InitStruct.Mode 		= GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull 		= XPT2046_INT__PULL;
	HAL_GPIO_Init( XPT2046_INT__PORT, &GPIO_InitStruct );
}
*/

////////////////////////////////////////////////////////////////////////////////
/**
*		SPI initialiaztion
*
* @return 		status - Status of operation
*/
////////////////////////////////////////////////////////////////////////////////
/*static xpt2046_status_t xpt2046_low_if_spi_init(void)
{
	xpt2046_status_t status = eXPT2046_OK;

	// Enable clock
	XPT2046_SPI_EN_CLK();

	// Init SPI
	gh_touch_spi.Instance 				= XPT2046_SPI;
	gh_touch_spi.Init.Mode 				= SPI_MODE_MASTER;
	gh_touch_spi.Init.Direction 		= SPI_DIRECTION_2LINES;
	gh_touch_spi.Init.DataSize 			= SPI_DATASIZE_8BIT;
	gh_touch_spi.Init.CLKPolarity 		= SPI_POLARITY_LOW;
	gh_touch_spi.Init.CLKPhase 			= SPI_PHASE_1EDGE;
	gh_touch_spi.Init.NSS 				= SPI_NSS_SOFT;
	gh_touch_spi.Init.BaudRatePrescaler = XPT2046_SPI_BAUDRATE_PSC;
	gh_touch_spi.Init.FirstBit 			= SPI_FIRSTBIT_MSB;
	gh_touch_spi.Init.TIMode 			= SPI_TIMODE_DISABLE;
	gh_touch_spi.Init.CRCCalculation 	= SPI_CRCCALCULATION_DISABLE;
	gh_touch_spi.Init.CRCPolynomial 	= 7;
	gh_touch_spi.Init.CRCLength 		= SPI_CRC_LENGTH_DATASIZE;
	gh_touch_spi.Init.NSSPMode 			= SPI_NSS_PULSE_ENABLE;

	if ( HAL_OK != HAL_SPI_Init( &gh_touch_spi ))
	{
		status = eXPT2046_ERROR;
		gpf_spi_exchange = NULL;

		XPT2046_DBG_PRINT( "Touch SPI init failed! ");
		XPT2046_ASSERT( 0 );
	}
	else
	{
		gpf_spi_exchange = &xpt2046_low_if_spi_exchange;
	}

	return status;
}*/

////////////////////////////////////////////////////////////////////////////////
/**
*		SPI exchange data
*
*	@param[in]	p_tx_data 	- Pointer to transmit data
*	@param[in]	p_rx_data 	- Pointer to receive data
*	@param[in]	size 		- Size of exhange data in bytes
*	@return		status 		- Status of operation
*/
////////////////////////////////////////////////////////////////////////////////
/*static xpt2046_spi_status_t	xpt2046_low_if_spi_exchange	(const uint8_t * p_tx_data, uint8_t * const p_rx_data, const uint32_t size)
{
	xpt2046_spi_status_t status = eXPT2046_SPI_OK;

	if ( HAL_OK != HAL_SPI_TransmitReceive( &gh_touch_spi, (uint8_t*) p_tx_data, (uint8_t*) p_rx_data, size, XPT2046_SPI_TIMEOUT_MS ))
	{
		status = eXPT2046_SPI_ERROR;
	}

	return status;
}*/

////////////////////////////////////////////////////////////////////////////////
/**
*		Low level interface exchange
*
* @param[in]	addr 			- Address of operation
* @param[in]	pd_mode 		- Power down mode
* @param[in]	start 			- Start bit
* @param[in]	p_adc_result 	- Pointer to measurement result
* @return 		status 			- Status of operation
*/
////////////////////////////////////////////////////////////////////////////////
xpt2046_status_t xpt2046_low_if_exchange(const xpt2046_addr_t addr, const xpt2046_pd_t pd_mode, const xpt2046_start_t start, uint16_t * const p_adc_result)
{
	xpt2046_status_t status = eXPT2046_OK;
	xpt2046_control_t control;
	xpt2046_result_t result;
	uint8_t rx_data[3];
	uint8_t tx_data[3];
	uint16_t rx_data_w;

	// Assemble frame
	control.U = 0;
	control.bits.source 	= start;
	control.bits.addr 		= addr;
	control.bits.mode 		= XPT2046_ADC_RESOLUTION;
	control.bits.ser_dfr 	= XPT2046_REF_MODE;
	control.bits.pd			= pd_mode;

	// Copy assemble frame
	tx_data[0] = control.U;

	// Interface with the device
	// TODO: Move to if...
	spi_2_transmit_receive( eSPI2_CH_TOUCH, (uint8_t*) &tx_data, (uint8_t*) &rx_data, 3U, ( eSPI_CS_LOW_ON_ENTRY | eSPI_CS_HIGH_ON_EXIT ));

	// NOTE: Big endian
	rx_data_w = ( rx_data[1] << 8 ) | ( rx_data[2] );

	// Parse received frame
	memcpy( &result.U, &rx_data_w, 2U );

	// Set result
	*p_adc_result = result.bits.adc_result;

	return status;
}

////////////////////////////////////////////////////////////////////////////////
/**
*		Get status of touch
*
* @return 		touch_int - Status of touch interrupt
*/
////////////////////////////////////////////////////////////////////////////////
xpt2046_int_t xpt2046_low_if_get_int(void)
{
	xpt2046_int_t touch_int;

	// TODO: Move to if

	// HW inverter used
	if ( eGPIO_HIGH == gpio_get( eGPIO_T_IRQ ))
	{
		touch_int = eXPT2046_INT_ON;
	}
	else
	{
		touch_int = eXPT2046_INT_OFF;
	}

	return touch_int;
}

////////////////////////////////////////////////////////////////////////////////
/**
* @} <!-- END GROUP -->
*/
////////////////////////////////////////////////////////////////////////////////

