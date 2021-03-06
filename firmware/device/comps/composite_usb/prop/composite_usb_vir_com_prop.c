/*!
 * \file composite_usb_vir_com_prop.c
 *
 * \brief 
 *
 *
 * \date Mar 19, 2011
 * \author Dan Riedler
 *
 */

/*-----------------------------------------------------------------------------
 Includes
------------------------------------------------------------------------------*/
#include "composite_usb_vir_com_prop.h"
#include "composite_usb_hid_mouse_prop.h"

#include "desc/composite_usb_desc.h"

#include "usb/pwr/hw_usb_pwr.h"
#include "usb/core/hw_usb_core.h"
#include "usb/sil/hw_usb_sil.h"

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
uint8 Request = 0;


LINE_CODING linecoding =
{
        115200, /* baud rate*/
        0x00,   /* stop bits-1*/
        0x00,   /* parity - none*/
        0x08    /* no. of bits 8*/
};


DEVICE Device_Table =
{
        EP_NUM,
        1
};

DEVICE_PROP Device_Property =
{
        Virtual_Com_Port_init,
        Virtual_Com_Port_Reset,
        Virtual_Com_Port_Status_In,
        Virtual_Com_Port_Status_Out,
        Virtual_Com_Port_Data_Setup,
        Virtual_Com_Port_NoData_Setup,
        Virtual_Com_Port_Get_Interface_Setting,
        Virtual_Com_Port_GetDeviceDescriptor,
        Virtual_Com_Port_GetConfigDescriptor,
        Virtual_Com_Port_GetStringDescriptor,
        0,
        0x40 /*MAX PACKET SIZE*/
};

USER_STANDARD_REQUESTS User_Standard_Requests =
{
        Virtual_Com_Port_GetConfiguration,
        Virtual_Com_Port_SetConfiguration,
        Virtual_Com_Port_GetInterface,
        Virtual_Com_Port_SetInterface,
        Virtual_Com_Port_GetStatus,
        Virtual_Com_Port_ClearFeature,
        Virtual_Com_Port_SetEndPointFeature,
        Virtual_Com_Port_SetDeviceFeature,
        Virtual_Com_Port_SetDeviceAddress
};

ONE_DESCRIPTOR Device_Descriptor =
{
        (uint8*)Virtual_Com_Port_DeviceDescriptor,
        USB_DEVICE_DESCRIPTOR_SIZE
};

ONE_DESCRIPTOR Config_Descriptor =
{
        (uint8*)Virtual_Com_Port_ConfigDescriptor,
        DEVICE_CONFIGURATION_DESCRIPTOR_SIZE
};


ONE_DESCRIPTOR String_Descriptor[4] =
{
        {(uint8*)Virtual_Com_Port_StringLangID, VIRTUAL_COM_PORT_SIZ_STRING_LANGID},
        {(uint8*)Virtual_Com_Port_StringVendor, VIRTUAL_COM_PORT_SIZ_STRING_VENDOR},
        {(uint8*)Virtual_Com_Port_StringProduct, VIRTUAL_COM_PORT_SIZ_STRING_PRODUCT},
        {(uint8*)Virtual_Com_Port_StringSerial, VIRTUAL_COM_PORT_SIZ_STRING_SERIAL}
};


//*****************************************************************************
//
// Exported Functions
//
//*****************************************************************************

/*******************************************************************************
 * Function Name  : Virtual_Com_Port_init.
 * Description    : Virtual COM Port Mouse init routine.
 * Input          : None.
 * Output         : None.
 * Return         : None.
 *******************************************************************************/
void Virtual_Com_Port_init(void)
{

    /* Update the serial number string descriptor with the data from the unique
  ID*/

    pInformation->Current_Configuration = 0;

    /* Connect the device */
    PowerOn();

    USB_SIL_Init();

    /* configure the USART to the default settings */
    //USART_Config_Default();

    bDeviceState = HW_USB_STATE_UNCONNECTED;
    HW_USB_ISSUE_STATE_CHANGE_CALLBACK(bDeviceState);
}

