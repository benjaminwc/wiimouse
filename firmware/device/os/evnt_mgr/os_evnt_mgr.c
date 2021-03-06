/*!
 * \file os_evnt_mgr.c
 *
 * \brief 
 *
 *
 * \date Mar 6, 2011
 * \author Dan Riedler
 *
 */

/*-----------------------------------------------------------------------------
 Includes
------------------------------------------------------------------------------*/
#include "os_evnt_mgr.h"
#include "list/lib_array_list.h"

#ifdef OS_MOD_EVNT_MGR

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
PRIVATE pLIB_ARRAY_LIST_List EventLists[OS_EVNT_MGR_EVENT_ID_COUNT];

//*****************************************************************************
//
// Exported Functions
//
//*****************************************************************************

/******************************************************************************/
PROTECTED Result EVNT_MGR_Init( void )
{
    //Result result = HW_MGR_RESULT_INIT();

    LOG_Printf("Initializing EventMgr\n");

    ZeroMemory(EventLists, sizeof(pLIB_ARRAY_LIST_List)*OS_EVNT_MGR_EVENT_ID_COUNT);

    LOG_RegisterModule(MOD_MGR_OS, OS_EVNT_MGR, TRUE);


    return OS_EVNT_MGR_RESULT(SUCCESS);
}


/******************************************************************************/
PUBLIC Result OS_EVNT_MGR_RegisterEventListener( OS_EVNT_MGR_EvntId EventId, pOS_EVNT_MGR_EventListener Listener)
{

    Result result = OS_EVNT_MGR_RESULT(SUCCESS);

    if( EventId > OS_EVNT_MGR_EVENT_ID_COUNT )
    {
        result = OS_EVNT_MGR_RESULT(INVALID_EVENT_ID);
    }
    else if( Listener == NULL )
    {
        result = OS_EVNT_MGR_RESULT(NULL_LISTENER);
    }
    else if( EventLists[EventId] == NULL &&
            (EventLists[EventId] = LIB_ARRAY_LIST_CreateList(sizeof(pOS_EVNT_MGR_EventListener), OS_EVNT_MGR_EVENT_LIST_INIT_SIZE)) == NULL )
    {
        result = OS_EVNT_MGR_RESULT(CREATE_EVENT_LIST_FAIL);
    }
    else if( LIB_ARRAY_LIST_AddItem(EventLists[EventId], Listener) < 0 )
    {
        result = OS_EVNT_MGR_RESULT(ADD_EVENT_TO_LIST_FAIL);
    }

    return result;
}



/******************************************************************************/
PUBLIC Result OS_EVNT_MGR_GenerateEvent( OS_EVNT_MGR_EvntId EventId, void* Parameters )
{
    if( EventId > OS_EVNT_MGR_EVENT_ID_COUNT )
    {
        return OS_EVNT_MGR_RESULT(INVALID_EVENT_ID);
    }

    if( EventLists[EventId] == NULL )
    {
        return OS_EVNT_MGR_RESULT(NO_LISTENERS);
    }
    else
    {
        uint32 i, cnt;
        pOS_EVNT_MGR_EventListener listener;

        cnt = LIB_ARRAY_LIST_ListSize(EventLists[EventId]);

        for( i = 0; i < cnt; i++ )
        {
            listener = (pOS_EVNT_MGR_EventListener)LIB_ARRAY_LIST_GetItemAtPosition(EventLists[EventId], i);
            listener(Parameters);
        }
    }

    return OS_EVNT_MGR_RESULT(SUCCESS);
}

//*****************************************************************************
//
// Local Functions
//
//*****************************************************************************

#endif
