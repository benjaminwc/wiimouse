/******************** (C) COPYRIGHT 2010 STMicroelectronics ********************
* File Name          : usb_sil.h
* Author             : MCD Application Team
* Version            : V3.2.1
* Date               : 07/05/2010
* Description        : Simplified Interface Layer function prototypes.
********************************************************************************
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __USB_SIL_H
#define __USB_SIL_H

#include "stm32f10x_type.h"

/* Includes ------------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

uint32 USB_SIL_Init(void);
uint32 USB_SIL_Write(uint8 bEpAddr, uint8* pBufferPointer, uint32 wBufferSize);
uint32 USB_SIL_Read(uint8 bEpAddr, uint8* pBufferPointer);

/* External variables --------------------------------------------------------*/

#endif /* __USB_SIL_H */

/******************* (C) COPYRIGHT 2010 STMicroelectronics *****END OF FILE****/
