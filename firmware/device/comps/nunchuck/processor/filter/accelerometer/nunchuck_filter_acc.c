/*!
 * \file nunchuck_filter_acc.c
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
#include "nunchuck_filter_acc.h"


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

//*****************************************************************************//

// TODO: actually filter the acclerometer data
PROTECTED void NunchuckFilterAccelerometerData( void )
{
    uint8 newest;

    newest = NunchuckRawData.NextPoint - 1;
    if(newest > NunchuckRawData.TotalDataPtCount) newest = NunchuckRawData.TotalDataPtCount - 1;

    CopyMemory(&NunchuckProcessedData.Data.Accelerometer, &NunchuckRawData.DataPts[newest].Accelerometer, sizeof(NunchuckAccelerometerData));
}


//*****************************************************************************
//
// Local Functions
//
//*****************************************************************************
