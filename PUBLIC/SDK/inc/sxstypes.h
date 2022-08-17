 
/*++ BUILD Version: 0005    // Increment this if a change has global effects

Copyright (c) Microsoft Corporation.  All rights reserved.

Module Name:

    sxstypes.h

Abstract:

    Include file with definitions for data structures used for side-by-side
    binding.

Author:

    Michael Grier (MGrier) 28-Mar-2000

Environment:


Revision History:

--*/

#ifndef _SXSTYPES_
#define _SXSTYPES_

#if (_MSC_VER > 1020)
#pragma once
#endif

#if defined(__cplusplus)
extern "C" {
#endif

typedef struct _ACTIVATION_CONTEXT_DATA ACTIVATION_CONTEXT_DATA;
typedef const ACTIVATION_CONTEXT_DATA *PCACTIVATION_CONTEXT_DATA;

//
// These data structures have to line up in a number of different run-time
// environments, so we explicitly set the alignment.
//
#include "pshpack4.h"
//
// These data structures may be generated by 64bit code and consumed
// in 32bit code, as in the case of 32bit processes on Win64.
// Therefore they have no pointers and no SIZE_Ts.
//
// Besides that, they are created in a different process than they
// are consumed. They are position independent.
//

//
//  ASSEMBLY_VERSION represents a traditional four-part version
//  as in Major.Minor.Revision.Build.
//
//  They are laid out so that you can perform a simple ULONGLONG-
//  based comparison on them.
//
//  They are interpreted as:
//
//      Major.Minor.Build.Revision
//
//  So for example you might have "5.1.2505.2" (where 5.1 is the major
//  minor, 2505 represents the daily build number and 2 is the number
//  of updates to the build since its initial build).
//
//  Overloaded comparison operators are provided for C++ clients.
//

#include "pshpack1.h"

typedef union _ASSEMBLY_VERSION {
    struct {
        USHORT Build;
        USHORT Revision;
        USHORT Minor;
        USHORT Major;
    };
    ULONGLONG QuadPart;
} ASSEMBLY_VERSION, *PASSEMBLY_VERSION;

#include "poppack.h"

typedef const ASSEMBLY_VERSION *PCASSEMBLY_VERSION;

#if defined(__cplusplus)
extern "C++" {
inline bool operator ==(const ASSEMBLY_VERSION &av1, const ASSEMBLY_VERSION &av2) { return av1.QuadPart == av2.QuadPart; }
inline bool operator !=(const ASSEMBLY_VERSION &av1, const ASSEMBLY_VERSION &av2) { return av1.QuadPart != av2.QuadPart; }
inline bool operator <(const ASSEMBLY_VERSION &av1, const ASSEMBLY_VERSION &av2) { return av1.QuadPart < av2.QuadPart; }
inline bool operator >(const ASSEMBLY_VERSION &av1, const ASSEMBLY_VERSION &av2) { return av1.QuadPart > av2.QuadPart; }
inline bool operator <=(const ASSEMBLY_VERSION &av1, const ASSEMBLY_VERSION &av2) { return av1.QuadPart <= av2.QuadPart; }
inline bool operator >=(const ASSEMBLY_VERSION &av1, const ASSEMBLY_VERSION &av2) { return av1.QuadPart >= av2.QuadPart; }
} /* extern "C++" */
#endif /* __cplusplus */

//
//  Standard Activation Context section IDs:
//

// begin_winnt
#define ACTIVATION_CONTEXT_SECTION_ASSEMBLY_INFORMATION         (1)
#define ACTIVATION_CONTEXT_SECTION_DLL_REDIRECTION              (2)
#define ACTIVATION_CONTEXT_SECTION_WINDOW_CLASS_REDIRECTION     (3)
#define ACTIVATION_CONTEXT_SECTION_COM_SERVER_REDIRECTION       (4)
#define ACTIVATION_CONTEXT_SECTION_COM_INTERFACE_REDIRECTION    (5)
#define ACTIVATION_CONTEXT_SECTION_COM_TYPE_LIBRARY_REDIRECTION (6)
#define ACTIVATION_CONTEXT_SECTION_COM_PROGID_REDIRECTION       (7)
#define ACTIVATION_CONTEXT_SECTION_GLOBAL_OBJECT_RENAME_TABLE   (8)
#define ACTIVATION_CONTEXT_SECTION_CLR_SURROGATES               (9)
// end_winnt

//
//  Activation Context section format identifiers:
//

#define ACTIVATION_CONTEXT_SECTION_FORMAT_UNKNOWN               (0)
#define ACTIVATION_CONTEXT_SECTION_FORMAT_STRING_TABLE          (1)
#define ACTIVATION_CONTEXT_SECTION_FORMAT_GUID_TABLE            (2)

typedef struct _ACTIVATION_CONTEXT_DATA {
    ULONG Magic;
    ULONG HeaderSize;
    ULONG FormatVersion;
    ULONG TotalSize;
    ULONG DefaultTocOffset;
    ULONG ExtendedTocOffset;
    ULONG AssemblyRosterOffset;
    ULONG Flags;
} ACTIVATION_CONTEXT_DATA, *PACTIVATION_CONTEXT_DATA;
typedef const ACTIVATION_CONTEXT_DATA *PCACTIVATION_CONTEXT_DATA;

#define ACTIVATION_CONTEXT_DATA_MAGIC ((ULONG) 'xtcA')
#define ACTIVATION_CONTEXT_DATA_FORMAT_WHISTLER (1)

// Internally this is associated with the data, but externally
// the data is usually opaque and it is associated with the activation context.
#define ACTIVATION_CONTEXT_FLAG_NO_INHERIT (0x00000001)

typedef struct _ACTIVATION_CONTEXT_DATA_TOC_HEADER {
    ULONG HeaderSize;
    ULONG EntryCount;
    ULONG FirstEntryOffset;
    ULONG Flags;
} ACTIVATION_CONTEXT_DATA_TOC_HEADER, *PACTIVATION_CONTEXT_DATA_TOC_HEADER;
typedef const struct _ACTIVATION_CONTEXT_DATA_TOC_HEADER *PCACTIVATION_CONTEXT_DATA_TOC_HEADER;

#define ACTIVATION_CONTEXT_DATA_TOC_HEADER_DENSE (0x00000001)
#define ACTIVATION_CONTEXT_DATA_TOC_HEADER_INORDER (0x00000002)

typedef struct _ACTIVATION_CONTEXT_DATA_TOC_ENTRY {
    ULONG Id;
    ULONG Offset;            // from ACTIVATION_CONTEXT_DATA base
    ULONG Length;           // in bytes
    ULONG Format;           // ACTIVATION_CONTEXT_SECTION_FORMAT_*
} ACTIVATION_CONTEXT_DATA_TOC_ENTRY, *PACTIVATION_CONTEXT_DATA_TOC_ENTRY;
typedef const struct _ACTIVATION_CONTEXT_DATA_TOC_ENTRY *PCACTIVATION_CONTEXT_DATA_TOC_ENTRY;

typedef struct _ACTIVATION_CONTEXT_DATA_EXTENDED_TOC_HEADER {
    ULONG HeaderSize;
    ULONG EntryCount;
    ULONG FirstEntryOffset;     // from ACTIVATION_CONTEXT_DATA base
    ULONG Flags;
} ACTIVATION_CONTEXT_DATA_EXTENDED_TOC_HEADER, *PACTIVATION_CONTEXT_DATA_EXTENDED_TOC_HEADER;
typedef const struct _ACTIVATION_CONTEXT_DATA_EXTENDED_TOC_HEADER *PCACTIVATION_CONTEXT_DATA_EXTENDED_TOC_HEADER;

typedef struct _ACTIVATION_CONTEXT_DATA_EXTENDED_TOC_ENTRY {
    GUID ExtensionGuid;
    ULONG TocOffset;            // from ACTIVATION_CONTEXT_DATA base
    ULONG Length;
} ACTIVATION_CONTEXT_DATA_EXTENDED_TOC_ENTRY, *PACTIVATION_CONTEXT_DATA_EXTENDED_TOC_ENTRY;
typedef const struct _ACTIVATION_CONTEXT_DATA_EXTENDED_TOC_ENTRY *PCACTIVATION_CONTEXT_DATA_EXTENDED_TOC_ENTRY;

typedef struct _ACTIVATION_CONTEXT_DATA_ASSEMBLY_ROSTER_HEADER {
    ULONG HeaderSize;
    ULONG HashAlgorithm;
    ULONG EntryCount;               // Entry 0 is reserved; this is the number of assemblies plus 1.
    ULONG FirstEntryOffset;         // From ACTIVATION_CONTEXT_DATA base
    ULONG AssemblyInformationSectionOffset; // Offset from the ACTIVATION_CONTEXT_DATA base to the
                                    // header of the assembly information string section.  Needed because
                                    // the roster entries contain the offsets from the ACTIVATION_CONTEXT_DATA
                                    // to the assembly information structs, but those structs contain offsets
                                    // from their section base to the strings etc.
} ACTIVATION_CONTEXT_DATA_ASSEMBLY_ROSTER_HEADER, *PACTIVATION_CONTEXT_DATA_ASSEMBLY_ROSTER_HEADER;
typedef const struct _ACTIVATION_CONTEXT_DATA_ASSEMBLY_ROSTER_HEADER *PCACTIVATION_CONTEXT_DATA_ASSEMBLY_ROSTER_HEADER;

#define ACTIVATION_CONTEXT_DATA_ASSEMBLY_ROSTER_ENTRY_INVALID (0x00000001)
#define ACTIVATION_CONTEXT_DATA_ASSEMBLY_ROSTER_ENTRY_ROOT    (0x00000002)

typedef struct _ACTIVATION_CONTEXT_DATA_ASSEMBLY_ROSTER_ENTRY {
    ULONG Flags;
    ULONG PseudoKey;                // case-insentively-hashed assembly name
    ULONG AssemblyNameOffset;       // from ACTIVATION_CONTEXT_DATA base
    ULONG AssemblyNameLength;       // length in bytes
    ULONG AssemblyInformationOffset; // from ACTIVATION_CONTEXT_DATA base to ACTIVATION_CONTEXT_DATA_ASSEMBLY_INFORMATION
    ULONG AssemblyInformationLength; // length in bytes
} ACTIVATION_CONTEXT_DATA_ASSEMBLY_ROSTER_ENTRY, *PACTIVATION_CONTEXT_DATA_ASSEMBLY_ROSTER_ENTRY;
typedef const struct _ACTIVATION_CONTEXT_DATA_ASSEMBLY_ROSTER_ENTRY *PCACTIVATION_CONTEXT_DATA_ASSEMBLY_ROSTER_ENTRY;

//
//  ActivationContext string sections are organized as follows:
//
//  Header
//  Hash structure (optional)
//  List of subelements
//  Variable length data
//
//
//  If you don't recognize the FormatVersion, you should still
//  be able to navigate to the list of subelements; once there
//  you can still do a very fast linear search avoiding many
//  string comparisons if the hash algorithms align.
//
//  If you can't even use the hash algorithm, you can still do
//  string comparisons.
//

typedef struct _ACTIVATION_CONTEXT_STRING_SECTION_HEADER {
    ULONG Magic;
    ULONG HeaderSize;               // in bytes
    ULONG FormatVersion;
    ULONG DataFormatVersion;
    ULONG Flags;
    ULONG ElementCount;
    ULONG ElementListOffset;        // offset from section header
    ULONG HashAlgorithm;
    ULONG SearchStructureOffset;    // offset from section header
    ULONG UserDataOffset;           // offset from section header
    ULONG UserDataSize;             // in bytes
} ACTIVATION_CONTEXT_STRING_SECTION_HEADER, *PACTIVATION_CONTEXT_STRING_SECTION_HEADER;

typedef const ACTIVATION_CONTEXT_STRING_SECTION_HEADER *PCACTIVATION_CONTEXT_STRING_SECTION_HEADER;

#define ACTIVATION_CONTEXT_STRING_SECTION_MAGIC ((ULONG) 'dHsS')

#define ACTIVATION_CONTEXT_STRING_SECTION_FORMAT_WHISTLER (1)

#define ACTIVATION_CONTEXT_STRING_SECTION_CASE_INSENSITIVE              (0x00000001)
#define ACTIVATION_CONTEXT_STRING_SECTION_ENTRIES_IN_PSEUDOKEY_ORDER    (0x00000002)

typedef struct _ACTIVATION_CONTEXT_STRING_SECTION_HASH_TABLE {
    ULONG BucketTableEntryCount;
    ULONG BucketTableOffset;        // offset from section header
} ACTIVATION_CONTEXT_STRING_SECTION_HASH_TABLE, *PACTIVATION_CONTEXT_STRING_SECTION_HASH_TABLE;

typedef const ACTIVATION_CONTEXT_STRING_SECTION_HASH_TABLE *PCACTIVATION_CONTEXT_STRING_SECTION_HASH_TABLE;

typedef struct _ACTIVATION_CONTEXT_STRING_SECTION_HASH_BUCKET {
    ULONG ChainCount;
    ULONG ChainOffset;              // offset from section header
} ACTIVATION_CONTEXT_STRING_SECTION_HASH_BUCKET, *PACTIVATION_CONTEXT_STRING_SECTION_HASH_BUCKET;

typedef const ACTIVATION_CONTEXT_STRING_SECTION_HASH_BUCKET *PCACTIVATION_CONTEXT_STRING_SECTION_HASH_BUCKET;

// The hash table bucket chain is then a list of offsets from the section header to
// the section entries for the chain.

typedef struct _ACTIVATION_CONTEXT_STRING_SECTION_ENTRY {
    ULONG PseudoKey;
    ULONG KeyOffset;            // offset from the section header
    ULONG KeyLength;            // in bytes
    ULONG Offset;               // offset from the section header
    ULONG Length;               // in bytes
    ULONG AssemblyRosterIndex;  // 1-based index into the assembly roster for the assembly that
                                // provided this entry.  If the entry is not associated with
                                // an assembly, zero.
} ACTIVATION_CONTEXT_STRING_SECTION_ENTRY, *PACTIVATION_CONTEXT_STRING_SECTION_ENTRY;

typedef const ACTIVATION_CONTEXT_STRING_SECTION_ENTRY *PCACTIVATION_CONTEXT_STRING_SECTION_ENTRY;

//
//  ActivationContext GUID sections are organized as follows:
//
//  Header
//  Hash structure (optional)
//  List of subelements
//  Variable length data
//
//  If you don't recognize the FormatVersion, you should still
//  be able to navigate to the list of subelements; once there
//  you can still do a very fast linear search avoiding many
//  GUID comparisons.
//

typedef struct _ACTIVATION_CONTEXT_GUID_SECTION_HEADER {
    ULONG Magic;
    ULONG HeaderSize;
    ULONG FormatVersion;
    ULONG DataFormatVersion;
    ULONG Flags;
    ULONG ElementCount;
    ULONG ElementListOffset;        // offset from section header
    ULONG SearchStructureOffset;    // offset from section header
    ULONG UserDataOffset;           // offset from section header
    ULONG UserDataSize;             // in bytes
} ACTIVATION_CONTEXT_GUID_SECTION_HEADER, *PACTIVATION_CONTEXT_GUID_SECTION_HEADER;

typedef const ACTIVATION_CONTEXT_GUID_SECTION_HEADER *PCACTIVATION_CONTEXT_GUID_SECTION_HEADER;

#define ACTIVATION_CONTEXT_GUID_SECTION_MAGIC ((ULONG) 'dHsG')

#define ACTIVATION_CONTEXT_GUID_SECTION_FORMAT_WHISTLER (1)

#define ACTIVATION_CONTEXT_GUID_SECTION_ENTRIES_IN_ORDER    (0x00000001)

typedef struct _ACTIVATION_CONTEXT_GUID_SECTION_HASH_TABLE {
    ULONG BucketTableEntryCount;
    ULONG BucketTableOffset;        // offset from section header
} ACTIVATION_CONTEXT_GUID_SECTION_HASH_TABLE, *PACTIVATION_CONTEXT_GUID_SECTION_HASH_TABLE;

typedef const ACTIVATION_CONTEXT_GUID_SECTION_HASH_TABLE *PCACTIVATION_CONTEXT_GUID_SECTION_HASH_TABLE;

typedef struct _ACTIVATION_CONTEXT_GUID_SECTION_HASH_BUCKET {
    ULONG ChainCount;
    ULONG ChainOffset;              // offset from section header
} ACTIVATION_CONTEXT_GUID_SECTION_HASH_BUCKET, *PACTIVATION_CONTEXT_GUID_SECTION_HASH_BUCKET;

typedef const ACTIVATION_CONTEXT_GUID_SECTION_HASH_BUCKET *PCACTIVATION_CONTEXT_GUID_SECTION_HASH_BUCKET;

// The hash table bucket chain is then a list of offsets from the section header to
// the section entries for the chain.

typedef struct _ACTIVATION_CONTEXT_GUID_SECTION_ENTRY {
    GUID Guid;
    ULONG Offset;               // offset from the section header
    ULONG Length;               // in bytes
    ULONG AssemblyRosterIndex;  // 1-based index into the assembly roster for the assembly that
                                // provided this entry.  If the entry is not associated with
                                // an assembly, zero.
} ACTIVATION_CONTEXT_GUID_SECTION_ENTRY, *PACTIVATION_CONTEXT_GUID_SECTION_ENTRY;

typedef const ACTIVATION_CONTEXT_GUID_SECTION_ENTRY *PCACTIVATION_CONTEXT_GUID_SECTION_ENTRY;

//
//  Data structures for the assembly information section (NULL Extension GUID, ACTIVATION_CONTEXT_SECTION_ASSEMBLY_INFORMATION)
//

typedef struct _ACTIVATION_CONTEXT_DATA_ASSEMBLY_GLOBAL_INFORMATION {
    ULONG Size;
    ULONG Flags;
    GUID PolicyCoherencyGuid;
    GUID PolicyOverrideGuid;
    ULONG ApplicationDirectoryPathType;
    ULONG ApplicationDirectoryLength;
    ULONG ApplicationDirectoryOffset; // Offset from base of ACTIVATION_CONTEXT_DATA_ASSEMBLY_GLOBAL_INFORMATION
} ACTIVATION_CONTEXT_DATA_ASSEMBLY_GLOBAL_INFORMATION, *PACTIVATION_CONTEXT_DATA_ASSEMBLY_GLOBAL_INFORMATION;
typedef const ACTIVATION_CONTEXT_DATA_ASSEMBLY_GLOBAL_INFORMATION *PCACTIVATION_CONTEXT_DATA_ASSEMBLY_GLOBAL_INFORMATION;

//
//  Leaf node structure for the assembly information section
//

#define ACTIVATION_CONTEXT_DATA_ASSEMBLY_INFORMATION_FORMAT_WHISTLER (1)

//
//  Bitflags for the Flags member of an assembly information section element.
//

#define ACTIVATION_CONTEXT_DATA_ASSEMBLY_INFORMATION_ROOT_ASSEMBLY              (0x00000001)
#define ACTIVATION_CONTEXT_DATA_ASSEMBLY_INFORMATION_POLICY_APPLIED             (0x00000002)
#define ACTIVATION_CONTEXT_DATA_ASSEMBLY_INFORMATION_ASSEMBLY_POLICY_APPLIED    (0x00000004)
#define ACTIVATION_CONTEXT_DATA_ASSEMBLY_INFORMATION_ROOT_POLICY_APPLIED        (0x00000008)
#define ACTIVATION_CONTEXT_DATA_ASSEMBLY_INFORMATION_PRIVATE_ASSEMBLY           (0x00000010)

// ACTIVATION_CONTEXT_PATH_TYPE_NONE is used when
// a manifest has no stored location or identity, such as when a manifest is found
// in the app compat database.  The client is free to specify a manifest path
// string which should assist in diagnosing where the manifest came from, but
// cannot be assumed to have any particular format or syntax.

typedef struct _ACTIVATION_CONTEXT_DATA_ASSEMBLY_INFORMATION {
    ULONG Size;                                 // size of this structure, in bytes
    ULONG Flags;
    ULONG EncodedAssemblyIdentityLength;        // in bytes
    ULONG EncodedAssemblyIdentityOffset;        // offset from section header base

    ULONG ManifestPathType;
    ULONG ManifestPathLength;                   // in bytes
    ULONG ManifestPathOffset;                   // offset from section header base
    LARGE_INTEGER ManifestLastWriteTime;
    ULONG PolicyPathType;
    ULONG PolicyPathLength;                     // in bytes
    ULONG PolicyPathOffset;                     // offset from section header base
    LARGE_INTEGER PolicyLastWriteTime;
    ULONG MetadataSatelliteRosterIndex;
    ULONG Unused2;
    ULONG ManifestVersionMajor;
    ULONG ManifestVersionMinor;
    ULONG PolicyVersionMajor;
    ULONG PolicyVersionMinor;
    ULONG AssemblyDirectoryNameLength; // in bytes
    ULONG AssemblyDirectoryNameOffset; // from section header base
    ULONG NumOfFilesInAssembly;
// 2600 stopped here
    ULONG LanguageLength; // in bytes
    ULONG LanguageOffset; // from section header base
} ACTIVATION_CONTEXT_DATA_ASSEMBLY_INFORMATION, *PACTIVATION_CONTEXT_DATA_ASSEMBLY_INFORMATION;

typedef const ACTIVATION_CONTEXT_DATA_ASSEMBLY_INFORMATION *PCACTIVATION_CONTEXT_DATA_ASSEMBLY_INFORMATION;

//
//  Leaf node structure for the dll redirection section (NULL Extension GUID, ACTIVATION_CONTEXT_SECTION_DLL_REDIRECTION)
//

#define ACTIVATION_CONTEXT_DATA_DLL_REDIRECTION_FORMAT_WHISTLER (1)

//
//  ACTIVATION_CONTEXT_DATA_DLL_REDIRECTION Flags:
//
//      ACTIVATION_CONTEXT_DATA_DLL_REDIRECTION_PATH_INCLUDES_BASE_NAME
//
//          Provides for a redirection that remaps not just the path but the actual
//          base name of the file to access.
//
//          Not used in any current Whistler scenarios.
//
//      ACTIVATION_CONTEXT_DATA_DLL_REDIRECTION_PATH_OMITS_ASSEMBLY_ROOT
//
//          Provides for a redirection where the actual storage path of the file
//          must be determined at runtime by via the assembly roster.  This allows
//          for a cached activation context to remain valid across when an assembly
//          is relocated across storage volumes.
//
//      ACTIVATION_CONTEXT_DATA_DLL_REDIRECTION_PATH_EXPAND
//
//          The path must be constructed by appending all the segments and then
//          the resultant string must be passed through either the
//          RtlExpandEnvironmentStrings() or the Win32 ExpandEnvironmentStrings() APIs.
//
//          Used generally only for app compat where a manifest for the executable
//          may call out a file which the application may erroneously carry with it
//          (possibly on read-only media) to be redirected to, for example,
//          "%windir%\system32\"
//
//      ACTIVATION_CONTEXT_DATA_DLL_REDIRECTION_PATH_SYSTEM_DEFAULT_REDIRECTED_SYSTEM32_DLL
//
//          Provides for dll which exist under system32 as well as system default
//          for example, comctl32.dll. There are two entries for this dll in string section
//          (1) LoadLibrary("comctl32.dll"), redirected to 5.82 comctl32 under winsxs
//          (2) LoadLibrary("c:\windows\system32\comctl32.dll"), is also redirected to 5.82 
//              comctl32 under winsxs
//
//  Note!
//
//      You may not have a single entry with both the
//      ACTIVATION_CONTEXT_DATA_DLL_REDIRECTION_PATH_OMITS_ASSEMBLY_ROOT and
//      ACTIVATION_CONTEXT_DATA_DLL_REDIRECTION_PATH_EXPAND flags set.
//

#define ACTIVATION_CONTEXT_DATA_DLL_REDIRECTION_PATH_INCLUDES_BASE_NAME                     (0x00000001)
#define ACTIVATION_CONTEXT_DATA_DLL_REDIRECTION_PATH_OMITS_ASSEMBLY_ROOT                    (0x00000002)
#define ACTIVATION_CONTEXT_DATA_DLL_REDIRECTION_PATH_EXPAND                                 (0x00000004)
#define ACTIVATION_CONTEXT_DATA_DLL_REDIRECTION_PATH_SYSTEM_DEFAULT_REDIRECTED_SYSTEM32_DLL (0x00000008)

typedef struct _ACTIVATION_CONTEXT_DATA_DLL_REDIRECTION {
    ULONG Size;
    ULONG Flags;
    ULONG TotalPathLength; // bytewise length of concatenated segments only
    ULONG PathSegmentCount;
    ULONG PathSegmentOffset; // offset from section base header so that entries can share
} ACTIVATION_CONTEXT_DATA_DLL_REDIRECTION, *PACTIVATION_CONTEXT_DATA_DLL_REDIRECTION;

typedef const ACTIVATION_CONTEXT_DATA_DLL_REDIRECTION *PCACTIVATION_CONTEXT_DATA_DLL_REDIRECTION;

typedef struct _ACTIVATION_CONTEXT_DATA_DLL_REDIRECTION_PATH_SEGMENT {
    ULONG Length; // in bytes
    ULONG Offset; // from section header so that individual entries can share
} ACTIVATION_CONTEXT_DATA_DLL_REDIRECTION_PATH_SEGMENT, *PACTIVATION_CONTEXT_DATA_DLL_REDIRECTION_PATH_SEGMENT;

typedef const ACTIVATION_CONTEXT_DATA_DLL_REDIRECTION_PATH_SEGMENT *PCACTIVATION_CONTEXT_DATA_DLL_REDIRECTION_PATH_SEGMENT;

//
//  Leaf node structures for window class redirection section (NULL Extension GUID, ACTIVATION_CONTEXT_SECTION_WINDOW_CLASS_REDIRECTION)
//

#define ACTIVATION_CONTEXT_DATA_WINDOW_CLASS_REDIRECTION_FORMAT_WHISTLER (1)

typedef struct _ACTIVATION_CONTEXT_DATA_WINDOW_CLASS_REDIRECTION {
    ULONG Size;
    ULONG Flags;
    ULONG VersionSpecificClassNameLength; // in bytes
    ULONG VersionSpecificClassNameOffset; // Offset from ACTIVATION_CONTEXT_DATA_WINDOW_CLASS_REDIRECTION base
    ULONG DllNameLength; // in bytes
    ULONG DllNameOffset; // Offset from section base because this can be shared across multiple entries
} ACTIVATION_CONTEXT_DATA_WINDOW_CLASS_REDIRECTION, *PACTIVATION_CONTEXT_DATA_WINDOW_CLASS_REDIRECTION;

typedef const ACTIVATION_CONTEXT_DATA_WINDOW_CLASS_REDIRECTION *PCACTIVATION_CONTEXT_DATA_WINDOW_CLASS_REDIRECTION;

//
//  Leaf node structures for COM activation redirection section (NULL Extension GUID, ACTIVATION_CONTEXT_SECTION_COM_SERVER_REDIRECTION)
//

#define ACTIVATION_CONTEXT_DATA_COM_SERVER_REDIRECTION_FORMAT_WHISTLER (1)

#define ACTIVATION_CONTEXT_DATA_COM_SERVER_REDIRECTION_THREADING_MODEL_INVALID (0)
#define ACTIVATION_CONTEXT_DATA_COM_SERVER_REDIRECTION_THREADING_MODEL_APARTMENT (1)
#define ACTIVATION_CONTEXT_DATA_COM_SERVER_REDIRECTION_THREADING_MODEL_FREE (2)
#define ACTIVATION_CONTEXT_DATA_COM_SERVER_REDIRECTION_THREADING_MODEL_SINGLE (3)
#define ACTIVATION_CONTEXT_DATA_COM_SERVER_REDIRECTION_THREADING_MODEL_BOTH (4)
#define ACTIVATION_CONTEXT_DATA_COM_SERVER_REDIRECTION_THREADING_MODEL_NEUTRAL (5)

typedef struct _ACTIVATION_CONTEXT_DATA_COM_SERVER_REDIRECTION {
    ULONG Size;
    ULONG Flags;
    ULONG ThreadingModel;
    GUID ReferenceClsid;
    GUID ConfiguredClsid;
    GUID ImplementedClsid;
    GUID TypeLibraryId;
    ULONG ModuleLength; // in bytes
    ULONG ModuleOffset; // offset from section base because this can be shared across multiple entries
    ULONG ProgIdLength; // in bytes
    ULONG ProgIdOffset; // offset from ACTIVATION_CONTEXT_DATA_COM_SERVER_REDIRECTION because this is never shared
    ULONG ShimDataLength; // in bytes
    ULONG ShimDataOffset; // offset from ACTIVATION_CONTEXT_DATA_COM_SERVER_REDIRECTION because this is not shared
} ACTIVATION_CONTEXT_DATA_COM_SERVER_REDIRECTION, *PACTIVATION_CONTEXT_DATA_COM_SERVER_REDIRECTION;

typedef const ACTIVATION_CONTEXT_DATA_COM_SERVER_REDIRECTION *PCACTIVATION_CONTEXT_DATA_COM_SERVER_REDIRECTION;

//
//  ACTIVATION_CONTEXT_DATA_COM_SERVER_REDIRECTION_SHIM is a struct optionally hung
//  off an ACTIVATION_CONTEXT_DATA_COM_SERVER_REDIRECTION that describes shimming. 
//  The common use of a shim is a file that is not a PE that implements
//  DllGetClassObject(); instead some other DLL will use the path
//  to the file in question plus metadata (typename for managed code and Java)
//  to provide a COM object that implements the CLSID.  Note that the file may not
//  even be a PE for things like scriptlets.  Most shims will reference the
//  system registry for this metadata; Fusion-aware shims can use the information
//  here in the activation context.
//
//  The format version of the ACTIVATION_CONTEXT_DATA_COM_SERVER_REDIRECTION should
//  account for any format changes in the _SHIM struct here.
//

#define ACTIVATION_CONTEXT_DATA_COM_SERVER_REDIRECTION_SHIM_TYPE_OTHER (1)
#define ACTIVATION_CONTEXT_DATA_COM_SERVER_REDIRECTION_SHIM_TYPE_CLR_CLASS (2)

typedef struct _ACTIVATION_CONTEXT_DATA_COM_SERVER_REDIRECTION_SHIM {
    ULONG Size;
    ULONG Flags;
    ULONG Type;
    ULONG ModuleLength; // in bytes
    ULONG ModuleOffset; // offset from section base
    ULONG TypeLength; // in bytes
    ULONG TypeOffset; // offset from ACTIVATION_CONTEXT_DATA_COM_SERVER_REDIRECTION_SHIM
    ULONG ShimVersionLength; // in bytes
    ULONG ShimVersionOffset; // offset from ACTIVATION_CONTEXT_DATA_COM_SERVER_REDIRECTION_SHIM
    ULONG DataLength; // in bytes
    ULONG DataOffset; // offset from ACTIVATION_CONTEXT_DATA_COM_SERVER_REDIRECTION_SHIM
} ACTIVATION_CONTEXT_DATA_COM_SERVER_REDIRECTION_SHIM, *PACTIVATION_CONTEXT_DATA_COM_SERVER_REDIRECTION_SHIM;

typedef const ACTIVATION_CONTEXT_DATA_COM_SERVER_REDIRECTION_SHIM *PCACTIVATION_CONTEXT_DATA_COM_SERVER_REDIRECTION_SHIM;

//
//  Leaf node structures for COM interface marshalling redirection section (NULL Extension GUID, ACTIVATION_CONTEXT_SECTION_COM_INTERFACE_REDIRECTION)
//

#define ACTIVATION_CONTEXT_DATA_COM_INTERFACE_REDIRECTION_FORMAT_WHISTLER (1)

#define ACTIVATION_CONTEXT_DATA_COM_INTERFACE_REDIRECTION_FLAG_NUM_METHODS_VALID    (0x00000001)
#define ACTIVATION_CONTEXT_DATA_COM_INTERFACE_REDIRECTION_FLAG_BASE_INTERFACE_VALID (0x00000002)

typedef struct _ACTIVATION_CONTEXT_DATA_COM_INTERFACE_REDIRECTION {
    ULONG Size;
    ULONG Flags;
    GUID ProxyStubClsid32;
    ULONG NumMethods;
    GUID TypeLibraryId;
    GUID BaseInterface;
    ULONG NameLength; // in bytes
    ULONG NameOffset; // offset from ACTIVATION_CONTEXT_DATA_COM_INTERFACE_REDIRECTION because this is not shared
} ACTIVATION_CONTEXT_DATA_COM_INTERFACE_REDIRECTION, *PACTIVATION_CONTEXT_DATA_COM_INTERFACE_REDIRECTION;

typedef const ACTIVATION_CONTEXT_DATA_COM_INTERFACE_REDIRECTION *PCACTIVATION_CONTEXT_DATA_COM_INTERFACE_REDIRECTION;

//
//  Leaf node structures for COM type library redirection section (NULL Extension GUID, ACTIVATION_CONTEXT_SECTION_COM_TYPE_LIBRARY_REDIRECTION)
//

//
// CLR interop goop
//
#define ACTIVATION_CONTEXT_DATA_CLR_SURROGATE_FORMAT_WHISTLER   (1)

typedef struct _ACTIVATION_CONTEXT_DATA_CLR_SURROGATE {
    ULONG   Size;
    ULONG   Flags;
    GUID    SurrogateIdent;
    ULONG   VersionOffset;              // The version of runtime corresponding to this type
    ULONG   VersionLength;
    ULONG   TypeNameOffset;             // Name of the type that implements this surrogate
    ULONG   TypeNameLength;             
} ACTIVATION_CONTEXT_DATA_CLR_SURROGATE, *PACTIVATION_CONTEXT_DATA_CLR_SURROGATE;

typedef const struct _ACTIVATION_CONTEXT_DATA_CLR_SURROGATE *PCACTIVATION_CONTEXT_DATA_CLR_SURROGATE;




//
//OLD
//OLD  The type library redirection section is keyed off a string composed of the type library GUID,
//OLD  the hexidecimal representation of the LCID for the tlb and the version number of the
//OLD type library.
//OLD
//OLD  e.g.
//OLD
//OLD      "{0ECD9B60-23AA-11D0-B351-00A0C9055D8E}_en-us_6.0"
//OLD
//
// The type library redirection section is keyed off of the type library guid.
//

#define ACTIVATION_CONTEXT_DATA_COM_TYPE_LIBRARY_REDIRECTION_FORMAT_WHISTLER (1)

typedef struct _ACTIVATION_CONTEXT_DATA_TYPE_LIBRARY_VERSION
{
    USHORT Major;
    USHORT Minor;
} ACTIVATION_CONTEXT_DATA_TYPE_LIBRARY_VERSION, *PACTIVATION_CONTEXT_DATA_TYPE_LIBRARY_VERSION;
typedef const ACTIVATION_CONTEXT_DATA_TYPE_LIBRARY_VERSION* PCACTIVATION_CONTEXT_DATA_TYPE_LIBRARY_VERSION;

typedef struct _ACTIVATION_CONTEXT_DATA_COM_TYPE_LIBRARY_REDIRECTION_2600 {
    ULONG   Size;
    ULONG   Flags;
    ULONG   NameLength; // in bytes
    ULONG   NameOffset; // offset from section header
    USHORT  ResourceId; // Resource ID of type library resource in PE
    USHORT  LibraryFlags; // flags, as defined by the LIBFLAGS enumeration in oaidl.h
    ULONG   HelpDirLength; // in bytes
    ULONG   HelpDirOffset; // offset from ACTIVATION_CONTEXT_DATA_COM_TYPE_LIBRARY_REDIRECTION
} ACTIVATION_CONTEXT_DATA_COM_TYPE_LIBRARY_REDIRECTION_2600, *PACTIVATION_CONTEXT_DATA_COM_TYPE_LIBRARY_REDIRECTION_2600;

typedef const ACTIVATION_CONTEXT_DATA_COM_TYPE_LIBRARY_REDIRECTION_2600 *PCACTIVATION_CONTEXT_DATA_COM_TYPE_LIBRARY_REDIRECTION_2600;

typedef struct _ACTIVATION_CONTEXT_DATA_COM_TYPE_LIBRARY_REDIRECTION {
    ULONG   Size;
    ULONG   Flags;
    ULONG   NameLength; // in bytes
    ULONG   NameOffset; // offset from section header
    USHORT  ResourceId; // Resource ID of type library resource in PE
    USHORT  LibraryFlags; // flags, as defined by the LIBFLAGS enumeration in oaidl.h
    ULONG   HelpDirLength; // in bytes
    ULONG   HelpDirOffset; // offset from ACTIVATION_CONTEXT_DATA_COM_TYPE_LIBRARY_REDIRECTION
// 2600 stopped here.
    ACTIVATION_CONTEXT_DATA_TYPE_LIBRARY_VERSION Version;
} ACTIVATION_CONTEXT_DATA_COM_TYPE_LIBRARY_REDIRECTION, *PACTIVATION_CONTEXT_DATA_COM_TYPE_LIBRARY_REDIRECTION;

typedef const ACTIVATION_CONTEXT_DATA_COM_TYPE_LIBRARY_REDIRECTION *PCACTIVATION_CONTEXT_DATA_COM_TYPE_LIBRARY_REDIRECTION;

//
//  Leaf node structures for COM ProgId redirection section (NULL Extension GUID, ACTIVATION_CONTEXT_SECTION_COM_PROGID_REDIRECTION)
//

#define ACTIVATION_CONTEXT_DATA_COM_PROGID_REDIRECTION_FORMAT_WHISTLER (1)

typedef struct _ACTIVATION_CONTEXT_DATA_COM_PROGID_REDIRECTION {
    ULONG Size;
    ULONG Flags;
    ULONG ConfiguredClsidOffset; // offset from section header
} ACTIVATION_CONTEXT_DATA_COM_PROGID_REDIRECTION, *PACTIVATION_CONTEXT_DATA_COM_PROGID_REDIRECTION;

typedef const ACTIVATION_CONTEXT_DATA_COM_PROGID_REDIRECTION *PCACTIVATION_CONTEXT_DATA_COM_PROGID_REDIRECTION;

#include "poppack.h"

#if defined(__cplusplus)
} /* extern "C" */
#endif

#endif /* _SXSTYPES_ */
