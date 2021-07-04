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
#include "xpt2046_low_if.h"
#include "../../xpt2046_cfg.h"
#include "../../xpt2046_if.h"

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

////////////////////////////////////////////////////////////////////////////////
// Variables
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Function prototypes
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Functions
////////////////////////////////////////////////////////////////////////////////

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
	status = xpt2046_if_spi_transmit_receive((uint8_t*) &tx_data, (uint8_t*) &rx_data, 3U, ( eSPI_CS_LOW_ON_ENTRY | eSPI_CS_HIGH_ON_EXIT ));

	if ( eXPT2046_OK == status )
	{
		// NOTE: Big endian
		rx_data_w = ( rx_data[1] << 8 ) | ( rx_data[2] );

		// Parse received frame
		memcpy( &result.U, &rx_data_w, 2U );

		// Set result
		*p_adc_result = result.bits.adc_result;
	}

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

	if ( true == xpt2046_if_get_int())
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
