/****************************************************************************************
|  Description: bootloader callback source file
|    File Name: hooks.c
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
#include "stm32f10x.h"                           /* microcontroller registers          */


/****************************************************************************************
*   B A C K D O O R   E N T R Y   H O O K   F U N C T I O N S
****************************************************************************************/

#if (BOOT_BACKDOOR_HOOKS_ENABLE > 0)
/****************************************************************************************
** NAME:           BackDoorInitHook
** PARAMETER:      none
** RETURN VALUE:   none
** DESCRIPTION:    Initializes the backdoor entry option.
**
****************************************************************************************/
void BackDoorInitHook(void)
{
  /* enable clock for PA0 pin peripheral (GPIOA) */
  RCC->APB2ENR |= (blt_int32u)(0x00000004);
  /* configure BUT (GPIOA0) as floating digital input */
  /* first reset the configuration */
  GPIOA->CRL &= ~(blt_int32u)((blt_int32u)0xf << 0);
  /* CNF0[1:0] = %01 and MODE0[1:0] = %00 */
  GPIOA->CRL |= (blt_int32u)((blt_int32u)0x4 << 0);
} /*** end of BackDoorInitHook ***/


/****************************************************************************************
** NAME:           BackDoorEntryHook
** PARAMETER:      none
** RETURN VALUE:   BLT_TRUE if the backdoor entry is requested, BLT_FALSE otherwise.
** DESCRIPTION:    Checks if a backdoor entry is requested.
**
****************************************************************************************/
blt_bool BackDoorEntryHook(void)
{
  /* button PA0 has a pullup, so will read high by default. enter backdoor only when
   * this button is pressed. this is the case when it reads low */

  if ((GPIOA->IDR & ((blt_int32u)0x01)) == 0)
  {
    return BLT_TRUE;
  }
  return BLT_FALSE;
} /*** end of BackDoorEntryHook ***/
#endif /* BOOT_BACKDOOR_HOOKS_ENABLE > 0 */


/****************************************************************************************
*   C P U   D R I V E R   H O O K   F U N C T I O N S
****************************************************************************************/

#if (BOOT_CPU_USER_PROGRAM_START_HOOK > 0)
/****************************************************************************************
** NAME:           CpuUserProgramStartHook
** PARAMETER:      none
** RETURN VALUE:   BLT_TRUE if it is okay to start the user program, BLT_FALSE to keep
**                 keep the bootloader active.
** DESCRIPTION:    Callback that gets called when the bootloader is about to exit and
**                 hand over control to the user program. This is the last moment that
**                 some final checking can be performed and if necessary prevent the
**                 bootloader from activiting the user program.
**
****************************************************************************************/
blt_bool CpuUserProgramStartHook(void)
{
  /* okay to start the user program */
  return BLT_TRUE;
} /*** end of CpuUserProgramStartHook ***/
#endif /* BOOT_CPU_USER_PROGRAM_START_HOOK > 0 */



/*********************************** end of hooks.c ************************************/
