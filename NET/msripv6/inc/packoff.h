/*++

Copyright (c) 1990,91  Microsoft Corporation

This file is part of the Microsoft Research IPv6 Network Protocol Stack.
You should have received a copy of the Microsoft End-User License Agreement
for this software along with this release; see the file "license.txt".
If not, please see http://www.research.microsoft.com/msripv6/license.htm,
or write to Microsoft Research, One Microsoft Way, Redmond, WA 98052-6399.

Module Name:

    packoff.h

Abstract:

    This file turns packing of structures off.  (That is, it enables
    automatic alignment of structure fields.)  An include file is needed
    because various compilers do this in different ways.

    packoff.h is the complement to packon.h.  An inclusion of packoff.h
    MUST ALWAYS be preceded by an inclusion of packon.h, in one-to-one
    correspondence.

Author:

    Chuck Lenzmeier (chuckl) 4-Mar-1990

Revision History:

    15-Apr-1991 JohnRo
        Created lint-able variant.
--*/

#if ! (defined(lint) || defined(_lint))
#if ( _MSC_VER >= 800 )
#pragma warning(disable:4103)
#endif
#pragma pack()
#endif // ! (defined(lint) || defined(_lint))
