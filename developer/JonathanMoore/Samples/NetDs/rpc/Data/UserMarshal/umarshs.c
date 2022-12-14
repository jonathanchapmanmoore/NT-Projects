// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Copyright (c) Microsoft Corporation. All rights reserved.


/****************************************************************************
						Microsoft RPC
                        umarsh Example

    FILE:       umarshs.c

    USAGE:      umarshs -p protocol_sequence
                       -e endpoint
                       -m max calls
                       -n min calls
                       -f flag for RpcServerListen

    PURPOSE:    Server side of RPC distributed application umarsh

    FUNCTIONS:  main() - registers server as RPC server

    COMMENTS:   This sample program generates a client and server can share
                an interface, but one side can use a different representation
                than the other.

                The client side in this example does all operations using
                character strings, and the server side does all operations
                using UNICODE strings.  Two procedures are provided, one
                defined with ASCII strings, one with UNICODE strings.
                The wire format reflects these definitions, yet the client
                and server see pure ASCII and pure UNICODE respectively.

                The [represent_as] attribute (used in the client and server
                side acf files) requires the four user-supplied functions
                whose names start with the name of the transmitted type
                (in the client side's case: WCHAR_STRING)

                The [in, out] attributes applied to remote procedure
                parameters require the two user-supplied functions
                midl_user_allocate and midl_user_free.

                The other functions are utilities that are used to
                build or display the data structures.

****************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include "umarshs.h"     // header file generated by MIDL compiler

#define PURPOSE \
"This Microsoft RPC Version sample program demonstrates\n\
the use of the [transmit_as] attribute. For more information\n\
about the attributes and the RPC API functions, see the\n\
RPC programming guide and reference.\n\n"

void Usage(char * pszProgramName)
{
    fprintf_s(stderr, "%s", PURPOSE);
    fprintf_s(stderr, "Usage:  %s\n", pszProgramName);
    fprintf_s(stderr, " -p protocol_sequence\n");
    fprintf_s(stderr, " -e endpoint\n");
    fprintf_s(stderr, " -m maxcalls\n");
    fprintf_s(stderr, " -n mincalls\n");
    fprintf_s(stderr, " -f flag_wait_op\n");
    //fprintf_s(stderr, " -i interface_flag\n");
    exit(1);
}

/* main:  register the interface, start listening for clients */
void __cdecl main(int argc, char * argv[])
{
    RPC_STATUS status;
    unsigned char * pszProtocolSequence = "ncacn_ip_tcp";
    unsigned char * pszSecurity         = NULL;
    unsigned char * pszEndpoint         = "8765";
    unsigned int    cMinCalls           = 1;
    unsigned int    cMaxCalls           = 20;
    unsigned int    fDontWait           = FALSE;
    unsigned int    ifFlag             = RPC_C_AUTHN_LEVEL_NONE;

    int i;

    /* allow the user to override settings with command line switches */
    for (i = 1; i < argc; i++) {
        if ((*argv[i] == '-') || (*argv[i] == '/')) {
            switch (tolower(*(argv[i]+1))) {
            case 'p':  // protocol sequence
                pszProtocolSequence = argv[++i];
                break;
            case 'e':
                pszEndpoint = argv[++i];
                break;
            case 'm':
                cMaxCalls = (unsigned int) atoi(argv[++i]);
                break;
            case 'n':
                cMinCalls = (unsigned int) atoi(argv[++i]);
                break;
            case 'f':
                fDontWait = (unsigned int) atoi(argv[++i]);
                break;
	  /* case 'i':
		if(!_stricmp(argv[++i],"No_Authenticate"))
			ifFlag = RPC_IF_ALLOW_CALLBACKS_WITH_NO_AUTH;
		break;*/

            case 'h':
            case '?':
            default:
                Usage(argv[0]);
            }
        }
        else
            Usage(argv[0]);
    }

    status = RpcServerUseProtseqEp(pszProtocolSequence,
                                   cMaxCalls,
                                   pszEndpoint,
                                   pszSecurity);  // Security descriptor
    printf_s("RpcServerUseProtseqEp returned 0x%x\n", status);
    if (status) {
        exit(status);
    }


 status = RpcServerRegisterIfEx(umarsh_ServerIfHandle,  NULL, NULL, ifFlag, RPC_C_LISTEN_MAX_CALLS_DEFAULT, NULL ); 


    printf_s("RpcServerRegisterIfEx returned 0x%x\n", status);
    if (status) {
        exit(status);
    }

    printf_s("Calling RpcServerListen\n");
    status = RpcServerListen(cMinCalls,
                             cMaxCalls,
                             fDontWait);
    printf_s("RpcServerListen returned: 0x%x\n", status);
    if (status) {
        exit(status);
    }

    if (fDontWait) {
        printf_s("Calling RpcMgmtWaitServerListen\n");
        status = RpcMgmtWaitServerListen();  //  wait operation
        printf_s("RpcMgmtWaitServerListen returned: 0x%x\n", status);
        if (status) {
            exit(status);
        }
    }

}  // end main()

/* end file umarshs.c */