/*******************************************************************************
 * Function Name  : Virtual_Com_Port_Reset
 * Description    : Virtual_Com_Port Mouse reset routine
 * Input          : None.
 * Output         : None.
 * Return         : None.
 *******************************************************************************/
void Virtual_Com_Port_Reset(void)
{
    /* Set Virtual_Com_Port DEVICE as not configured */
    pInformation->Current_Configuration = 0;

    /* Current Feature initialization */
    pInformation->Current_Feature = Virtual_Com_Port_ConfigDescriptor[7];

    /* Set Virtual_Com_Port DEVICE with the default Interface*/
    pInformation->Current_Interface = 0;

    SetBTABLE(BTABLE_ADDRESS);

    /* Initialize Endpoint 0 */
    SetEPType(ENDP0, EP_CONTROL);
    SetEPTxStatus(ENDP0, EP_TX_STALL);
    SetEPRxAddr(ENDP0, ENDP0_RXADDR);
    SetEPTxAddr(ENDP0, ENDP0_TXADDR);
    Clear_Status_Out(ENDP0);
    SetEPRxCount(ENDP0, Device_Property.MaxPacketSize);
    SetEPRxValid(ENDP0);


    /* Initialize Endpoint 1: HId interrupt in */
    SetEPType(ENDP1, EP_INTERRUPT);
    SetEPTxAddr(ENDP1, ENDP1_TXADDR);
    SetEPTxCount(ENDP1, HID_MOUSE_REPORT_SIZE);
    SetEPRxStatus(ENDP1, EP_RX_DIS);
    SetEPTxStatus(ENDP1, EP_TX_NAK);


    /* Initialize Endpoint 2: CDC Interrupt in */
    SetEPType(ENDP2, EP_INTERRUPT);
    SetEPTxAddr(ENDP2, ENDP2_TXADDR);
    SetEPRxStatus(ENDP2, EP_RX_DIS);
    SetEPTxStatus(ENDP2, EP_TX_NAK);

    /* Initialize Endpoint 3: CDC bulk out */
    SetEPType(ENDP3, EP_BULK);
    SetEPRxAddr(ENDP3, ENDP3_RXADDR);
    SetEPRxCount(ENDP3, VIRTUAL_COM_PORT_DATA_SIZE);
    SetEPRxStatus(ENDP3, EP_RX_VALID);
    SetEPTxStatus(ENDP3, EP_TX_DIS);

    /* Initialize Endpoint 4: CDC Bulk in */
    SetEPType(ENDP4, EP_BULK);
    SetEPTxAddr(ENDP4, ENDP4_TXADDR);
    //SetEPTxCount(ENDP4, VIRTUAL_COM_PORT_DATA_SIZE);
    SetEPTxStatus(ENDP4, EP_TX_NAK);
    SetEPRxStatus(ENDP4, EP_RX_DIS);


    /* Set this device to response on default address */
    SetDeviceAddress(0);

    bDeviceState = HW_USB_STATE_ATTACHED;
    HW_USB_ISSUE_STATE_CHANGE_CALLBACK(bDeviceState);
}

/*******************************************************************************
 * Function Name  : Virtual_Com_Port_SetConfiguration.
 * Description    : Udpade the device state to configured.
 * Input          : None.
 * Output         : None.
 * Return         : None.
 *******************************************************************************/
void Virtual_Com_Port_SetConfiguration(void)
{
    DEVICE_INFO *pInfo = &Device_Info;

    if (pInfo->Current_Configuration != 0)
    {
        /* Device configured */
        bDeviceState = HW_USB_STATE_CONFIGURED;
        HW_USB_ISSUE_STATE_CHANGE_CALLBACK(bDeviceState);
    }
}

/*******************************************************************************
 * Function Name  : Virtual_Com_Port_SetConfiguration.
 * Description    : Udpade the device state to addressed.
 * Input          : None.
 * Output         : None.
 * Return         : None.
 *******************************************************************************/
void Virtual_Com_Port_SetDeviceAddress (void)
{
    bDeviceState = HW_USB_STATE_ADDRESSED;
    HW_USB_ISSUE_STATE_CHANGE_CALLBACK(bDeviceState);
}

