/*!
 * \file comps_conf.h
 *
 * \brief 
 *
 *
 * \date Mar 18, 2011
 * \author Dan Riedler
 *
 */

#ifndef _COMPS_CONF_H_
#define _COMPS_CONF_H_

/*-----------------------------------------------------------------------------
 Includes
------------------------------------------------------------------------------*/
#include "device_conf.h"


#ifdef DEV_MOD_COMPS

/*-----------------------------------------------------------------------------
 Defines
------------------------------------------------------------------------------*/

/*!
 * \brief This defines which component modules to use
 */
#define COMPS_MOD_SETTINGS_MGR
#define COMPS_MOD_NUNCHUCK
#define COMPS_MOD_COMPOSITE_USB
#define COMPS_MOD_PACKET_MGR


/*-----------------------------------------------------------------------------
 Macros
------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 Typedefs
------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 Exported Function Prototypes
------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 External Data Members
------------------------------------------------------------------------------*/

#endif

#endif /* COMPS_CONF_H_ */
