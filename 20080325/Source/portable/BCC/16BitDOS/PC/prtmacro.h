/*
	FreeRTOS.org V4.7.2 - Copyright (C) 2003-2008 Richard Barry.

	This file is part of the FreeRTOS.org distribution.

	FreeRTOS.org is free software; you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation; either version 2 of the License, or
	(at your option) any later version.

	FreeRTOS.org is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with FreeRTOS.org; if not, write to the Free Software
	Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

	A special exception to the GPL can be applied should you wish to distribute
	a combined work that includes FreeRTOS.org, without being obliged to provide
	the source code for any proprietary components.  See the licensing section 
	of http://www.FreeRTOS.org for full details of how and when the exception
	can be applied.

	***************************************************************************

	Please ensure to read the configuration and relevant port sections of the 
	online documentation.

	+++ http://www.FreeRTOS.org +++
	Documentation, latest information, license and contact details.  

	+++ http://www.SafeRTOS.com +++
	A version that is certified for use in safety critical systems.

	+++ http://www.OpenRTOS.com +++
	Commercial support, development, porting, licensing and training services.

	***************************************************************************
*/

#ifndef PORTMACRO_H
#define PORTMACRO_H

/*-----------------------------------------------------------
 * Port specific definitions.  
 *
 * The settings in this file configure FreeRTOS correctly for the
 * given hardware and compiler.
 *
 * These settings should not be altered.
 *-----------------------------------------------------------
 */

/* Type definitions. */
#define portCHAR		char
#define portFLOAT		long
#define portDOUBLE		long
#define portLONG		long
#define portSHORT		int
#define portSTACK_TYPE	unsigned portSHORT
#define portBASE_TYPE	portSHORT

#if( configUSE_16_BIT_TICKS == 1 )
	typedef unsigned portSHORT portTickType;
	#define portMAX_DELAY ( portTickType ) 0xffff
#else
	typedef unsigned portLONG portTickType;
	#define portMAX_DELAY ( portTickType ) 0xffffffff
#endif
/*-----------------------------------------------------------*/

/* Critical section management. */
#define portENTER_CRITICAL()			__asm{ pushf }  \
										__asm{ cli 	 }	\

#define portEXIT_CRITICAL()				__asm{ popf }

#define portDISABLE_INTERRUPTS()		__asm{ cli }

#define portENABLE_INTERRUPTS()			__asm{ sti }
/*-----------------------------------------------------------*/

/* Hardware specifics. */
#define portNOP()				__asm{ nop }
#define portSTACK_GROWTH		( -1 )
#define portSWITCH_INT_NUMBER 	0x80
#define portYIELD()				__asm{ int portSWITCH_INT_NUMBER } 
#define portDOS_TICK_RATE		( 18.20648 )
#define portTICK_RATE_MS		( ( portTickType ) 1000 / configTICK_RATE_HZ )		
#define portTICKS_PER_DOS_TICK	( ( unsigned portSHORT ) ( ( ( portDOUBLE ) configTICK_RATE_HZ / portDOS_TICK_RATE ) + 0.5 ) )
#define portINITIAL_SW			( ( portSTACK_TYPE ) 0x0202 )	/* Start the tasks with interrupts enabled. */
/*-----------------------------------------------------------*/

/* Compiler specifics. */
#define portINPUT_BYTE( xAddr )				inp( xAddr )
#define portOUTPUT_BYTE( xAddr, ucValue )	outp( xAddr, ucValue )
#define inline
/*-----------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site. */
#define portTASK_FUNCTION_PROTO( vTaskFunction, pvParameters ) void vTaskFunction( void *pvParameters )
#define portTASK_FUNCTION( vTaskFunction, pvParameters ) void vTaskFunction( void *pvParameters )

#endif /* PORTMACRO_H */
