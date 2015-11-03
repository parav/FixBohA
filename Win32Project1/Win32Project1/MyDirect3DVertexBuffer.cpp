#include "main.h"

#define TRXN(N, p1, p2, p3, p4, p5, p6, p7, p8, p9,p10)		TRACEN(MyDirect3DVertexBuffer8,N,p1,p2,p3,p4,p5,p6,p7,p8,p9,p10)
#define TRX10(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10)		TRXN(10,p1, p2, p3, p4, p5, p6, p7, p8, p9, p10)
#define TRX9(p1, p2, p3, p4, p5, p6, p7, p8, p9)			TRXN(9,p1, p2, p3, p4, p5, p6, p7, p8, p9, "")
#define TRX8(p1, p2, p3, p4, p5, p6, p7, p8)				TRXN(8,p1, p2, p3, p4, p5, p6, p7, p8, "", "")
#define TRX7(p1, p2, p3, p4, p5, p6, p7)					TRXN(7,p1, p2, p3, p4, p5, p6, p7, "", "", "")
#define TRX6(p1, p2, p3, p4, p5, p6)						TRXN(6,p1, p2, p3, p4, p5, p6, "", "", "", "")
#define TRX5(p1, p2, p3, p4, p5)							TRXN(5,p1, p2, p3, p4, p5, "", "", "", "", "")
#define TRX4(p1, p2, p3, p4)								TRXN(4,p1, p2, p3, p4, "", "", "", "", "", "")
#define TRX3(p1, p2, p3)									TRXN(3,p1, p2, p3, "", "", "", "", "", "", "")
#define TRX2(p1, p2)										TRXN(2,p1, p2, "", "", "", "", "", "", "", "")
#define TRX1(p1)											TRXN(1,p1, "", "", "", "", "", "", "", "", "")
#define TRX()												TRXN(0,"", "", "", "", "", "", "", "", "", "")


MyDirect3DVertexBuffer8::MyDirect3DVertexBuffer8(MyDirect3DDevice8 *device, UINT Length, DWORD Usage, DWORD FVF, D3DPOOL Pool) : pD3D( device ), ptr( nullptr ) {
	TRX5(device, Length, Usage, FVF, Pool);
	pD3D->AddRef();
	length = Length;
	lockedData = new UCHAR[length]();
	pD3D->__CreateVertexBuffer(Length, /*Usage*/ D3DUSAGE_DYNAMIC, FVF, Pool, &ptr);
	isBufferLocked = false;
}
MyDirect3DVertexBuffer8::~MyDirect3DVertexBuffer8() {
	TRX();
	pD3D->Release();
	delete[] lockedData;
}
bool MyDirect3DVertexBuffer8::WasInit() {
	return ptr != nullptr;
}

void MyDirect3DVertexBuffer8::TryUnlockBuffer() {
	//if (!isBufferLocked)
	//	return;

	BYTE *data;
	if (FAILED(ptr->Lock(0, 0, &data, D3DLOCK_DISCARD)))
		return;
	memcpy(data, lockedData, length);
	ptr->Unlock();
	isBufferLocked = false;
}

///*** IUnknown methods ***/
STDFUNC(MyDirect3DVertexBuffer8::QueryInterface)(THIS_ REFIID riid, void** ppvObj) {
	TRX2(riid, ppvObj);
	return ptr->QueryInterface(riid, ppvObj);
}
STDFUNC_(ULONG, MyDirect3DVertexBuffer8::AddRef)(THIS) {
	TRX();
	return ptr->AddRef();
}
STDFUNC_(ULONG, MyDirect3DVertexBuffer8::Release)(THIS) {
	TRX();
	auto count = ptr->Release();
	if (count == 0)
		delete this;
	return count;
}
//
///*** IDirect3DResource8 methods ***/
STDFUNC(MyDirect3DVertexBuffer8::GetDevice)(THIS_ IDirect3DDevice8** ppDevice) {
	TRX1(ppDevice);
	*ppDevice = pD3D;
	return S_OK;
}
STDFUNC(MyDirect3DVertexBuffer8::SetPrivateData)(THIS_ REFGUID refguid, CONST void* pData, DWORD SizeOfData, DWORD Flags) {
	TRX4(refguid, pData, SizeOfData, Flags);
	return ptr->SetPrivateData(refguid, pData, SizeOfData, Flags);
}
STDFUNC(MyDirect3DVertexBuffer8::GetPrivateData)(THIS_ REFGUID refguid, void* pData, DWORD* pSizeOfData) {
	TRX3(refguid, pData, pSizeOfData);
	return ptr->GetPrivateData(refguid, pData, pSizeOfData);
}
STDFUNC(MyDirect3DVertexBuffer8::FreePrivateData)(THIS_ REFGUID refguid) {
	TRX1(refguid);
	return ptr->FreePrivateData(refguid);
}
STDFUNC_(DWORD, MyDirect3DVertexBuffer8::SetPriority)(THIS_ DWORD PriorityNew) {
	TRX1(PriorityNew);
	return ptr->SetPriority(PriorityNew);
}
STDFUNC_(DWORD, MyDirect3DVertexBuffer8::GetPriority)(THIS) {
	TRX();
	return ptr->GetPriority();
}
STDFUNC_(void, MyDirect3DVertexBuffer8::PreLoad)(THIS) {
	TRX();
	return ptr->PreLoad();
}
STDFUNC_(D3DRESOURCETYPE, MyDirect3DVertexBuffer8::GetType)(THIS) {
	TRX();
	return ptr->GetType();
}
STDFUNC(MyDirect3DVertexBuffer8::Lock)(THIS_ UINT OffsetToLock, UINT SizeToLock, BYTE** ppbData, DWORD Flags) {
	TRX4(OffsetToLock, SizeToLock, ppbData, Flags);
	
	//return ptr->Lock(OffsetToLock, SizeToLock, ppbData, Flags);
	
	//HRESULT hr = ptr->Lock(0, 0, ppbData, Flags);
	//if( FAILED(hr))
	//	return hr;
	//memcpy(*ppbData, lockedData, length);
	//hr = ptr->Unlock();
	//if (FAILED(hr))
	//	return hr;
	TryUnlockBuffer();
	isBufferLocked = true;
	ZeroMemory(lockedData, length);
	*ppbData = lockedData;
	return S_OK;
//	return ptr->Lock(OffsetToLock, SizeToLock, ppbData, Flags);
}

STDFUNC(MyDirect3DVertexBuffer8::Unlock)(THIS) {
	TRX();
	return S_OK;
	//return ptr->Unlock();
	//	return S_OK;
	BYTE *data;
	HRESULT hr = ptr->Lock(0, 0, &data, D3DLOCK_DISCARD);
	if( FAILED(hr))
		return hr;
	memcpy(data, lockedData, length);
	hr = ptr->Unlock();
	if (FAILED(hr))
		return hr;
	return hr;
	return ptr->Unlock();

	/*BYTE *data;
	ptr->Lock(0, 0, &data, D3DLOCK_DISCARD);
	memcpy(data, lockedData, length);
	return ptr->Unlock();*/
}
STDFUNC(MyDirect3DVertexBuffer8::GetDesc)(THIS_ D3DVERTEXBUFFER_DESC *pDesc) {
	TRX1(pDesc);
	return ptr->GetDesc(pDesc);
}

