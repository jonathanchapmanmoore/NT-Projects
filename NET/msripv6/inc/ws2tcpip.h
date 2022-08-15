// -*- mode: C++; tab-width: 4; indent-tabs-mode: nil -*- (for GNU Emacs)
//
// Copyright (c) 1985-2000 Microsoft Corporation
//
// This file is part of the Microsoft Research IPv6 Network Protocol Stack.
// You should have received a copy of the Microsoft End-User License Agreement
// for this software along with this release; see the file "license.txt".
// If not, please see http://www.research.microsoft.com/msripv6/license.htm,
// or write to Microsoft Research, One Microsoft Way, Redmond, WA 98052-6399.
//
// Abstract:
//
// WinSock2 Extension for TCP/IP protocols.
//
// This file contains TCP/IP specific information for use 
// by WinSock2 compatible applications. 
//
// To provide the backward compatibility, all the TCP/IP  
// specific definitions that were included in the WINSOCK.H
// file are now included in WINSOCK2.H file. WS2TCPIP.H 
// file includes only the definitions  introduced in the 
// "WinSock 2 Protocol-Specific Annex" document.
//
// This file is almost identical to ws2tcpip.h in the Platform SDK.
// For the MSR IPv6 release, we have removed all the IPv6 definitions.
// They are now found in ws2ip6.h.
//


#ifndef _WS2TCPIP_H_
#define _WS2TCPIP_H_

/* Argument structure for IP_ADD_MEMBERSHIP and IP_DROP_MEMBERSHIP */

struct ip_mreq {
	struct in_addr imr_multiaddr;	/* IP multicast address of group */
	struct in_addr imr_interface;	/* local IP address of interface */
};

/* TCP/IP specific Ioctl codes */

#define SIO_GET_INTERFACE_LIST  _IOR('t', 127, u_long)	

/* Option to use with [gs]etsockopt at the IPPROTO_IP level */

#define	IP_OPTIONS		1 /* set/get IP options */
#define	IP_HDRINCL		2 /* header is included with data */
#define	IP_TOS			3 /* IP type of service and preced*/
#define	IP_TTL			4 /* IP time to live */
#define	IP_MULTICAST_IF		9 /* set/get IP multicast i/f  */
#define	IP_MULTICAST_TTL       10 /* set/get IP multicast ttl */
#define	IP_MULTICAST_LOOP      11 /*set/get IP multicast loopback */
#define	IP_ADD_MEMBERSHIP      12 /* add an IP group membership */
#define	IP_DROP_MEMBERSHIP     13/* drop an IP group membership */
#define IP_DONTFRAGMENT     14 /* don't fragment IP datagrams */


/* Option to use with [gs]etsockopt at the IPPROTO_UDP level */

#define UDP_NOCHECKSUM	1

/* Option to use with [gs]etsockopt at the IPPROTO_TCP level */

#define  TCP_EXPEDITED_1122	0x0002


typedef union sockaddr_gen{
		struct sockaddr Address;
		struct sockaddr_in  AddressIn;
		struct sockaddr_in6 AddressIn6;
} sockaddr_gen;

/* Structure to keep interface specific information */

typedef struct _INTERFACE_INFO
{
	u_long		iiFlags;		/* Interface flags */
	sockaddr_gen	iiAddress;		/* Interface address */
	sockaddr_gen	iiBroadcastAddress; 	/* Broadcast address */
	sockaddr_gen	iiNetmask;		/* Network mask */
} INTERFACE_INFO, FAR * LPINTERFACE_INFO;

/* Possible flags for the  iiFlags - bitmask  */ 

#define IFF_UP		0x00000001 /* Interface is up */
#define IFF_BROADCAST	0x00000002 /* Broadcast is  supported */
#define IFF_LOOPBACK	0x00000004 /* this is loopback interface */
#define IFF_POINTTOPOINT 0x00000008 /*this is point-to-point interface*/
#define IFF_MULTICAST	0x00000010 /* multicast is supported */


#endif	/* _WS2TCPIP_H_ */

