// dllmain.cpp : Defines the entry point for the DLL application.
#include <Windows.h>
#include "ClassFactory.h"
#include <new>

// {B5E1208D-3235-44D5-ADD0-478E1A791AE1}
static const GUID CLSID_CgCompressHandler =
{ 0xb5e1208d, 0x3235, 0x44d5, { 0xad, 0xd0, 0x47, 0x8e, 0x1a, 0x79, 0x1a, 0xe1 } };




BOOL APIENTRY DllMain( HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved ){
	switch( ul_reason_for_call ){
		case DLL_PROCESS_ATTACH:
				DisableThreadLibraryCalls( hModule );
			break;
		case DLL_THREAD_ATTACH:
		case DLL_THREAD_DETACH:
		case DLL_PROCESS_DETACH:
			break;
	}
	return TRUE;
}

HRESULT __stdcall DllGetClassObject( REFCLSID objGuid, REFIID riid, void **ppv ){
	*ppv = NULL;
	
	if( IsEqualCLSID( objGuid, CLSID_CgCompressHandler ) ) {
		ClassFactory *factory = new (std::nothrow) ClassFactory();
		if( !factory )
			return E_OUTOFMEMORY;

		factory->AddRef();
		HRESULT hr = factory->QueryInterface( riid, ppv );
		factory->Release();
		return hr;
	}
	else
		return CLASS_E_CLASSNOTAVAILABLE;
}

HRESULT __stdcall DllCanUnloadNow(){
	return (ClassFactory::dll_ref>0) ? S_FALSE : S_OK;
}

