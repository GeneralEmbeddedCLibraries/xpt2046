////////////////////////////////////////////////////////////////////////////////
/**
*@file      xpt2046.h
*@brief     Application layer function for XPT2046 chip
*@author    Ziga Miklosic
*@date      29.06.2021
*@version	V1.0.0
*/
////////////////////////////////////////////////////////////////////////////////
/**
*@addtogroup XPT2046_API
* @{ <!-- BEGIN GROUP -->
*
* 	Application layer interface with XPT2046 chip.
*/
////////////////////////////////////////////////////////////////////////////////

#ifndef _XPT2046_H_
#define _XPT2046_H_

////////////////////////////////////////////////////////////////////////////////
// Includes
////////////////////////////////////////////////////////////////////////////////
#include <stdint.h>
#include <stdbool.h>
#include "../../xpt2046_cfg.h"

////////////////////////////////////////////////////////////////////////////////
// Definitions
////////////////////////////////////////////////////////////////////////////////

/**
 * 	Module version
 */
#define XPT2046_VER_MAJOR		( 1 )
#define XPT2046_VER_MINOR		( 0 )
#define XPT2046_VER_DEVELOP		( 0 )

// General status
typedef enum
{
	eXPT2046_OK = 0,
	eXPT2046_ERROR,
	eXPT2046_CAL_IN_PROGRESS,
} xpt2046_status_t;

////////////////////////////////////////////////////////////////////////////////
// Function Prototypes
////////////////////////////////////////////////////////////////////////////////
xpt2046_status_t 	xpt2046_init					(void);
bool				xpt2046_is_init					(void);
void 				xpt2046_hndl					(void);

xpt2046_status_t 	xpt2046_get_touch				(uint16_t * const p_page, uint16_t * const p_col, uint16_t * const p_force, bool * const p_pressed);
xpt2046_status_t 	xpt2046_start_calibration		(void);
bool				xpt2046_is_calibrated			(void);
void				xpt2046_set_cal_factors			(const int32_t * const p_factors);
void				xpt2046_get_cal_factors			(const int32_t * p_factors);

#endif // _XPT2046_H_
