/*!
 * \file comps_modules.c
 *
 * \brief 
 *
 *
 * \date Mar 18, 2011
 * \author Dan Riedler
 *
 */

/*-----------------------------------------------------------------------------
 Includes
------------------------------------------------------------------------------*/
#include "device.h"

#ifdef DEV_MOD_COMPS


#include "comps_modules.h"

#include "settings_mgr/settings_mgr.h"
#include "composite_usb/composite_usb.h"
#include "packet_mgr/packet_mgr.h"
#include "nunchuck/nunchuck.h"


/*-----------------------------------------------------------------------------
 Defines
------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 Macros
------------------------------------------------------------------------------*/
#define ADD_COMPS_MODULE(_name)         \
{                                       \
    COMPS_##_name,                      \
    &_name##_PowerUp,                   \
    &_name##_PowerDown,                 \
    &_name##_Init,                      \
    &_name##_GetResultCodeStr,          \
    FALSE,                              \
    FALSE                               \
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
CompsModules compsModules[COMPS_MODULE_COUNT] = {
#ifdef COMPS_MOD_SETTINGS_MGR
        ADD_COMPS_MODULE(SETTINGS_MGR),
#endif
#ifdef COMPS_MOD_COMPOSITE_USB
        ADD_COMPS_MODULE(COMPOSITE_USB),
#endif
#ifdef COMPS_MOD_PACKET_MGR
        ADD_COMPS_MODULE(PACKET_MGR),
#endif
#ifdef COMPS_MOD_NUNCHUCK
        ADD_COMPS_MODULE(NUNCHUCK),
#endif
};



//*****************************************************************************
//
// Exported Functions
//
//*****************************************************************************



//*****************************************************************************
//
// Local Functions
//
//*****************************************************************************


#endif
