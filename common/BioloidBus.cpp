/****************************************************************************
*
*   Copyright (c) 2009 Dave Hylands     <dhylands@gmail.com>
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
*   @file   BioloidBus.cpp
*
*   @brief  This file implements the BioloidBus class, which is an 
*           abstract base class for the hardware which actually talks
*   to the bioloid bus. This hardware usually takes the form of a UART.
*
****************************************************************************/

// ---- Include Files -------------------------------------------------------

#include "Log.h"
#include "Bioloid.h"
#include "BioloidBus.h"
#include "BioloidDevice.h"

// ---- Public Variables ----------------------------------------------------

bool    BioloidBus::m_log   = false;

// ---- Private Constants and Types -----------------------------------------
// ---- Private Variables ---------------------------------------------------
// ---- Private Function Prototypes -----------------------------------------
// ---- Functions -----------------------------------------------------------

/**
 * @addtogroup bioloid
 * @{
 */

//***************************************************************************
/**
*   Constructor
*/

BioloidBus::BioloidBus()
{
}

//***************************************************************************
/**
*   Destructor
*
*   virtual
*/

BioloidBus::~BioloidBus()
{
}

//***************************************************************************
/**
*   Reads a packet. Returns true if a packet was read successfully,
*   false if a timeout or error occurred.
*
*   virtual
*/

bool BioloidBus::ReadStatusPacket( BioloidPacket *pkt )
{
    Bioloid::Error err;

    do
    {
        uint8_t         ch;

        if ( !ReadByte( &ch ))
        {
            return false;
        }

        err = pkt->ProcessChar( ch );

    } while ( err == Bioloid::ERROR_NOT_DONE );

    return err == Bioloid::ERROR_NONE;
}

//***************************************************************************
/**
*   Scans the bus, calling the passed callback for each device
*   ID which responds.
*/

bool BioloidBus::Scan( bool (*devFound)( BioloidBus *bus, BioloidDevice *dev ))
{
    Bioloid::ID_t   id;
    BioloidDevice   scanDev;
    bool            someDevFound = false;

    for ( id = 0; id < Bioloid::BROADCAST_ID; id++ )
    {
        scanDev.SetBusAndID( this, id );

        if ( scanDev.Ping() == Bioloid::ERROR_NONE )
        {
            someDevFound = true;

            if ( !devFound( this, &scanDev ))
            {
                break;
            }
        }
    }

    return someDevFound;
}

//***************************************************************************
/**
*   Broadcasts an action packet to all of the devices on the bus.
*   This causes all of the devices to perform their deferred writes
*   at the same time.
*/

void BioloidBus::SendAction()
{
    BLD_BUS_LOG( "Sending ACTION\n" );

    SendCmdHeader( Bioloid::BROADCAST_ID, 0, Bioloid::CMD_ACTION );
    SendCheckSum();
}

//***************************************************************************
/**
*   Send the checksum. Since the checksum byte is the last byte of the
*   packet, this function is made virtual to allow bus drivers to
*   buffer the packet bytes until the entire packet is ready to send.
*
*   virtual
*/

void BioloidBus::SendCheckSum()
{
    SendByte( ~m_checksum );
}

//***************************************************************************
/**
*   Sends 'len' bytes, returning the sum of the bytes for easy accumulation
*   into the checksum) 
*/

void BioloidBus::SendData( uint8_t len, const void *voidData )
{
    const uint8_t *data = static_cast< const uint8_t *>( voidData );

    while ( len-- > 0 )
    {
        SendByte( *data++ );
    }
}

//***************************************************************************
/**
*   Sends the command header, which is common to all of the commands.
*   2 is added to paramLen (to cover the length and cmd bytes). This
*   way the caller is only responsible for figuring out how many extra
*   parameter bytes are being sent.
*
*   virtual
*/

void BioloidBus::SendCmdHeader
(
    Bioloid::ID_t       id, 
    uint8_t             paramLen,
    Bioloid::Command    cmd
)
{
    SendByte( 0xff );
    SendByte( 0xff );

    m_checksum = 0;

    SendByte( id );
    SendByte( paramLen + 2 );
    SendByte( cmd );
}

/** @} */

