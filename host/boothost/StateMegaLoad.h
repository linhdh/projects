/****************************************************************************
*
*   Copyright (c) 2005 - 2008 Dave Hylands     <dhylands@gmail.com>
*
*   This program is free software; you can redistribute it and/or modify
*   it under the terms of the GNU General Public License version 2 as
*   published by the Free Software Foundation.
*
*   Alternatively, this software may be distributed under the terms of BSD
*   license.
*
*   See README and COPYING for more details.
*
****************************************************************************/
/**
*
*   @file   StateMegaLoad.h
*
*   @brief  Implements the state machine for dealing with the MegaLoad
*           bootloader.
*
****************************************************************************/

#if !defined( STATEMEGALOAD_H )
#define STATEMEGALOAD_H

// ---- Include Files -------------------------------------------------------

#if !defined( STATE_H )
#   include "State.h"
#endif

// ---- Constants and Types -------------------------------------------------

// ---- Variable Externs ----------------------------------------------------

// ---- Function Prototypes -------------------------------------------------

StatePtrProxy   StateMegaDeviceId( char ch );
StatePtrProxy   StateMegaDeviceInfoAck( char ch );
StatePtrProxy   StateMegaFlashSize( char ch );
StatePtrProxy   StateMegaBootSize( char ch );
StatePtrProxy   StateMegaPageSize( char ch );
StatePtrProxy   StateMegaAckNack( char ch );

#endif  // STATEMEGALOAD_H

