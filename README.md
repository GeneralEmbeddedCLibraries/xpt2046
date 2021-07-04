# XPT2046 MODULE
This module contains C library for resistive touch embedded on 3.5" SPI TFT 480x320 display. Used touch controler is XPT2046.
Module was written and tested on STM32F746 Nucleo board, using STM32CubeIDE. 

## Dependencies
XPT2046 used also diplay ILI9488 module for calibration purposes. Display module can be found under this [link](https://github.com/GeneralEmbeddedCLibraries/ili9488).

Definition of float32_t must be provided by user. In current implementation it is defined in "project_config.h". Just add following statement to your code where it suits the best.

```C
// Define float
typedef float float32_t;
```

## Usage
### 1. Setting up configuration
Display driver is fully configurable via **xpt2046_cfg.h** file. Low level interface shall be change only in **xpt2046_if.c/.h** files.

##### NOTE: When debug mode is enabled user should provide debug communication port by the choice!

### 2. Low level interface

- User shall change **xpt2046_if.c/.h** file between USER_CODE_BEGIN and USER_CODE_END sections. Template files with examples can be found in /template subdirectory.

### 3. Includes
  Only top level modules are needed, therefore single include should be provided. E.g.:
  
```C
  #include "xpt2046.h"
```

### 4. Initialization
- Initialization of tocuh driver should be done only once in project.
- User can access initilization status by calling **xpt2046_is_init()** function.
- Example of initialization routine:

```C
  // Init touch controller
  if ( eXPT2046_OK != xpt2046_init() )
  { 
    // Initialization failed, further actions here...
  }

```

### 5. Handle touch
- Touch controler (xpt2046) need to be handled every x ms in order to preserve real-time behaviour. Thus calling **xpt2046_hndl()** every x ms is mandatory.
- Example of touch handling invocation:

```C
  // Touch task or simple main loop
  @every x ms
  {
    // Handle touch controller
    xpt2046_hndl();
  }
```
- Access touch data via **xpt2046_get_touch()** function. This function only returns values from local data and doesn't interface with touch controler itself.
- Example of reading touch data:
```C
  // Touch variables
  uint16_t x_pos;
  uint16_t y_pos;
  uint16_t force;
  bool touch;
  
  // Get touch data
  xpt2046_get_touch( &x_pos, &y_pos, &force, &touch );

  // Add here furher actions based on touch data...
```

## Touch API

 - xpt2046_status_t 	**xpt2046_init**					(void);
 - bool				**xpt2046_is_init**					(void);
 - void 				**xpt2046_hndl**					(void);

 - xpt2046_status_t 	**xpt2046_get_touch**				(uint16_t * const p_page, uint16_t * const p_col, uint16_t * const p_force, bool * const p_pressed);
 - xpt2046_status_t 	**xpt2046_start_calibration**		(void);
 - bool				**xpt2046_is_calibrated**			(void);
 - void				**xpt2046_set_cal_factors**			(const int32_t * const p_factors);
 - void				**xpt2046_get_cal_factors**			(const int32_t * p_factors);
