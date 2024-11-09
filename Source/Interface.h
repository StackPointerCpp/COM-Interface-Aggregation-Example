#pragma once

// Resource file
#include "pch.h"

// Windows 8 minimum required
#if WINVER >= _WIN32_WINNT_WIN8

// Check if interface is defined
#ifndef IFace_INTERFACE_DEFINED
#define IFace_INTERFACE_DEFINED

// C++ compiler linkage
extern "C++"
{
	// Declare IFace interface
	__interface DECLSPEC_INTERFACE("FFFF0000-AA00-BB00-CC00-ABCDEF000001") IFace :public IUnknown
	{
		// Sample IFace virtual methods
		HRESULT FirstSampleMethod(UINT something) = 0;
		HRESULT SecondSampleMethod(UINT something) = 0;
		HRESULT ThirdSampleMethod(UINT something) = 0;
	};

	// Define classes for COM interface aggregation
	// Outer object: exposes interfaces of the inner object
	class FaceOuter :public IUnknown
	{
		// Outer object reference count
		ULONG m_nRefCount;

		// IUnknown controller
		IUnknown* m_pUnknownController;

		// Inner object: implements IFace interface method
		class FaceInner :public IFace
		{
			// Specifies a friendship relationship with the outer object
			friend class FaceOuter;

		private:
			// Interface reference count for debugging
			ULONG m_nRefCount;

			// Controller for inner object's reference count
			IUnknown* m_pUnknownController;

		public:
			// Inner class constructor
			FaceInner() :m_nRefCount(1), m_pUnknownController(NULL) { NOTIMPL }

			// Delegate QueryInterface method implementation to the outer object
			inline STDMETHODIMP QueryInterface(const IID& iid, void** ppv);

			// Delegate AddRef method implementation to the outer object
			inline STDMETHODIMP_(ULONG) AddRef();

			// Delegate Release method implementation to the outer object
			inline STDMETHODIMP_(ULONG) Release();

			// Override and implement IFace's FirstSampleMethod
			HRESULT FirstSampleMethod(UINT something) override;

			// Override and implement IFace's SecondSampleMethod
			HRESULT SecondSampleMethod(UINT something) override;

			// Override and implement IFace's ThirdSampleMethod
			HRESULT ThirdSampleMethod(UINT something) override;

			// Inner class constructor is default
			~FaceInner() = default;
		};
		
		// Inner class object
		FaceInner m_inner;

	public:
		// Delete default outer class destructor because IUnknown controller pointer is required
		FaceOuter() = delete;

		// Outer class constructor
		FaceOuter(IUnknown* pUnknownController) :m_nRefCount(1), m_pUnknownController(pUnknownController) { NOTIMPL }

		// Static method to create an interface
		static HRESULT Create(IUnknown* pUnknown, const IID& iid, void** ppv);

		// QueryInterface method's full implementation
		STDMETHODIMP QueryInterface(const IID& iid, void** ppv);

		// AddRef method's full implementation
		STDMETHODIMP_(ULONG) AddRef();

		// Release method's full implementation
		STDMETHODIMP_(ULONG) Release();

		// Outer class constructor is default
		~FaceOuter() = default;
	};

	// Interface identifier constant
	const IID IID_IFace = __uuidof(IFace);

	HRESULT GetFace(IUnknown* pUnknown, const IID& iid, void** ppv);
};

#else // IFace_INTERFACE_DEFINED
#endif // !IFace_INTERFACE_DEFINED
#else // WINVER <= _WIN32_WINNT_WIN8
// Operative system too old
#error OS Not Supported
#endif // WINVER >= _WIN32_WINNT_WIN8