/*******************************************************************************
 * Function Name  : Virtual_Com_Port_Status_In.
 * Description    : Virtual COM Port Status In Routine.
 * Input          : None.
 * Output         : None.
 * Return         : None.
 *******************************************************************************/
void Virtual_Com_Port_Status_In(void)
{
    if (Request == SET_LINE_CODING)
    {
        //USART_Config();
        Request = 0;
    }
}

/*******************************************************************************
 * Function Name  : Virtual_Com_Port_Status_Out
 * Description    : Virtual COM Port Status OUT Routine.
 * Input          : None.
 * Output         : None.
 * Return         : None.
 *******************************************************************************/
void Virtual_Com_Port_Status_Out(void)
{}

/*******************************************************************************
 * Function Name  : Virtual_Com_Port_Data_Setup
 * Description    : handle the data class specific requests
 * Input          : Request Nb.
 * Output         : None.
 * Return         : USB_UNSUPPORT or USB_SUCCESS.
 *******************************************************************************/
USB_RESULT Virtual_Com_Port_Data_Setup(uint8 RequestNo)
{
    uint8    *(*CopyRoutine)(uint16);

    CopyRoutine = NULL;

    if (RequestNo == GET_LINE_CODING)
    {
        if (Type_Recipient == (CLASS_REQUEST | INTERFACE_RECIPIENT))
        {
            CopyRoutine = Virtual_Com_Port_GetLineCoding;
        }
    }
    else if (RequestNo == SET_LINE_CODING)
    {
        if (Type_Recipient == (CLASS_REQUEST | INTERFACE_RECIPIENT))
        {
            CopyRoutine = Virtual_Com_Port_SetLineCoding;
        }
        Request = SET_LINE_CODING;
    }

    else if ((RequestNo == GET_DESCRIPTOR)
            && (Type_Recipient == (STANDARD_REQUEST | INTERFACE_RECIPIENT))
            && (pInformation->USBwIndex0 == HID_IFC_NUM))
    {

        if (pInformation->USBwValue1 == HID_REPORT_DESCRIPTOR_TYPE)
        {
            CopyRoutine = CustomHID_GetReportDescriptor;
        }
        else if (pInformation->USBwValue1 == HID_HID_DESCRIPTOR_TYPE)
        {
            CopyRoutine = CustomHID_GetHIDDescriptor;
        }
    }

    else if ((RequestNo == GET_DESCRIPTOR)
            && (Type_Recipient == (STANDARD_REQUEST | INTERFACE_RECIPIENT))
            && (pInformation->USBwIndex0 == CDC_IFC_NUM))
    {

        //printf("Get CDC Desc: &d\n",pInformation->USBwValue1 );
    }

    else if ((RequestNo == GET_DESCRIPTOR)
            && (Type_Recipient == (STANDARD_REQUEST | INTERFACE_RECIPIENT))
            && (pInformation->USBwIndex0 == CDC_DATA_IFC_NUM))
    {

        //printf("Get CDC-Data Desc: &d\n",pInformation->USBwValue1 );
    }

    /* End of GET_DESCRIPTOR */

    /*** GET_PROTOCOL ***/
    else if ((Type_Recipient == (CLASS_REQUEST | INTERFACE_RECIPIENT))
            && RequestNo == GET_PROTOCOL)
    {
        CopyRoutine = CustomHID_GetProtocolValue;
    }

    if (CopyRoutine == NULL)
    {
        return USB_UNSUPPORT;
    }

    pInformation->Ctrl_Info.CopyData = CopyRoutine;
    pInformation->Ctrl_Info.Usb_wOffset = 0;
    (*CopyRoutine)(0);
    return USB_SUCCESS;
}

/*******************************************************************************
 * Function Name  : Virtual_Com_Port_NoData_Setup.
 * Description    : handle the no data class specific requests.
 * Input          : Request Nb.
 * Output         : None.
 * Return         : USB_UNSUPPORT or USB_SUCCESS.
 *******************************************************************************/
