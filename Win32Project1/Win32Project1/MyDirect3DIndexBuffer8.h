#pragma once
#include "MyD3D8.h"

class MyDirect3DDevice8;
class MyDirect3DIndexBuffer8 : public IDirect3DIndexBuffer8 {
public:
	static IDirect3DIndexBuffer8 *Get(IDirect3DIndexBuffer8 *vb) {
		auto mvb = dynamic_cast<MyDirect3DIndexBuffer8*>(vb);
		if (mvb) {
			mvb->TryUnlockBuffer();
			return mvb->ptr;
		}
		return vb;
	}

	MyDirect3DIndexBuffer8(MyDirect3DDevice8 *device, UINT Length, DWORD Usage, D3DFORMAT Format, D3DPOOL Pool);
	virtual ~MyDirect3DIndexBuffer8();
	bool WasInit();
	void TryUnlockBuffer();

	/*** IUnknown methods ***/
	STDMETHOD(QueryInterface)(THIS_ REFIID riid, void** ppvObj);
	STDMETHOD_(ULONG, AddRef)(THIS);
	STDMETHOD_(ULONG, Release)(THIS);

	/*** IDirect3DResource8 methods ***/
	STDMETHOD(GetDevice)(THIS_ IDirect3DDevice8** ppDevice);
	STDMETHOD(SetPrivateData)(THIS_ REFGUID refguid, CONST void* pData, DWORD SizeOfData, DWORD Flags);
	STDMETHOD(GetPrivateData)(THIS_ REFGUID refguid, void* pData, DWORD* pSizeOfData);
	STDMETHOD(FreePrivateData)(THIS_ REFGUID refguid);
	STDMETHOD_(DWORD, SetPriority)(THIS_ DWORD PriorityNew);
	STDMETHOD_(DWORD, GetPriority)(THIS);
	STDMETHOD_(void, PreLoad)(THIS);
	STDMETHOD_(D3DRESOURCETYPE, GetType)(THIS);
	STDMETHOD(Lock)(THIS_ UINT OffsetToLock, UINT SizeToLock, BYTE** ppbData, DWORD Flags);
	STDMETHOD(Unlock)(THIS);
	STDMETHOD(GetDesc)(THIS_ D3DINDEXBUFFER_DESC *pDesc);

private:
	MyDirect3DDevice8 *pD3D;
	IDirect3DIndexBuffer8 *ptr;
	size_t length;
	UCHAR *lockedData;
	bool isBufferLocked;
};
