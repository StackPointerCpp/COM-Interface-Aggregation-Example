#include "Interface.h"

inline STDMETHODIMP FaceOuter::FaceInner::QueryInterface(const IID& iid, void** ppv)
{
    // Return default QueryInterface method result
    return m_pUnknownController->QueryInterface(iid, ppv);
}

inline STDMETHODIMP_(ULONG) FaceOuter::FaceInner::AddRef()
{
    // Return default AddRef method result
    return m_pUnknownController->AddRef();
}

inline STDMETHODIMP_(ULONG) FaceOuter::FaceInner::Release()
{
    // Return default Release method result
    return m_pUnknownController->Release();
}

HRESULT FaceOuter::FaceInner::FirstSampleMethod(UINT something)
{
    // Print current method name
    std::cout << "Method " << __func__ << " called!" << std::endl;

    // Check whether parameter is greater than reference count
    if (something > m_nRefCount)
    {
        // Return missing interface error
        return E_NOINTERFACE;
    }

    // Resturn success
    return S_OK;
}

HRESULT FaceOuter::FaceInner::SecondSampleMethod(UINT something)
{
    // Print current method name
    std::cout << "Method " << __func__ << " called!" << std::endl;

    // Check whether parameter is equal to reference count
    if (something == m_nRefCount)
    {
        // Return missing interface error
        return E_NOINTERFACE;
    }

    // Resturn success
    return S_OK;
}

HRESULT FaceOuter::FaceInner::ThirdSampleMethod(UINT something)
{
    // Print current method name
    std::cout << "Method " << __func__ << " called!" << std::endl;

    // Check whether parameter is less than reference count
    if (something < m_nRefCount)
    {
        // Return missing interface error
        return E_NOINTERFACE;
    }

    // Resturn success
    return S_OK;
}

HRESULT FaceOuter::Create(IUnknown* pUnknown, const IID& iid, void** ppv)
{
    // Method result
    HRESULT hr = S_OK;

    // Check if IUnknown pointer parameter and interface identifier is invalid
    if (pUnknown && iid != IID_IUnknown)
    {
        // Impossible to aggregate classes
        return CLASS_E_NOAGGREGATION;
    }

    // Initialize outer class pointer
    FaceOuter* pOuter = new FaceOuter(pUnknown);
    if (!pOuter)
    {
        // Failed outer pointer allocation
        return E_OUTOFMEMORY;
    }

    // Initialize IUnknown controller in both classes
    pOuter->m_pUnknownController = reinterpret_cast<IUnknown*>(pOuter);
    pOuter->m_inner.m_pUnknownController = reinterpret_cast<IUnknown*>(pOuter);

    // Call outer object's QuieryInterface method to initialize void** parameter, that is the interface reference
    hr = pOuter->QueryInterface(iid, ppv);
    if (FAILED(hr))
    {
        // Deallocate outer object's pointer
        delete pOuter;
    }

    // Return QuieryInterface call result
    return hr;
}

STDMETHODIMP FaceOuter::QueryInterface(const IID& iid, void** ppv)
{
    // IUnknown case: IUnknown interface need the outer object
    if (iid == IID_IUnknown) *ppv = this;

    // Create a table conteining all queryable interfaces
    QITAB qiTab[] = {
        QITABENT(FaceOuter, IUnknown),
        QITABENT(FaceOuter, IFace),
        QUERYINTERFACETABLE_TERMINATOR_VALUE,
    };

    // Return interface search result
    return QISearch(&m_inner, qiTab, iid, ppv);
}

STDMETHODIMP_(ULONG) FaceOuter::AddRef()
{
    // Return new reference count
    return InterlockedIncrement(&m_nRefCount);
}

STDMETHODIMP_(ULONG) FaceOuter::Release()
{
    // Save new reference count
    ULONG newRefCount = InterlockedDecrement(&m_nRefCount);

    // Check if new reference count is zero
    if (!newRefCount)
    {
        // Deallocate outer object that represent the entire interface
        delete this;
    }

    // Return new reference count
    return newRefCount;
}

HRESULT GetFace(IUnknown* pUnknown, const IID& iid, void** ppv)
{
    // Return the creation interface result
    return FaceOuter::Create(pUnknown, iid, ppv);
}
