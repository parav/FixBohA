#include "main.h"
#include <numeric>
#define TRXN(N, p1, p2, p3, p4, p5, p6, p7, p8)				TRACEN(MyDirect3DSurface8,N,p1,p2,p3,p4,p5,p6,p7,p8, "", "")
//#define TRXN(N, p1, p2, p3, p4, p5, p6, p7, p8, p9)			TRACEN(MyDirect3DDevice8,N+1,++command,p1,p2,p3,p4,p5,p6,p7,p8,p9)
//#define TRX10(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10)		TRXN(10,p1, p2, p3, p4, p5, p6, p7, p8, p9, p10)
//#define TRX9(p1, p2, p3, p4, p5, p6, p7, p8, p9)			TRXN(9,p1, p2, p3, p4, p5, p6, p7, p8, p9, "")
#define TRX8(p1, p2, p3, p4, p5, p6, p7, p8)				TRXN(8,p1, p2, p3, p4, p5, p6, p7, p8)
#define TRX7(p1, p2, p3, p4, p5, p6, p7)					TRXN(7,p1, p2, p3, p4, p5, p6, p7, "")
#define TRX6(p1, p2, p3, p4, p5, p6)						TRXN(6,p1, p2, p3, p4, p5, p6, "", "")
#define TRX5(p1, p2, p3, p4, p5)							TRXN(5,p1, p2, p3, p4, p5, "", "", "")
#define TRX4(p1, p2, p3, p4)								TRXN(4,p1, p2, p3, p4, "", "", "", "")
#define TRX3(p1, p2, p3)									TRXN(3,p1, p2, p3, "", "", "", "", "")
#define TRX2(p1, p2)										TRXN(2,p1, p2, "", "", "", "", "", "")
#define TRX1(p1)											TRXN(1,p1, "", "", "", "", "", "", "")
#define TRX()												TRXN(0,"", "", "", "", "", "", "", "")

const WORD skipColor = static_cast<WORD>( ((255>>3)<<1)|(255>>3) );

MyDirect3DSurface8::MyDirect3DSurface8( bool isBackBuffer, MyDirect3DDevice8 *device, IDirect3DSurface8 *surface ) : ptr( surface ), device( device ), isBackBuffer( isBackBuffer ) {
	TRX2(isBackBuffer, device);
	device->AddRef();

	D3DSURFACE_DESC desc = {};
	desc.Size = sizeof(desc);
	ptr->GetDesc(&desc);
	width = desc.Width;
	height = desc.Height;
	pitch = ((width+15)&(std::numeric_limits<UINT>::max() - 15))*sizeof(WORD);		// pitch round up to 32 bytes
	buffer = new WORD[pitch*height/sizeof(WORD)]();
}

MyDirect3DSurface8::~MyDirect3DSurface8() {
	TRX();
	delete[] buffer;
	device->Release();
}

void MyDirect3DSurface8::UpdateBuffer() {
	D3DLOCKED_RECT rc;
	ptr->LockRect(&rc, nullptr, D3DLOCK_READONLY);
	WORD *dest = buffer;
	DWORD *source = reinterpret_cast<DWORD*>(rc.pBits);

	for (UINT y = 0; y < height; ++y) {
		for (UINT x = 0; x < width; ++x) {
			dest[x] = rgb32to16(source[x]);
		}
		dest += pitch / sizeof(WORD);
		source += rc.Pitch / sizeof(DWORD);
	}

	ptr->UnlockRect();
}

void MyDirect3DSurface8::UpdateBackBufferFromProgram() {
	D3DLOCKED_RECT rc;
	HRESULT hr = ptr->LockRect(&rc, nullptr, 0);
	if( FAILED( hr ) )
		return;

	WORD *source = buffer;
	DWORD *dest = reinterpret_cast<DWORD*>(rc.pBits);
	for (UINT y = 0; y < height; ++y) {
		for (UINT x = 0; x < width; ++x) {
			if(source[x] == skipColor )
				continue;
			if (source[x] == (120 >> 3)) {
				dest[x] = (120 >> 6);
			}
			else
				dest[x] = rgb16to32(source[x]);
		}
		source += pitch / sizeof(WORD);
		dest += rc.Pitch / sizeof(DWORD);
	}

	ptr->UnlockRect();
}

