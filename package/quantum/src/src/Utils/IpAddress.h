/*---------------------------------------------------------------------------
-----------------------------------------------------------------------------
Copyright 2003-201x Haute école ARC Ingéniérie, Switzerland.
All rights reserved.
-----------------------------------------------------------------------------
File name 			: IpAddress.h
Author				: Cestele Yves
Date				: 30 juin 2017
Description			: Header for the functions used for the
				  TCP/IP communication

Modifications			: -

---------------------------------------------------------------------------*/
#ifndef SRC_UTILS_IPADDRESS_H_
#define SRC_UTILS_IPADDRESS_H_

//--------------------------------------------------------------
// 				INCLUDES & DEFINES
//--------------------------------------------------------------
#include "xil_types.h"

// UDP buffer size
#define kBufSize 256

// Network configuration
struct uip_eth_addr {
  u8 addr[6];
};

typedef struct
{
    u32 Tag;
    u32 TftpServerAddr;
    u32 IPAddr;
    u32 IPmask;
    u32 IPGTW;
    struct uip_eth_addr MacAddress;
    u16 RemotePort;
}IPConfigStruct;

extern IPConfigStruct gIPConfig;

//--------------------------------------------------------------
// 				FUNCTIONS'S LIST
//--------------------------------------------------------------





#endif /* SRC_UTILS_IPADDRESS_H_ */
