#pragma once

// Windows header
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif // !WIN32_LEAN_AND_MEAN

// Windows
#include <Windows.h>
#include <ShlObj.h>
#include <Shlwapi.h>

// COM Headers
#include <comdef.h>
#include <Unknwn.h>

// C Runtime
#include <memory.h>
#include <stdio.h>
#include <math.h>
#include <iostream>
#include <tchar.h>

// Graphics
#include <d2d1_3.h>
#include <d2d1_3helper.h>
#include <dxgi1_6.h>
#include <dxgidebug.h>
#include <d3d11_4.h>
#include <d3d12.h>
#include <dwrite_3.h>
#include <wincodec.h>

// Library for compile
#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3d12.lib")
#pragma comment(lib, "Shlwapi.lib")

// Macros definition
#define NONE /* Empty */
#define NOTIMPL /* Empty */
#define DECLSPEC_INTERFACE(x) __declspec(novtable) __declspec(uuid(x))
#define QUERYINTERFACETABLE_TERMINATOR_VALUE { NULL, NULL }
#define DECLGETIFACEPTR(name,_class) HRESULT Get##name##Interface(IUnknown* pUnknownOuter, const IID& iid, void** ppv) {return _class::Create(pUnknownOuter, iid, ppv);}

// Safe release function
template <class Interface>
void SafeRelease(Interface** ppInterface)
{
	// Check wheder interface is valid
	if (ppInterface)
	{
		// Release the interface and invalidate its pointer
		(*ppInterface)->Release();
		(*ppInterface) = NULL;
	}

	// Exit
	return NONE;
}