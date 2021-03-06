/*!
 * \file settings_mgr.h
 *
 * \brief 
 *
 *
 * \date Apr 3, 2011
 * \author Dan Riedler
 *
 */

#ifndef _SETTINGS_MGR_H_
#define _SETTINGS_MGR_H_

/*-----------------------------------------------------------------------------
 Includes
------------------------------------------------------------------------------*/
#include "device.h"
#include "comps.h"
#include "settings_mgr_result.h"
#include "settings_mgr_entry.h"
#include "settings_mgr/feeprom/feeprom.h"

/*-----------------------------------------------------------------------------
 Defines
------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 Macros
------------------------------------------------------------------------------*/
#define SETTINGS_MGR_Write(_key, _data, _size, _flags) FEEPROM_Write( (FEEPROM_EntryKey)_key, (void*)_data, _size, (FEEPROM_EntryFlag)_flags);

#define SETTINGS_MGR_Read(_key, _data, _size, _bytes_read) FEEPROM_Read( (FEEPROM_EntryKey)_key, (void*)_data, _size, _bytes_read);


/*-----------------------------------------------------------------------------
 Typedefs
------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 Exported Function Prototypes
------------------------------------------------------------------------------*/
PUBLIC ModuleInitPrototype SETTINGS_MGR_Init;

PUBLIC ModulePowerUpPrototype SETTINGS_MGR_PowerUp;

PUBLIC ModulePowerDownPrototype SETTINGS_MGR_PowerDown;


/*-----------------------------------------------------------------------------
 External Data Members
------------------------------------------------------------------------------*/


#endif /* SETTINGS_MGR_H_ */
