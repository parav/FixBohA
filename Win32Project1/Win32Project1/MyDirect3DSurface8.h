#pragma once
#include "MyD3D8.h"

class MyDirect3DDevice8;

class MyDirect3DSurface8 : public IDirect3DSurface8 {
public:
	static IDirect3DSurface8 *Get(IDirect3DSurface8 *surface) {
		auto my = dynamic_cast<MyDirect3DSurface8*>(surface);
		return my ? my->Get() : surface;
	}
	MyDirect3DSurface8(bool isBackBuffer, MyDirect3DDevice8 *device, IDirect3DSurface8 *surface);
	virtual ~MyDirect3DSurface8();
	IDirect3DSurface8 *Get() { return ptr; }
	void UpdateBuffer();
	void UpdateBackBufferFromProgram();

	/*** IUnknown methods ***/
	STDMETHOD(QueryInterface)(THIS_ REFIID riid, void** ppvObj);
	STDMETHOD_(ULONG, AddRef)(THIS);
	STDMETHOD_(ULONG, Release)(THIS);

	/*** IDirect3DSurface8 methods ***/
	STDMETHOD(GetDevice)(THIS_ IDirect3DDevice8** ppDevice);
	STDMETHOD(SetPrivateData)(THIS_ REFGUID refguid, CONST void* pData, DWORD SizeOfData, DWORD Flags);
	STDMETHOD(GetPrivateData)(THIS_ REFGUID refguid, void* pData, DWORD* pSizeOfData);
	STDMETHOD(FreePrivateData)(THIS_ REFGUID refguid);
	STDMETHOD(GetContainer)(THIS_ REFIID riid, void** ppContainer);
	STDMETHOD(GetDesc)(THIS_ D3DSURFACE_DESC *pDesc);
	STDMETHOD(LockRect)(THIS_ D3DLOCKED_RECT* pLockedRect, CONST RECT* pRect, DWORD Flags);
	STDMETHOD(UnlockRect)(THIS);

private:
	IDirect3DSurface8 *ptr;
	MyDirect3DDevice8 *device;
	bool isBackBuffer;

	WORD *buffer;
	UINT width, height, pitch;
};