USB_RESULT Virtual_Com_Port_NoData_Setup(uint8 RequestNo)
{

    if (Type_Recipient == (CLASS_REQUEST | INTERFACE_RECIPIENT))
    {
        if (RequestNo == SET_COMM_FEATURE)
        {
            return USB_SUCCESS;
        }
        else if (RequestNo == SET_CONTROL_LINE_STATE)
        {
            return USB_SUCCESS;
        }
        else if( RequestNo == SET_PROTOCOL )
        {
            return CustomHID_SetProtocol();
        }
    }

    return USB_UNSUPPORT;
}

/*******************************************************************************
 * Function Name  : Virtual_Com_Port_GetDeviceDescriptor.
 * Description    : Gets the device descriptor.
 * Input          : Length.
 * Output         : None.
 * Return         : The address of the device descriptor.
 *******************************************************************************/
uint8 *Virtual_Com_Port_GetDeviceDescriptor(uint16 Length)
{
    //printf("getting device desc: %d\n", Length);
    return Standard_GetDescriptorData(Length, &Device_Descriptor);
}

/*******************************************************************************
 * Function Name  : Virtual_Com_Port_GetConfigDescriptor.
 * Description    : get the configuration descriptor.
 * Input          : Length.
 * Output         : None.
 * Return         : The address of the configuration descriptor.
 *******************************************************************************/
uint8 *Virtual_Com_Port_GetConfigDescriptor(uint16 Length)
{
    //printf("getting config desc: %d\n", Length);
    return Standard_GetDescriptorData(Length, &Config_Descriptor);
}

/*******************************************************************************
 * Function Name  : Virtual_Com_Port_GetStringDescriptor
 * Description    : Gets the string descriptors according to the needed index
 * Input          : Length.
 * Output         : None.
 * Return         : The address of the string descriptors.
 *******************************************************************************/
uint8 *Virtual_Com_Port_GetStringDescriptor(uint16 Length)
{
    uint8 wValue0 = pInformation->USBwValue0;
    if (wValue0 > 4)
    {
        return NULL;
    }
    else
    {
        return Standard_GetDescriptorData(Length, &String_Descriptor[wValue0]);
    }
}

/*******************************************************************************
 * Function Name  : Virtual_Com_Port_Get_Interface_Setting.
 * Description    : test the interface and the alternate setting according to the
 *                  supported one.
 * Input1         : uint8: Interface : interface number.
 * Input2         : uint8: AlternateSetting : Alternate Setting number.
 * Output         : None.
 * Return         : The address of the string descriptors.
 *******************************************************************************/
USB_RESULT Virtual_Com_Port_Get_Interface_Setting(uint8 Interface, uint8 AlternateSetting)
{
    //printf("getting ifc setting: %d\n", Interface);
    if (AlternateSetting > 0)
    {
        return USB_UNSUPPORT;
    }
    else if (Interface > (IFC_NUM-1))
    {
        return USB_UNSUPPORT;
    }
    return USB_SUCCESS;
}

/*******************************************************************************
 * Function Name  : Virtual_Com_Port_GetLineCoding.
 * Description    : send the linecoding structure to the PC host.
 * Input          : Length.
 * Output         : None.
 * Return         : Inecoding structure base address.
 *******************************************************************************/
uint8 *Virtual_Com_Port_GetLineCoding(uint16 Length)
{
    //printf("getting line codingc: %d\n", Length);
    if (Length == 0)
    {
        pInformation->Ctrl_Info.Usb_wLength = sizeof(linecoding);
        return NULL;
    }
    return(uint8 *)&linecoding;
}

/*******************************************************************************
 * Function Name  : Virtual_Com_Port_SetLineCoding.
 * Description    : Set the linecoding structure fields.
 * Input          : Length.
 * Output         : None.
 * Return         : Linecoding structure base address.
 *******************************************************************************/
uint8 *Virtual_Com_Port_SetLineCoding(uint16 Length)
{
    //printf("setting line coding: %d\n", Length);
    if (Length == 0)
    {
        pInformation->Ctrl_Info.Usb_wLength = sizeof(linecoding);
        return NULL;
    }
    return(uint8 *)&linecoding;
}

//*****************************************************************************
//
// Local Functions
//
//*****************************************************************************

