#pragma once
#define _WIN32_WINNT 0x0501
#define _WIN32_DCOM
#include "..\..\ApplicationPlugin.h"
#include "..\..\CaptureGlobal.h"
//#include "..\ComHelper.h"
#include <Exdisp.h>
#include <comutil.h>
#include <exdispid.h>
#include <objbase.h>
#include <psapi.h>
#include <shlwapi.h>
#import <shdocvw.dll> 

class InternetExplorerInstanceBulk : DWebBrowserEvents2 
{
public:
	InternetExplorerInstanceBulk(std::wstring fullPathToExe);
	~InternetExplorerInstanceBulk(void);
	DWORD executeProcess();
	void visitUrl(Url* url);
	bool isOpen();
	DWORD getProcessId(void);
	bool close(void);

	DWORD major;
	DWORD minor;
	bool exited;
private:
	HANDLE hVisiting;
	bool bNetworkError;
	DWORD dwNetworkErrorCode;
	IWebBrowser2* pInternetExplorer;
	bool open;
	_variant_t mainURL;
	PROCESS_INFORMATION m_piProcessInfo;
	std::wstring m_fullPathToExe;
	bool setCurrentWebBrowserIF(void);
	BOOL static CALLBACK EnumWindowsCloseProc(HWND hwnd,LPARAM lParam);


	bool Close();

private:
	/* Below are various methods we must implement for DWebBrowserEvents.
	   Just ignore most of them as they are just stubs. The important ones
	   are implemented in Application_InternetExplorer.cpp */
	HRESULT STDMETHODCALLTYPE QueryInterface( 
                /* [in] */ REFIID riid,
                /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject)
	{
		if (IsEqualIID(riid, IID_IUnknown) || IsEqualIID(riid, DIID_DWebBrowserEvents2))
		{
			*ppvObject = this;
			return(NOERROR);
		}
		*ppvObject = 0;
		return(E_NOINTERFACE);
	}
	ULONG STDMETHODCALLTYPE AddRef( void)
	{
		return(1);
	}
            
    ULONG STDMETHODCALLTYPE Release( void)
	{
		return(1);
	}
	HRESULT STDMETHODCALLTYPE GetTypeInfoCount( 
            /* [out] */ UINT *pctinfo)
	{
		return(NOERROR);
	}
        
    HRESULT STDMETHODCALLTYPE GetTypeInfo( 
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo)
	{
		return(NOERROR);
	}
        
    HRESULT STDMETHODCALLTYPE GetIDsOfNames( 
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId)
	{
		return(NOERROR);
	}
        
     HRESULT STDMETHODCALLTYPE Invoke( 
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
};
