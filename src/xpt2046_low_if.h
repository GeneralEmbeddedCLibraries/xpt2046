////////////////////////////////////////////////////////////////////////////////
/**
*@file      xpt2046_low_if.h
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

#ifndef _XPT2046_LOW_IF_H_
#define _XPT2046_LOW_IF_H_

////////////////////////////////////////////////////////////////////////////////
// Includes
////////////////////////////////////////////////////////////////////////////////
#include "xpt2046.h"

////////////////////////////////////////////////////////////////////////////////
// Definitions
////////////////////////////////////////////////////////////////////////////////

// Address list
typedef enum
{
	eXPT2046_ADDR_TEMP_0 = 0,
	eXPT2046_ADDR_Y_POS,
	eXPT2046_ADDR_VBAT,
	eXPT2046_ADDR_Z1_POS,
	eXPT2046_ADDR_YN,		// YN is also Z2
	eXPT2046_ADDR_X_POS,
	eXPT2046_ADDR_AUX_IN,
	eXPT2046_ADDR_TEMP_1,

	eXPT2046_ADDR_NUM_OF,
} xpt2046_addr_t;

// Power down mode
typedef enum
{
	eXPT2046_PD_POWER_DOWN = 0,
	eXPT2046_PD_VREF_OFF,
	eXPT2046_PD_VREF_ON,
	eXPT2046_PD_DEVICE_FULLY_ON,
} xpt2046_pd_t;

// Interrupt line
typedef enum
{
	eXPT2046_INT_ON = 0,
	eXPT2046_INT_OFF,
} xpt2046_int_t;

// Start
typedef enum
{
	eXPT2046_START_OFF = 0,
	eXPT2046_START_ON
} xpt2046_start_t;

////////////////////////////////////////////////////////////////////////////////
// Function Prototypes
////////////////////////////////////////////////////////////////////////////////
xpt2046_status_t 	xpt2046_low_if_exchange	(const xpt2046_addr_t addr, const xpt2046_pd_t pd_mode, const xpt2046_start_t start, uint16_t * const p_adc_result);
xpt2046_int_t 		xpt2046_low_if_get_int	(void);

#endif // _XPT2046_LOW_IF_H_
