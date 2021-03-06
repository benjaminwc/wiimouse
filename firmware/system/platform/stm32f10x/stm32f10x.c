/*!
 * \file stm32f10x.c
 *
 * \brief 
 *
 *
 * \date Apr 29, 2011
 * \author Dan Riedler
 *
 */

/*-----------------------------------------------------------------------------
 Includes
------------------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "cortexm3_macro.h"

/*-----------------------------------------------------------------------------
 Defines
------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 Macros
------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 Typedefs
------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 Local Function Prototypes
------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 Data Members
------------------------------------------------------------------------------*/


//*****************************************************************************
//
// Exported Functions
//
//*****************************************************************************


/******************************************************************************/
inline void SetMainStackPointer( uint32 Value )
{
    __MSR_MSP(Value);
}

//*****************************************************************************
//
// Local Functions
//
//*****************************************************************************

