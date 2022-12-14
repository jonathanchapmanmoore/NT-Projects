/*
**++
**
** Copyright (c) 2006  Microsoft Corporation
**
**
** Module Name:
**
**	    swriter.h
**
**
** Abstract:
**
**	Demonstrate a  writer
**
*/

#ifndef _SWRITER_H_
#define _SWRITER_H_

///////////////////////////////////////////////////////////////////////////////
// Declarations and Definitions

// This GUID identifies the writer
static const VSS_ID DepWriterId = 
	{ 0x079462f1, 0x1079, 0x48dd, { 0xb3, 0xfb, 0xcc, 0xb2, 0xf2, 0x93, 0x4e, 0xcf } };

static const wchar_t* const  DepWriterName = L"MSDNSampleWriter";

///////////////////////////////////////////////////////////////////////////////
// DepWriter class

class DepWriter : public CVssWriter    {
private:
public:
    // initialize all static variables
    static void StaticInitialize()  {  }
    
    DepWriter() { }
    virtual ~DepWriter() { Uninitialize(); }

    HRESULT STDMETHODCALLTYPE Initialize();
    HRESULT STDMETHODCALLTYPE Uninitialize()    { return Unsubscribe(); }
    bool STDMETHODCALLTYPE OnIdentify(IN IVssCreateWriterMetadata *pMetadata);
    bool STDMETHODCALLTYPE OnPrepareBackup(IN IVssWriterComponents *pComponents);
    bool STDMETHODCALLTYPE OnPrepareSnapshot();
    bool STDMETHODCALLTYPE OnFreeze();
    bool STDMETHODCALLTYPE OnThaw();
    bool STDMETHODCALLTYPE OnPostSnapshot(IN IVssWriterComponents *pComponents);
    bool STDMETHODCALLTYPE OnAbort();
    bool STDMETHODCALLTYPE OnBackupComplete(IN IVssWriterComponents *pComponents);
    bool STDMETHODCALLTYPE OnBackupShutdown(IN VSS_ID SnapshotSetId);
    bool STDMETHODCALLTYPE OnPreRestore(IN IVssWriterComponents *pComponents);
    bool STDMETHODCALLTYPE OnPostRestore(IN IVssWriterComponents *pComponents);
};


#endif
	