STDFUNC(MyDirect3DSurface8::QueryInterface)(THIS_ REFIID riid, void** ppvObj) {
	TRX2(riid, ppvObj);
	if (::IsEqualGUID(riid, IID_IDirect3DDevice8)) {
		*ppvObj = device;
		device->AddRef();
		return S_OK;
	}
	if (::IsEqualGUID(riid, IID_IDirect3D8)) {
		return device->QueryInterface(riid, ppvObj);
	}
	return ptr->QueryInterface(riid, ppvObj);
}
STDFUNC_(ULONG, MyDirect3DSurface8::AddRef)(THIS) {
	TRX();
	return ptr->AddRef();
}
STDFUNC_(ULONG, MyDirect3DSurface8::Release)(THIS) {
	TRX();
	auto counter = ptr->Release();
	if (counter == 0)
		delete this;
	return counter;
}

/*** IDirect3DSurface8 methods ***/
STDFUNC(MyDirect3DSurface8::GetDevice)(THIS_ IDirect3DDevice8** ppDevice) {
	TRX1(ppDevice);
	*ppDevice = device;
	device->AddRef();
	return S_OK;
}
STDFUNC(MyDirect3DSurface8::SetPrivateData)(THIS_ REFGUID refguid, CONST void* pData, DWORD SizeOfData, DWORD Flags) {
	TRX4(refguid, pData, SizeOfData, Flags);
	return ptr->SetPrivateData(refguid, pData, SizeOfData, Flags);
}
STDFUNC(MyDirect3DSurface8::GetPrivateData)(THIS_ REFGUID refguid, void* pData, DWORD* pSizeOfData) {
	TRX3(refguid, pData, pSizeOfData);
	return ptr->GetPrivateData(refguid, pData, pSizeOfData);
}
STDFUNC(MyDirect3DSurface8::FreePrivateData)(THIS_ REFGUID refguid) {
	TRX1(refguid);
	return ptr->FreePrivateData(refguid);
}
STDFUNC(MyDirect3DSurface8::GetContainer)(THIS_ REFIID riid, void** ppContainer) {
	TRX2(riid, ppContainer);
	return ptr->GetContainer(riid, ppContainer);
}
STDFUNC(MyDirect3DSurface8::GetDesc)(THIS_ D3DSURFACE_DESC *pDesc) {
	TRX1(pDesc);
	return ptr->GetDesc(pDesc);
}

STDFUNC(MyDirect3DSurface8::LockRect)(THIS_ D3DLOCKED_RECT* pLockedRect, CONST RECT* pRect, DWORD Flags) {
	TRX3(pLockedRect, pRect, Flags);
	UpdateBackBufferFromProgram();
	for (UINT y = 0; y < height; ++y) {
		for (UINT x = 0; x < width; ++x) {
			buffer[x + y*pitch / sizeof(WORD)] = skipColor;
		}
	}

//	return ptr->LockRect(pLockedRect, pRect, Flags);
//	memcpy(copyBuffer, buffer, pitch*height);
	//if( GetAsyncKeyState(VK_F1))
	//	UpdateBuffer();
	//if (GetAsyncKeyState(VK_F2))
	//	ZeroMemory(buffer, pitch*height);
	//if (GetAsyncKeyState(VK_F3))
	//{
	//	for (UINT y = 0; y < height; ++y) {
	//		for (UINT x = 0; x < width; ++x) {
	//			buffer[x + y*pitch / sizeof(WORD)] = static_cast<WORD>( 0xFFFF );
	//		}
	//	}
	//}

	pLockedRect->pBits = pRect ? ( buffer + pRect->left + pRect->top * pitch / sizeof(WORD) ) : buffer;
	pLockedRect->Pitch = pitch;
	return S_OK;
}
STDFUNC(MyDirect3DSurface8::UnlockRect)(THIS) {
	TRX();
	return S_OK;
	//if (GetAsyncKeyState(VK_F4))
	//	return S_OK;
	//return ptr->UnlockRect();
	//D3DLOCKED_RECT rc;
	//HRESULT hr = ptr->LockRect(&rc, nullptr, 0);
	//if( FAILED( hr ) )
	//	return hr;

	//WORD *source = buffer;
	//DWORD *dest = reinterpret_cast<DWORD*>(rc.pBits);
	//for (UINT y = 0; y < height; ++y) {
	//	for (UINT x = 0; x < width; ++x) {
	//		//if (source[x] != copyBuffer[x + y*pitch / sizeof(WORD)])
	//		//	continue;
	//		DWORD color = rgb16to32(source[x]);
	//		dest[x] = color;
	//	}
	//	source += pitch / sizeof(WORD);
	//	dest += rc.Pitch / sizeof(DWORD);
	//}

	//return ptr->UnlockRect();
}
