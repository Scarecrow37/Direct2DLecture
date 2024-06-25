#include "pch.h"
#include "D2D1Animation.h"

D2D1Animation::D2D1Animation(): _bitmap(nullptr), _refCount(1)
{
}

D2D1Animation::~D2D1Animation()
{
    if (_bitmap != nullptr) _bitmap->Release();
    _bitmap = nullptr;
}

HRESULT D2D1Animation::QueryInterface(const IID& riid, void** ppvObject)
{
    if (riid == IID_IUnknown) (*ppvObject) = static_cast<IUnknown*>(this);
    else if (riid == IID_IAnimation) *ppvObject = static_cast<ID2D1Animation*>(this);
    else
    {
        *ppvObject = nullptr;
        return E_NOINTERFACE;
    }
    AddRef();
    return S_OK;
}

ULONG D2D1Animation::AddRef()
{
    return InterlockedIncrement(&_refCount);
}

ULONG D2D1Animation::Release()
{
    const ULONG newRefCount = InterlockedDecrement(&_refCount);
    if (newRefCount == 0) delete this;
    return newRefCount;
}
