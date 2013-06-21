/****************************************************************************************
|  Description: bootloader non-volatile memory driver source file
|    File Name: nvm.c
|
|----------------------------------------------------------------------------------------
|                          C O P Y R I G H T
|----------------------------------------------------------------------------------------
|   Copyright (c) 2011  by Feaser    http://www.feaser.com    All rights reserved
|
|----------------------------------------------------------------------------------------
|                            L I C E N S E
|----------------------------------------------------------------------------------------
| This file is part of OpenBLT. OpenBLT is free software: you can redistribute it and/or
| modify it under the terms of the GNU General Public License as published by the Free
| Software Foundation, either version 3 of the License, or (at your option) any later
| version.
|
| OpenBLT is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
| without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
| PURPOSE. See the GNU General Public License for more details.
|
| You should have received a copy of the GNU General Public License along with OpenBLT.
| If not, see <http://www.gnu.org/licenses/>.
|
| A special exception to the GPL is included to allow you to distribute a combined work 
| that includes OpenBLT without being obliged to provide the source code for any 
| proprietary components. The exception text is included at the bottom of the license
| file <license.html>.
| 
****************************************************************************************/

/****************************************************************************************
* Include files
****************************************************************************************/
#include "boot.h"                                /* bootloader generic header          */

/****************************************************************************************
** NAME:           NvmInit
** PARAMETER:      none
** RETURN VALUE:   none
** DESCRIPTION:    Initializes the NVM driver. 
**
****************************************************************************************/
void NvmInit(void)
{
  /* init the internal driver */
  FlashInit();
} /*** end of NvmInit ***/


/****************************************************************************************
** NAME:           NvmWrite
** PARAMETER:      addr start address
**                 len  length in bytes
**                 data pointer to the data buffer.
** RETURN VALUE:   BLT_TRUE if successful, BLT_FALSE otherwise.
** DESCRIPTION:    Programs the non-volatile memory.
**
****************************************************************************************/
blt_bool NvmWrite(blt_addr addr, blt_int32u len, blt_int8u *data)
{
  /* still here so the internal driver should try and perform the program operation */
  return FlashWrite(addr, len, data);
} /*** end of NvmWrite ***/


/****************************************************************************************
** NAME:           NvmErase
** PARAMETER:      addr start address
**                 len  length in bytes
** RETURN VALUE:   BLT_TRUE if successful, BLT_FALSE otherwise.
** DESCRIPTION:    Erases the non-volatile memory.
**
****************************************************************************************/
blt_bool NvmErase(blt_addr addr, blt_int32u len)
{
  /* still here so the internal driver should try and perform the erase operation */
  return FlashErase(addr, len);
} /*** end of NvmErase ***/


/****************************************************************************************
** NAME:           NvmVerifyChecksum
** PARAMETER:      none
** RETURN VALUE:   BLT_TRUE is successful, BTL_FALSE otherwise.
** DESCRIPTION:    Verifies the checksum, which indicates that a valid user program is
**                 present and can be started.
**
****************************************************************************************/
blt_bool NvmVerifyChecksum(void)
{
  /* check checksum */
  return FlashVerifyChecksum();
} /*** end of NvmVerifyChecksum ***/


/****************************************************************************************
** NAME:           NvmDone
** PARAMETER:      none
** RETURN VALUE:   BLT_TRUE is successful, BLT_FALSE otherwise.
** DESCRIPTION:    Once all erase and programming operations are completed, this 
**                 function is called, so at the end of the programming session and 
**                 right before a software reset is performed. It is used to calculate
**                 a checksum and program this into flash. This checksum is later used
**                 to determine if a valid user program is present in flash. 
**
****************************************************************************************/
blt_bool NvmDone(void)
{
  /* compute and write checksum, which is programmed by the internal driver */
  if (FlashWriteChecksum() == BLT_FALSE)
  {
    return BLT_FALSE;
  }
  /* finish up internal driver operations */
  return FlashDone();
} /*** end of NvmDone ***/


/*********************************** end of nvm.c **************************************/
