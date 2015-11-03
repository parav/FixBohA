#include "main.h"

#define TRXN(N, p1, p2, p3, p4, p5, p6, p7, p8, p9,p10)		TRACEN(MyDirect3DIndexBuffer8,N,p1,p2,p3,p4,p5,p6,p7,p8,p9,p10)
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


MyDirect3DIndexBuffer8::MyDirect3DIndexBuffer8(MyDirect3DDevice8 *device, UINT Length, DWORD Usage, D3DFORMAT Format, D3DPOOL Pool) : pD3D(device), ptr( nullptr ), length( Length )  {
	TRX5(device, Length, Usage, Format, Pool);
	pD3D->AddRef();
	lockedData = new UCHAR[Length];
	isBufferLocked = false;
	if (FAILED(device->__CreateIndexBuffer(Length, /*Usage*/ D3DUSAGE_DYNAMIC, Format, Pool, &ptr)))
		ptr = nullptr;
}
MyDirect3DIndexBuffer8::~MyDirect3DIndexBuffer8() {
	TRX();
	pD3D->Release();
	delete[] lockedData;
}
bool MyDirect3DIndexBuffer8::WasInit() {
	return ptr != nullptr;
}

void MyDirect3DIndexBuffer8::TryUnlockBuffer() {
	//if (!isBufferLocked) {
	//	return;
	//}
	BYTE *data;
	if (SUCCEEDED(ptr->Lock(0, 0, &data, D3DLOCK_DISCARD))) {
		memcpy(data, lockedData, length);
		ptr->Unlock();
		isBufferLocked = false;
	}
}

/*** IUnknown methods ***/
STDFUNC(MyDirect3DIndexBuffer8::QueryInterface)(THIS_ REFIID riid, void** ppvObj) {
	TRX2(riid, ppvObj);
	return ptr->QueryInterface(riid, ppvObj);
}
STDFUNC_(ULONG, MyDirect3DIndexBuffer8::AddRef)(THIS) {
	TRX();
	return ptr->AddRef();
}
STDFUNC_(ULONG, MyDirect3DIndexBuffer8::Release)(THIS) {
	TRX();
	auto counter = ptr->Release();
	if (counter == 0)
		delete this;
	return counter;
}

/*** IDirect3DResource8 methods ***/
STDFUNC(MyDirect3DIndexBuffer8::GetDevice)(THIS_ IDirect3DDevice8** ppDevice) {
	TRX1(ppDevice);
	*ppDevice = pD3D;
	return S_OK;
}
STDFUNC(MyDirect3DIndexBuffer8::SetPrivateData)(THIS_ REFGUID refguid, CONST void* pData, DWORD SizeOfData, DWORD Flags) {
	TRX4(refguid, pData, SizeOfData, Flags);
	return ptr->SetPrivateData(refguid, pData, SizeOfData, Flags);
}
STDFUNC(MyDirect3DIndexBuffer8::GetPrivateData)(THIS_ REFGUID refguid, void* pData, DWORD* pSizeOfData) {
	TRX3(refguid, pData, pSizeOfData);
	return ptr->GetPrivateData(refguid, pData, pSizeOfData);
}
STDFUNC(MyDirect3DIndexBuffer8::FreePrivateData)(THIS_ REFGUID refguid) {
	TRX1(refguid);
	return ptr->FreePrivateData(refguid);
}
STDFUNC_(DWORD, MyDirect3DIndexBuffer8::SetPriority)(THIS_ DWORD PriorityNew) {
	TRX1(PriorityNew);
	return ptr->SetPriority(PriorityNew);
}
STDFUNC_(DWORD, MyDirect3DIndexBuffer8::GetPriority)(THIS) {
	TRX();
	return ptr->GetPriority();
}
STDFUNC_(void, MyDirect3DIndexBuffer8::PreLoad)(THIS) {
	TRX();
	return ptr->PreLoad();
}
STDFUNC_(D3DRESOURCETYPE, MyDirect3DIndexBuffer8::GetType)(THIS) {
	TRX();
	return ptr->GetType();
}
STDFUNC(MyDirect3DIndexBuffer8::Lock)(THIS_ UINT OffsetToLock, UINT SizeToLock, BYTE** ppbData, DWORD Flags) {
	TRX4(OffsetToLock, SizeToLock, ppbData, Flags);
	TryUnlockBuffer();
	isBufferLocked = true;
	*ppbData = lockedData;
	return S_OK;
	return ptr->Lock(OffsetToLock, SizeToLock, ppbData, Flags);
}
STDFUNC(MyDirect3DIndexBuffer8::Unlock)(THIS) {
	TRX();
	return S_OK;
	return ptr->Unlock();
}
STDFUNC(MyDirect3DIndexBuffer8::GetDesc)(THIS_ D3DINDEXBUFFER_DESC *pDesc) {
	TRX1(pDesc);
	return ptr->GetDesc(pDesc);
}
