/*!
 * \file nunchuck_profile.c
 *
 * \brief 
 *
 *
 * \date Apr 9, 2011
 * \author Dan Riedler
 *
 */

/*-----------------------------------------------------------------------------
 Includes
------------------------------------------------------------------------------*/
#include "nunchuck_profile.h"
#include "nunchuck/nunchuck_conf.h"


/*-----------------------------------------------------------------------------
 Defines
------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 Macros
------------------------------------------------------------------------------*/
#define ADD_PROFILE(_slave_addr, _formatter, _use_encryption)                   \
{                                                                               \
    _slave_addr,                                                                \
    _formatter,                                                                 \
    _use_encryption                                                             \
}


/*-----------------------------------------------------------------------------
 Typedefs
------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 Local Function Prototypes
------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 Data Members
------------------------------------------------------------------------------*/


PROTECTED NunchuckProfileInfo NunchuckProfiles[NUNCHUCK_PROFILE_COUNT] = {
        ADD_PROFILE(0xA4, NunchuckProfileFormatterXOR_17_Plus17, TRUE)
};




//*****************************************************************************
//
// Exported Functions
//
//*****************************************************************************

PROTECTED uint8 NunchuckProfileFormatterXOR_17_Plus17(uint8 PacketData)
{
	return (PacketData^0x17)+ 0x17;
}

//*****************************************************************************
//
// Local Functions
//
//*****************************************************************************

