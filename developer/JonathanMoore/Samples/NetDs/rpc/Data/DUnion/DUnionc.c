// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Copyright (c) Microsoft Corporation. All rights reserved.


/****************************************************************************
						Microsoft RPC
                    Discriminated Union Example

    FILE:       dunionc.c

    USAGE:      dunionc  -n network_address
                         -p protocol_sequence
                         -e endpoint
                         -o options
                         -d discriminant
                         -v union_value

    PURPOSE:    Client side of RPC distributed application

    FUNCTIONS:  main() - binds to server and calls remote procedure

    COMMENTS:   This distributed application illustrates discriminated
                union.

****************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include "dunion.h"    // header file generated by MIDL compiler


void Usage(char * pszProgramName)
{
    fprintf_s(stderr, "Usage:  %s\n", pszProgramName);
    fprintf_s(stderr, " -p protocol_sequence\n");
    fprintf_s(stderr, " -n network_address\n");
    fprintf_s(stderr, " -e endpoint\n");
    fprintf_s(stderr, " -o options\n");
    fprintf_s(stderr, " -d discriminant\n");
    fprintf_s(stderr, " -v union_value\n");
    exit(1);
}

void DisplayUnionValue(DISCRIM_UNION_PARAM_TYPE *up,
                       short                    sDiscrim)
{
    printf_s("sDiscrim = %d, data = ", sDiscrim);
    switch(sDiscrim) {
    case 0:
        printf_s("short: %d\n", up->sVal);
        break;
    case 1:
        printf_s("float: %f\n", up->fVal);
        break;
    case 2:
        printf_s("char: %c\n", up->chVal);
        break;
    default:
        printf_s("invalid\n");
        break;
    }
}

void __cdecl main(int argc, char **argv)
{
    RPC_STATUS status;
    unsigned char * pszUuid             = NULL;
    unsigned char * pszProtocolSequence = "ncacn_ip_tcp";
    unsigned char * pszNetworkAddress   = NULL;
    unsigned char * pszEndpoint         = "8765";
    unsigned char * pszOptions          = NULL;
    unsigned char * pszStringBinding    = NULL;
    int i;

    short sDiscrim = 0;
    DISCRIM_UNION_PARAM_TYPE  up = {1};
    DISCRIM_UNION_STRUCT_TYPE us = {0, 1};

    /* allow the user to override settings with command line switches */
    for (i = 1; i < argc; i++) {
        if ((*argv[i] == '-') || (*argv[i] == '/')) {
            switch (tolower(*(argv[i]+1))) {
            case 'p':  // protocol sequence
                pszProtocolSequence = argv[++i];
                break;
            case 'n':  // network address
                pszNetworkAddress = argv[++i];
                break;
            case 'e':
                pszEndpoint = argv[++i];
                break;
            case 'o':
                pszOptions = argv[++i];
                break;
            case 'd':
                sDiscrim = (short) atoi(argv[++i]);
                if ((sDiscrim > 3) || (sDiscrim < 0))
                    sDiscrim = 0;
                us.sDiscrim = sDiscrim;
                break;
            case 'v':
                switch(sDiscrim) {
                case 0:
                    up.sVal =  (short) atoi(argv[++i]);
                    us.u.sVal = up.sVal;
                    break;
                case 1:
                    up.fVal =  (float) atof(argv[++i]);
                    us.u.fVal = up.fVal;
                    break;
                case 2:
                    up.chVal = *(argv[++i]);
                    us.u.chVal = up.chVal;
                    break;
                default:
                    break;
                }
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

    /* Use a convenience function to concatenate the elements of  */
    /* the string binding into the proper sequence.               */
    status = RpcStringBindingCompose(pszUuid,
                                     pszProtocolSequence,
                                     pszNetworkAddress,
                                     pszEndpoint,
                                     pszOptions,
                                     &pszStringBinding);
    printf_s("RpcStringBindingCompose returned 0x%x\n", status);
    printf_s("pszStringBinding = %s\n", pszStringBinding);
    if (status) {
        exit(status);
    }

    /* Set the binding handle that will be used to bind to the server. */
    status = RpcBindingFromStringBinding(pszStringBinding,
                                         &hDiscrim);
    printf_s("RpcBindingFromStringBinding returned 0x%x\n", status);
    if (status) {
        exit(status);
    }

    printf_s("Calling the remote procedure 'UnionParamProc'\n");

    RpcTryExcept {
        DisplayUnionValue(&up, sDiscrim);  // display value before call
        UnionParamProc(hDiscrim,&up, sDiscrim);     // call the remote procedure

        UnionStructProc(hDiscrim,&us);              // call the remote procedure
        DisplayUnionValue(&up, sDiscrim);  // display value after call

        Shutdown(hDiscrim);                    // Shut down the server
    }
    RpcExcept(( ( (RpcExceptionCode() != STATUS_ACCESS_VIOLATION) &&
                   (RpcExceptionCode() != STATUS_DATATYPE_MISALIGNMENT) &&
                   (RpcExceptionCode() != STATUS_PRIVILEGED_INSTRUCTION) &&
                   (RpcExceptionCode() != STATUS_BREAKPOINT) &&
                   (RpcExceptionCode() != STATUS_STACK_OVERFLOW) &&
                   (RpcExceptionCode() != STATUS_IN_PAGE_ERROR) &&
                   (RpcExceptionCode() != STATUS_GUARD_PAGE_VIOLATION)
                    )
                    ? EXCEPTION_EXECUTE_HANDLER : EXCEPTION_CONTINUE_SEARCH )) {
        printf_s("Runtime reported exception %ld\n", RpcExceptionCode() );

	printf_s("\n!!!NOTE!!!\nIf you are running XP or Vista, this problem might be due to Access Denial. Kindly go through the MSDN material: http://msdn.microsoft.com/security/productinfo/XPSP2/networkprotection/restrict_remote_clients_devimp.aspx.  \n\n");
    }
    RpcEndExcept

    /*  The remote procedure call is complete.  Free the binding handle */
    status = RpcBindingFree(&hDiscrim);
    printf_s("RpcBindingFree returned 0x%x\n", status);
    if (status) {
        exit(status);
    }

    exit(0);

}  // end main()


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

/* end file dunionc.c */
