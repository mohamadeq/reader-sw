/**
 * @file    hal_custom.c
 * @brief   Custom HAL subsystem code.
 *
 * @addtogroup HAL_CUSTOM
 * @{
 */

#include "hal.h"
#include "hal_custom.h"

#if (HAL_USE_CUSTOM == TRUE) || defined(__DOXYGEN__)

/*===========================================================================*/
/* Driver local definitions.                                                 */
/*===========================================================================*/

/*===========================================================================*/
/* Driver exported variables.                                                */
/*===========================================================================*/

/*===========================================================================*/
/* Driver local variables and types.                                         */
/*===========================================================================*/

/*===========================================================================*/
/* Driver local functions.                                                   */
/*===========================================================================*/

/*===========================================================================*/
/* Driver exported functions.                                                */
/*===========================================================================*/

/**
 * @brief   HAL initialization (custom part).
 *
 * @init
 */
void halCustomInit(void) {

}

#endif /* HAL_USE_CUSTOM */

/** @} */
