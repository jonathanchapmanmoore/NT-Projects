// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Copyright (c) Microsoft Corporation. All rights reserved.


/****************************************************************************
						Microsoft RPC
        
                        usrdef Example

    FILE:       usrdefc.c

    USAGE:      usrdefc  -n network_address
                         -p protocol_sequence
                         -e endpoint
                         -o options

    PURPOSE:    Client side of RPC distributed application

    FUNCTIONS:  main() - binds to server and calls remote procedure

    COMMENTS:   This distributed application uses a user-defined handle.

****************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include "usrdef.h"    // header file generated by MIDL compiler

void Usage(char * pszProgramName)
{
    fprintf_s(stderr, "Usage:  %s\n", pszProgramName);
    fprintf_s(stderr, " -p protocol_sequence\n");
    fprintf_s(stderr, " -n network_address\n");
    fprintf_s(stderr, " -e endpoint\n");
    fprintf_s(stderr, " -o options\n");
    fprintf_s(stderr, " -s string\n");
    exit(1);
}

void __cdecl main(int argc, char **argv)
{
    int i;
    DATA_HANDLE_TYPE dhBinding;
    unsigned char * pszString = "hello, world";

    dhBinding = (DATA_HANDLE_TYPE) midl_user_allocate(sizeof(DATA_TYPE));
    dhBinding->pszProtocolSequence = "ncacn_ip_tcp";
    dhBinding->pszUuid             = NULL;
    dhBinding->pszEndpoint         = "8765";
    dhBinding->pszNetworkAddress   = NULL;
    dhBinding->pszOptions          = NULL;

    /* allow the user to override settings with command line switches */
    for (i = 1; i < argc; i++) {
        if ((*argv[i] == '-') || (*argv[i] == '/')) {
            switch (tolower(*(argv[i]+1))) {
            case 'p':  // protocol sequence
                dhBinding->pszProtocolSequence = argv[++i];
                break;
            case 'n':  // network address
                dhBinding->pszNetworkAddress = argv[++i];
                break;
            case 'e':
                dhBinding->pszEndpoint = argv[++i];
                break;
            case 'o':
                dhBinding->pszOptions = argv[++i];
                break;
            case 's':
                pszString = argv[++i];
                break;
            case 'h':
            case '?':
            default:
                Usage(argv[0]);
            }
        }
        else
            Usage(argv[0]);
    }

	RpcTryExcept{
    printf_s("Calling the remote procedure 'UsrdefProc'\n");
    UsrdefProc(dhBinding, pszString);  // call the remote procedure

    printf_s("Calling the remote procedure 'Shutdown'\n");
    Shutdown(dhBinding);  // shut down the server side
	}
	RpcExcept(( ( (RpcExceptionCode() != STATUS_ACCESS_VIOLATION) &&
                   (RpcExceptionCode() != STATUS_DATATYPE_MISALIGNMENT) &&
                   (RpcExceptionCode() != STATUS_PRIVILEGED_INSTRUCTION) &&
                   (RpcExceptionCode() != STATUS_BREAKPOINT) &&
                   (RpcExceptionCode() != STATUS_STACK_OVERFLOW) &&
                   (RpcExceptionCode() != STATUS_IN_PAGE_ERROR) &&
                   (RpcExceptionCode() != STATUS_GUARD_PAGE_VIOLATION)
                    )
                    ? EXCEPTION_EXECUTE_HANDLER : EXCEPTION_CONTINUE_SEARCH )){
	printf("\nFound an exception: %x",RpcExceptionCode());
	}
	RpcEndExcept
   
}  // end main()

/* This _bind routine is called by the client stub immediately */
/* before each remote procedure call.                          */
RPC_BINDING_HANDLE __RPC_USER DATA_HANDLE_TYPE_bind(DATA_HANDLE_TYPE dh1)
{
    RPC_STATUS status;    // returned by RPC API functions
    RPC_BINDING_HANDLE hBinding;
    unsigned char * pszStringBinding;

    printf_s("Within DATA_HANDLE_TYPE_bind function:\n");
    status = RpcStringBindingCompose(dh1->pszUuid,
                                     dh1->pszProtocolSequence,
                                     dh1->pszNetworkAddress,
                                     dh1->pszEndpoint,
                                     dh1->pszOptions,
                                     &pszStringBinding);
    printf_s("RpcStringBindingCompose returned 0x%x\n", status);
    printf_s("pszStringBinding = %s\n", pszStringBinding);
    if (status) {
        exit(status);
    }

    status = RpcBindingFromStringBinding(pszStringBinding,
                                         &hBinding);
    printf_s("RpcBindingFromStringBinding returned 0x%x\n", status);
    if (status) {
        exit(status);
    }

    status = RpcStringFree(&pszStringBinding);  // unbind
    printf_s("RpcStringFree returned 0x%x\n", status);
    if (status) {
        exit(status);
    }

    return(hBinding);
}

/* This _unbind routine is called by the client stub immediately */
/* after each remote procedure call.                             */
void __RPC_USER DATA_HANDLE_TYPE_unbind(DATA_HANDLE_TYPE dh1,
                                       RPC_BINDING_HANDLE h1)
{
     RPC_STATUS status;    // returned by RPC API functions

     printf_s("Within DATA_HANDLE_TYPE_unbind function:\n");
     printf_s("Unbinding handle for %s\n", dh1->pszEndpoint);

     status = RpcBindingFree(&h1);  // unbind
     printf_s("RpcBindingFree returned 0x%x\n", status);
}

/*********************************************************************/
/*                 MIDL allocate and free                            */
/*********************************************************************/

void __RPC_FAR * __RPC_USER midl_user_allocate(size_t len)
{
    return(malloc(len));
}

void __RPC_USER midl_user_free(void __RPC_FAR * ptr)
{
    free(ptr);
}

/* end file usrdefc.c */
