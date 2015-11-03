//TODO: Вставить Get для VertexBuffer

#include "main.h"
#include <malloc.h>		// for _alligned_malloc
#define TRXN(N, p1, p2, p3, p4, p5, p6, p7, p8)				TRACEN(MyDirect3DDevice8,N+2,frame,++command,p1,p2,p3,p4,p5,p6,p7,p8)
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


bool IsMatricesDifferent(D3DMATRIX &a, D3DMATRIX &b) {
	float e = std::numeric_limits<float>::epsilon();
	return fabsf(a._11 - b._11) > e ||
		fabsf(a._12 - b._12) > e ||
		fabsf(a._13 - b._13) > e ||
		fabsf(a._14 - b._14) > e ||
		fabsf(a._21 - b._21) > e ||
		fabsf(a._22 - b._22) > e ||
		fabsf(a._23 - b._23) > e ||
		fabsf(a._24 - b._24) > e ||
		fabsf(a._31 - b._31) > e ||
		fabsf(a._32 - b._32) > e ||
		fabsf(a._33 - b._33) > e ||
		fabsf(a._34 - b._34) > e ||
		fabsf(a._41 - b._41) > e ||
		fabsf(a._42 - b._42) > e ||
		fabsf(a._43 - b._43) > e ||
		fabsf(a._44 - b._44) > e;
}

MyDirect3DDevice8::MyDirect3DDevice8(MyDirect3D8 *d3d8, UINT Adapter, D3DDEVTYPE DeviceType, HWND hFocusWindow, DWORD BehaviorFlags, D3DPRESENT_PARAMETERS* pPresentationParameters) : ptr( nullptr ), pD3D (d3d8), frame(0), command(0), hWnd( hFocusWindow ) {
	TRX1(d3d8)
	pD3D->AddRef();

	HRESULT hr = d3d8->__CreateDevice(Adapter, DeviceType, hFocusWindow, BehaviorFlags, pPresentationParameters, &ptr);
	if (FAILED(hr) || !ptr) {
		ptr = nullptr;
	}
}

MyDirect3DDevice8::~MyDirect3DDevice8() {
	TRX();
	pD3D->Release();
}

bool MyDirect3DDevice8::WasInit() {
//	TRX();
	return ptr != nullptr;
}

void MyDirect3DDevice8::SaveCurrentBackBuffer() {
	TRX1("!!!Not Implemented!!!");
}

HRESULT MyDirect3DDevice8::__CreateVertexBuffer(THIS_ UINT Length, DWORD Usage, DWORD FVF, D3DPOOL Pool, IDirect3DVertexBuffer8** ppVertexBuffer) {
	return ptr->CreateVertexBuffer(Length, Usage, FVF, Pool, ppVertexBuffer);
}

HRESULT MyDirect3DDevice8::__CreateIndexBuffer(THIS_ UINT Length, DWORD Usage, D3DFORMAT Format, D3DPOOL Pool, IDirect3DIndexBuffer8** ppIndexBuffer) {
	return ptr->CreateIndexBuffer(Length, Usage, Format, Pool, ppIndexBuffer);
}


//	/*** IUnknown methods ***/
STDFUNC(MyDirect3DDevice8::QueryInterface)(THIS_ REFIID riid, void** ppvObj)
{
	TRX2(riid, ppvObj);
	if (::IsEqualGUID(riid, IID_IDirect3D8)) {
		*ppvObj = pD3D;
		pD3D->AddRef();
		return S_OK;
	}
	return ptr->QueryInterface(riid, ppvObj);
}
STDFUNC_(ULONG, MyDirect3DDevice8::AddRef)(THIS) {
	TRX();
	return ptr->AddRef();
}
STDFUNC_(ULONG, MyDirect3DDevice8::Release)(THIS) {
	TRX();
	auto count = ptr->Release();
	if (count == 0)
		delete this;
	return count;
}
//
//	/*** IDirect3DDevice8 methods ***/
STDFUNC(MyDirect3DDevice8::TestCooperativeLevel)(THIS) {
	TRX();
	return ptr->TestCooperativeLevel();
}
STDFUNC_(UINT, MyDirect3DDevice8::GetAvailableTextureMem)(THIS) {
	TRX();
	return ptr->GetAvailableTextureMem();
}
STDFUNC(MyDirect3DDevice8::ResourceManagerDiscardBytes)(THIS_ DWORD Bytes) {
	TRX1(Bytes);
	return ptr->ResourceManagerDiscardBytes(Bytes);
}
STDFUNC(MyDirect3DDevice8::GetDirect3D)(THIS_ IDirect3D8** ppD3D8) {
	TRX1(ppD3D8);
	*ppD3D8 = pD3D;
	return S_OK;
}
STDFUNC(MyDirect3DDevice8::GetDeviceCaps)(THIS_ D3DCAPS8* pCaps) {
	TRX1(pCaps);
	return ptr->GetDeviceCaps(pCaps);
}
STDFUNC(MyDirect3DDevice8::GetDisplayMode)(THIS_ D3DDISPLAYMODE* pMode) {
	TRX1(pMode);
	return ptr->GetDisplayMode(pMode);
}
STDFUNC(MyDirect3DDevice8::GetCreationParameters)(THIS_ D3DDEVICE_CREATION_PARAMETERS *pParameters) {
	TRX1(pParameters);
	return ptr->GetCreationParameters(pParameters);
}
STDFUNC(MyDirect3DDevice8::SetCursorProperties)(THIS_ UINT XHotSpot, UINT YHotSpot, IDirect3DSurface8* pCursorBitmap) {
	TRX3(XHotSpot, YHotSpot, pCursorBitmap);
	return ptr->SetCursorProperties(XHotSpot, YHotSpot, MyDirect3DSurface8::Get(pCursorBitmap));
}
STDFUNC_(void, MyDirect3DDevice8::SetCursorPosition)(THIS_ UINT XScreenSpace, UINT YScreenSpace, DWORD Flags) {
	TRX3(XScreenSpace, YScreenSpace, Flags);
	return ptr->SetCursorPosition(XScreenSpace, YScreenSpace, Flags);
}
STDFUNC_(BOOL, MyDirect3DDevice8::ShowCursor)(THIS_ BOOL bShow) {
	TRX1(bShow);
	return ptr->ShowCursor(/*bShow*/TRUE);
}
STDFUNC(MyDirect3DDevice8::CreateAdditionalSwapChain)(THIS_ D3DPRESENT_PARAMETERS* pPresentationParameters, IDirect3DSwapChain8** pSwapChain) {
	TRX2(pPresentationParameters, pSwapChain);
	return ptr->CreateAdditionalSwapChain(pPresentationParameters, pSwapChain);
}
STDFUNC(MyDirect3DDevice8::Reset)(THIS_ D3DPRESENT_PARAMETERS* pPresentationParameters) {
	TRX1(pPresentationParameters);
	return ptr->Reset(pPresentationParameters);
}
STDFUNC(MyDirect3DDevice8::Present)(THIS_ CONST RECT* pSourceRect, CONST RECT* pDestRect, HWND hDestWindowOverride, CONST RGNDATA* pDirtyRegion) {
	TRX4(pSourceRect, pDestRect, hDestWindowOverride, pDirtyRegion);
	++frame;
	command = 0;

#ifdef _DEBUG
	if(wasTraced) {
		wasTraced = false;
		std::ostringstream out;
		out << "=== " << frame << "===" << std::endl;
		OutputDebugStringA(out.str().c_str());
	}
#endif
	HRESULT hr = ptr->Present(pSourceRect, pDestRect, hDestWindowOverride, pDirtyRegion);
		return hr;
}
STDFUNC(MyDirect3DDevice8::GetBackBuffer)(THIS_ UINT BackBuffer, D3DBACKBUFFER_TYPE Type, IDirect3DSurface8** ppBackBuffer) {
	// TODO: Watch at backbuffer and replace it interface
	TRX3(BackBuffer, Type, ppBackBuffer);
	HRESULT hr = ptr->GetBackBuffer(BackBuffer, Type, ppBackBuffer);
	if (FAILED(hr)) {
		*ppBackBuffer = nullptr;
		return hr;
	}
	
	*ppBackBuffer = new MyDirect3DSurface8(true, this, *ppBackBuffer);
	return hr;
}
STDFUNC(MyDirect3DDevice8::GetRasterStatus)(THIS_ D3DRASTER_STATUS* pRasterStatus) {
	TRX1(pRasterStatus);
	return ptr->GetRasterStatus(pRasterStatus);
}
STDFUNC_(void, MyDirect3DDevice8::SetGammaRamp)(THIS_ DWORD Flags, CONST D3DGAMMARAMP* pRamp) {
	TRX2(Flags, pRamp);
	return ptr->SetGammaRamp(Flags, pRamp);
}
STDFUNC_(void, MyDirect3DDevice8::GetGammaRamp)(THIS_ D3DGAMMARAMP* pRamp) {
	TRX1(pRamp);
	ptr->GetGammaRamp(pRamp);
}
STDFUNC(MyDirect3DDevice8::CreateTexture)(THIS_ UINT Width, UINT Height, UINT Levels, DWORD Usage, D3DFORMAT Format, D3DPOOL Pool, IDirect3DTexture8** ppTexture) {
	TRX7(Width, Height, Levels, Usage, Format, Pool, ppTexture);
	return ptr->CreateTexture(Width, Height, Levels, Usage, Format, Pool, ppTexture);
}
STDFUNC(MyDirect3DDevice8::CreateVolumeTexture)(THIS_ UINT Width, UINT Height, UINT Depth, UINT Levels, DWORD Usage, D3DFORMAT Format, D3DPOOL Pool, IDirect3DVolumeTexture8** ppVolumeTexture) {
	TRX8(Width, Height, Depth, Levels, Usage, Format, Pool, ppVolumeTexture);
	return ptr->CreateVolumeTexture(Width, Height, Depth, Levels, Usage, Format, Pool, ppVolumeTexture);
}
STDFUNC(MyDirect3DDevice8::CreateCubeTexture)(THIS_ UINT EdgeLength, UINT Levels, DWORD Usage, D3DFORMAT Format, D3DPOOL Pool, IDirect3DCubeTexture8** ppCubeTexture) {
	TRX6(EdgeLength, Levels, Usage, Format, Pool, ppCubeTexture);
	return ptr->CreateCubeTexture(EdgeLength, Levels, Usage, Format, Pool, ppCubeTexture);
}
STDFUNC(MyDirect3DDevice8::CreateVertexBuffer)(THIS_ UINT Length, DWORD Usage, DWORD FVF, D3DPOOL Pool, IDirect3DVertexBuffer8** ppVertexBuffer) {
	TRX5(Length, Usage, FVF, Pool, ppVertexBuffer);
	auto vb = new MyDirect3DVertexBuffer8(this, Length, Usage, FVF, Pool);
	if( vb->WasInit()) {
		*ppVertexBuffer = vb;
		return S_OK;
	}
	*ppVertexBuffer = nullptr;
	return E_FAIL;
	//return ptr->CreateVertexBuffer(Length, Usage, FVF, Pool, ppVertexBuffer);
}
STDFUNC(MyDirect3DDevice8::CreateIndexBuffer)(THIS_ UINT Length, DWORD Usage, D3DFORMAT Format, D3DPOOL Pool, IDirect3DIndexBuffer8** ppIndexBuffer) {
	TRX5(Length, Usage, Format, Pool, ppIndexBuffer);
	MyDirect3DIndexBuffer8 *ib = new MyDirect3DIndexBuffer8(this, Length, Usage, Format, Pool);
	if (ib->WasInit()) {
		*ppIndexBuffer = ib;
		return S_OK;
	}
	delete ib;
	return E_FAIL;
//	return ptr->CreateIndexBuffer(Length, /*Usage*/ D3DUSAGE_DYNAMIC, Format, Pool, ppIndexBuffer);
}
STDFUNC(MyDirect3DDevice8::CreateRenderTarget)(THIS_ UINT Width, UINT Height, D3DFORMAT Format, D3DMULTISAMPLE_TYPE MultiSample, BOOL Lockable, IDirect3DSurface8** ppSurface) {
	TRX6(Width, Height, Format, MultiSample, Lockable, ppSurface);
	return ptr->CreateRenderTarget(Width, Height, Format, MultiSample, Lockable, ppSurface);
}
STDFUNC(MyDirect3DDevice8::CreateDepthStencilSurface)(THIS_ UINT Width, UINT Height, D3DFORMAT Format, D3DMULTISAMPLE_TYPE MultiSample, IDirect3DSurface8** ppSurface) {
	TRX5(Width, Height, Format, MultiSample, ppSurface);
	return ptr->CreateDepthStencilSurface(Width, Height, Format, MultiSample, ppSurface);
}
STDFUNC(MyDirect3DDevice8::CreateImageSurface)(THIS_ UINT Width, UINT Height, D3DFORMAT Format, IDirect3DSurface8** ppSurface) {
	TRX4(Width, Height, Format, ppSurface);
	return ptr->CreateImageSurface(Width, Height, Format, ppSurface);
}
STDFUNC(MyDirect3DDevice8::CopyRects)(THIS_ IDirect3DSurface8* pSourceSurface, CONST RECT* pSourceRectsArray, UINT cRects, IDirect3DSurface8* pDestinationSurface, CONST POINT* pDestPointsArray) {
	TRX5(pSourceSurface, pSourceRectsArray, cRects, pDestinationSurface, pDestPointsArray);
	return ptr->CopyRects(MyDirect3DSurface8::Get(pSourceSurface), pSourceRectsArray, cRects, MyDirect3DSurface8::Get(pDestinationSurface), pDestPointsArray);
}
STDFUNC(MyDirect3DDevice8::UpdateTexture)(THIS_ IDirect3DBaseTexture8* pSourceTexture, IDirect3DBaseTexture8* pDestinationTexture) {
	TRX2(pSourceTexture, pDestinationTexture);
	return ptr->UpdateTexture(pSourceTexture, pDestinationTexture);
}
STDFUNC(MyDirect3DDevice8::GetFrontBuffer)(THIS_ IDirect3DSurface8* pDestSurface) {
	TRX1(pDestSurface);
	return ptr->GetFrontBuffer(MyDirect3DSurface8::Get(pDestSurface));
}
STDFUNC(MyDirect3DDevice8::SetRenderTarget)(THIS_ IDirect3DSurface8* pRenderTarget, IDirect3DSurface8* pNewZStencil) {
	TRX2(pRenderTarget, pNewZStencil);
	return ptr->SetRenderTarget(MyDirect3DSurface8::Get(pRenderTarget), MyDirect3DSurface8::Get(pNewZStencil));
}
STDFUNC(MyDirect3DDevice8::GetRenderTarget)(THIS_ IDirect3DSurface8** ppRenderTarget) {
	TRX1(ppRenderTarget);
	return ptr->GetRenderTarget(ppRenderTarget);
}
STDFUNC(MyDirect3DDevice8::GetDepthStencilSurface)(THIS_ IDirect3DSurface8** ppZStencilSurface) {
	TRX1(ppZStencilSurface);
	return ptr->GetDepthStencilSurface(ppZStencilSurface);
}
STDFUNC(MyDirect3DDevice8::BeginScene)(THIS) {
	TRX();
	ptr->Clear(0, nullptr, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0, 1.0f, 0);

	HRESULT hr = ptr->BeginScene();
	return hr;
}
STDFUNC(MyDirect3DDevice8::EndScene)(THIS) {
	TRX();
	return ptr->EndScene();
}
STDFUNC(MyDirect3DDevice8::Clear)(THIS_ DWORD Count, CONST D3DRECT* pRects, DWORD Flags, D3DCOLOR Color, float Z, DWORD Stencil) {
	TRX6(Count, pRects, Flags, Color, Z, Stencil);
	return ptr->Clear(Count, pRects, Flags, Color, Z, Stencil);
}
STDFUNC(MyDirect3DDevice8::SetTransform)(THIS_ D3DTRANSFORMSTATETYPE State, CONST D3DMATRIX* pMatrix) {
	TRX2(State, pMatrix);
	__declspec(align(16)) D3DMATRIX copy = *pMatrix;
	HRESULT hr = ptr->SetTransform(State, &copy);
	return hr;
}
STDFUNC(MyDirect3DDevice8::GetTransform)(THIS_ D3DTRANSFORMSTATETYPE State, D3DMATRIX* pMatrix) {
	TRX2(State, pMatrix);
	__declspec(align(16)) D3DMATRIX copy;
	HRESULT hr = ptr->GetTransform(State, &copy);
	*pMatrix = copy;
	return hr;
}
STDFUNC(MyDirect3DDevice8::MultiplyTransform)(D3DTRANSFORMSTATETYPE type, CONST D3DMATRIX* pMatrix) {
	TRX2(type, pMatrix);
	__declspec(align(16)) D3DMATRIX copy = *pMatrix;
	return ptr->MultiplyTransform(type,&copy);
}
STDFUNC(MyDirect3DDevice8::SetViewport)(THIS_ CONST D3DVIEWPORT8* pViewport) {
	TRX1(pViewport);
	return ptr->SetViewport(pViewport);
}
STDFUNC(MyDirect3DDevice8::GetViewport)(THIS_ D3DVIEWPORT8* pViewport) {
	TRX1(pViewport);
	return ptr->GetViewport(pViewport);
}
STDFUNC(MyDirect3DDevice8::SetMaterial)(THIS_ CONST D3DMATERIAL8* pMaterial) {
	TRX1(pMaterial);
	return ptr->SetMaterial(pMaterial);
}
STDFUNC(MyDirect3DDevice8::GetMaterial)(THIS_ D3DMATERIAL8* pMaterial) {
	TRX1(pMaterial)
	return ptr->GetMaterial(pMaterial);
}
STDFUNC(MyDirect3DDevice8::SetLight)(THIS_ DWORD Index, CONST D3DLIGHT8* pLight) {
	TRX2(Index, pLight);
	return ptr->SetLight(Index, pLight);
}
STDFUNC(MyDirect3DDevice8::GetLight)(THIS_ DWORD Index, D3DLIGHT8* pLight) {
	TRX2(Index, pLight);
	return ptr->GetLight(Index, pLight);
}
STDFUNC(MyDirect3DDevice8::LightEnable)(THIS_ DWORD Index, BOOL Enable) {
	TRX2(Index, Enable);
	return ptr->LightEnable(Index, Enable);
}
STDFUNC(MyDirect3DDevice8::GetLightEnable)(THIS_ DWORD Index, BOOL* pEnable) {
	TRX2(Index, pEnable);
	return ptr->GetLightEnable(Index, pEnable);
}
STDFUNC(MyDirect3DDevice8::SetClipPlane)(THIS_ DWORD Index, CONST float* pPlane) {
	TRX2(Index, pPlane);
	return ptr->SetClipPlane(Index,pPlane);
}
STDFUNC(MyDirect3DDevice8::GetClipPlane)(THIS_ DWORD Index, float* pPlane)  {
	TRX2(Index, pPlane);
	return ptr->GetClipPlane(Index,pPlane);
}
STDFUNC(MyDirect3DDevice8::SetRenderState)(THIS_ D3DRENDERSTATETYPE State, DWORD Value) {
	TRX2(State, Value);
	return ptr->SetRenderState(State, Value);
}
STDFUNC(MyDirect3DDevice8::GetRenderState)(THIS_ D3DRENDERSTATETYPE State, DWORD* pValue) {
	TRX2(State, pValue);
	return ptr->GetRenderState(State, pValue);
}
STDFUNC(MyDirect3DDevice8::BeginStateBlock)(THIS) {
	TRX();
	return ptr->BeginStateBlock();
}
STDFUNC(MyDirect3DDevice8::EndStateBlock)(THIS_ DWORD* pToken) {
	TRX1(pToken);
	HRESULT hr = ptr->EndStateBlock(pToken);
	return hr;
}
STDFUNC(MyDirect3DDevice8::ApplyStateBlock)(THIS_ DWORD Token) {
	TRX1(Token);
	return ptr->ApplyStateBlock(Token);
}
STDFUNC(MyDirect3DDevice8::CaptureStateBlock)(THIS_ DWORD Token) {
	TRX1(Token);
	return ptr->CaptureStateBlock(Token);
}
STDFUNC(MyDirect3DDevice8::DeleteStateBlock)(THIS_ DWORD Token) {
	TRX1(Token);
	return ptr->DeleteStateBlock(Token);
}
STDFUNC(MyDirect3DDevice8::CreateStateBlock)(THIS_ D3DSTATEBLOCKTYPE Type, DWORD* pToken) {
	TRX2(Type, pToken);
	return ptr->CreateStateBlock(Type, pToken);
}
STDFUNC(MyDirect3DDevice8::SetClipStatus)(THIS_ CONST D3DCLIPSTATUS8* pClipStatus) {
	TRX1(pClipStatus);
	return ptr->SetClipStatus(pClipStatus);
}
STDFUNC(MyDirect3DDevice8::GetClipStatus)(THIS_ D3DCLIPSTATUS8* pClipStatus) {
	TRX1(pClipStatus);
	return ptr->GetClipStatus(pClipStatus);
}
STDFUNC(MyDirect3DDevice8::GetTexture)(THIS_ DWORD Stage, IDirect3DBaseTexture8** ppTexture) {
	TRX2(Stage, ppTexture);
	return ptr->GetTexture(Stage, ppTexture);
}
STDFUNC(MyDirect3DDevice8::SetTexture)(THIS_ DWORD Stage, IDirect3DBaseTexture8* pTexture) {
	TRX2(Stage, pTexture);
	return ptr->SetTexture(Stage,pTexture);
}
STDFUNC(MyDirect3DDevice8::GetTextureStageState)(THIS_ DWORD Stage, D3DTEXTURESTAGESTATETYPE Type, DWORD* pValue) {
	TRX3(Stage, Type, pValue);
	return ptr->GetTextureStageState(Stage, Type, pValue);
}
STDFUNC(MyDirect3DDevice8::SetTextureStageState)(THIS_ DWORD Stage, D3DTEXTURESTAGESTATETYPE Type, DWORD Value) {
	TRX3(Stage, Type, Value);
	return ptr->SetTextureStageState(Stage,Type,Value);
}
STDFUNC(MyDirect3DDevice8::ValidateDevice)(THIS_ DWORD* pNumPasses) {
	TRX1(pNumPasses);
	return ptr->ValidateDevice(pNumPasses);
}
STDFUNC(MyDirect3DDevice8::GetInfo)(THIS_ DWORD DevInfoID, void* pDevInfoStruct, DWORD DevInfoStructSize) {
	TRX3(DevInfoID, pDevInfoStruct, DevInfoStructSize);
	return ptr->GetInfo(DevInfoID, pDevInfoStruct, DevInfoStructSize);
}
STDFUNC(MyDirect3DDevice8::SetPaletteEntries)(THIS_ UINT PaletteNumber, CONST PALETTEENTRY* pEntries) {
	TRX2(PaletteNumber, pEntries);
	return ptr->SetPaletteEntries(PaletteNumber, pEntries);
}
STDFUNC(MyDirect3DDevice8::GetPaletteEntries)(THIS_ UINT PaletteNumber, PALETTEENTRY* pEntries) {
	TRX2(PaletteNumber, pEntries);
	return ptr->GetPaletteEntries(PaletteNumber, pEntries);
}
STDFUNC(MyDirect3DDevice8::SetCurrentTexturePalette)(THIS_ UINT PaletteNumber) {
	TRX1(PaletteNumber);
	return ptr->SetCurrentTexturePalette(PaletteNumber);
}
STDFUNC(MyDirect3DDevice8::GetCurrentTexturePalette)(THIS_ UINT *PaletteNumber) {
	TRX1(PaletteNumber);
	return ptr->GetCurrentTexturePalette(PaletteNumber);
}
STDFUNC(MyDirect3DDevice8::DrawPrimitive)(THIS_ D3DPRIMITIVETYPE PrimitiveType, UINT StartVertex, UINT PrimitiveCount) {
	TRX3(PrimitiveType, StartVertex, PrimitiveCount);

	// check about myst
	//if (PrimitiveType == D3DPT_TRIANGLELIST) {
	//	DWORD value;
	//	if (SUCCEEDED(GetRenderState(static_cast<D3DRENDERSTATETYPE>(137), &value)) && value != 0 ||
	//		SUCCEEDED(GetRenderState(static_cast<D3DRENDERSTATETYPE>(27), &value)) && value != 1 ||
	//		SUCCEEDED(GetRenderState(static_cast<D3DRENDERSTATETYPE>(19), &value)) && value != 5 ||
	//		SUCCEEDED(GetRenderState(static_cast<D3DRENDERSTATETYPE>(20), &value)) && value != 6) {
	//	}
	//	else {
	//		return S_OK;
	//	}
	//}
	return ptr->DrawPrimitive( PrimitiveType, StartVertex, PrimitiveCount);
}
STDFUNC(MyDirect3DDevice8::DrawIndexedPrimitive)(THIS_ D3DPRIMITIVETYPE type, UINT minIndex, UINT NumVertices, UINT startIndex, UINT primCount) {
	TRX5(type, minIndex, NumVertices, startIndex, primCount);
	return ptr->DrawIndexedPrimitive(type, minIndex, NumVertices, startIndex, primCount);
}
STDFUNC(MyDirect3DDevice8::DrawPrimitiveUP)(THIS_ D3DPRIMITIVETYPE PrimitiveType, UINT PrimitiveCount, CONST void* pVertexStreamZeroData, UINT VertexStreamZeroStride) {
	TRX4(PrimitiveType, PrimitiveCount, pVertexStreamZeroData, VertexStreamZeroStride);
	return ptr->DrawPrimitiveUP(PrimitiveType, PrimitiveCount, pVertexStreamZeroData, VertexStreamZeroStride);
}
STDFUNC(MyDirect3DDevice8::DrawIndexedPrimitiveUP)(THIS_ D3DPRIMITIVETYPE PrimitiveType, UINT MinVertexIndex, UINT NumVertexIndices, UINT PrimitiveCount, CONST void* pIndexData, D3DFORMAT IndexDataFormat, CONST void* pVertexStreamZeroData, UINT VertexStreamZeroStride) {
	TRX8(PrimitiveType, MinVertexIndex, NumVertexIndices, PrimitiveCount, pIndexData, IndexDataFormat, pVertexStreamZeroData, VertexStreamZeroStride);
	return ptr->DrawIndexedPrimitiveUP(PrimitiveType, MinVertexIndex, NumVertexIndices, PrimitiveCount, pIndexData, IndexDataFormat, pVertexStreamZeroData, VertexStreamZeroStride);
}
STDFUNC(MyDirect3DDevice8::ProcessVertices)(THIS_ UINT SrcStartIndex, UINT DestIndex, UINT VertexCount, IDirect3DVertexBuffer8* pDestBuffer, DWORD Flags) {
	TRX5(SrcStartIndex, DestIndex, VertexCount, pDestBuffer, Flags);
	return ptr->ProcessVertices(SrcStartIndex, DestIndex, VertexCount, MyDirect3DVertexBuffer8::Get( pDestBuffer ), Flags);
}
STDFUNC(MyDirect3DDevice8::CreateVertexShader)(THIS_ CONST DWORD* pDeclaration, CONST DWORD* pFunction, DWORD* pHandle, DWORD Usage) {
	TRX4(pDeclaration, pFunction, pHandle, Usage);
	return ptr->CreateVertexShader(pDeclaration, pFunction, pHandle, Usage);
}
STDFUNC(MyDirect3DDevice8::SetVertexShader)(THIS_ DWORD Handle) {
	TRX1(Handle);
	HRESULT hr = ptr->SetVertexShader(Handle);
	return hr;
}
STDFUNC(MyDirect3DDevice8::GetVertexShader)(THIS_ DWORD* pHandle) {
	TRX1(pHandle);
	return ptr->GetVertexShader(pHandle);
}
STDFUNC(MyDirect3DDevice8::DeleteVertexShader)(THIS_ DWORD Handle) {
	TRX1(Handle)
	return ptr->DeleteVertexShader(Handle);
}
STDFUNC(MyDirect3DDevice8::SetVertexShaderConstant)(THIS_ DWORD Register, CONST void* pConstantData, DWORD ConstantCount) {
	TRX3(Register, pConstantData, ConstantCount);
	return ptr->SetVertexShaderConstant(Register, pConstantData, ConstantCount);
}
STDFUNC(MyDirect3DDevice8::GetVertexShaderConstant)(THIS_ DWORD Register, void* pConstantData, DWORD ConstantCount) {
	TRX3(Register, pConstantData, ConstantCount);
	return ptr->GetVertexShaderConstant(Register,pConstantData, ConstantCount);
}
STDFUNC(MyDirect3DDevice8::GetVertexShaderDeclaration)(THIS_ DWORD Handle, void* pData, DWORD* pSizeOfData) {
	TRX3(Handle, pData, pSizeOfData);
	return ptr->GetVertexShaderDeclaration(Handle, pData, pSizeOfData);
}
STDFUNC(MyDirect3DDevice8::GetVertexShaderFunction)(THIS_ DWORD Handle, void* pData, DWORD* pSizeOfData) {
	TRX3(Handle, pData, pSizeOfData);
	return ptr->GetVertexShaderFunction(Handle, pData, pSizeOfData);
}
STDFUNC(MyDirect3DDevice8::SetStreamSource)(THIS_ UINT StreamNumber, IDirect3DVertexBuffer8* pStreamData, UINT Stride) {
	TRX3(StreamNumber, pStreamData, Stride);
	return ptr->SetStreamSource(StreamNumber, MyDirect3DVertexBuffer8::Get( pStreamData ), Stride);
}
STDFUNC(MyDirect3DDevice8::GetStreamSource)(THIS_ UINT StreamNumber, IDirect3DVertexBuffer8** ppStreamData, UINT* pStride) {
	TRX3(StreamNumber, ppStreamData, pStride);
	return ptr->GetStreamSource(StreamNumber, ppStreamData, pStride);
}
STDFUNC(MyDirect3DDevice8::SetIndices)(THIS_ IDirect3DIndexBuffer8* pIndexData, UINT BaseVertexIndex) {
	TRX2(pIndexData, BaseVertexIndex);
	return ptr->SetIndices(MyDirect3DIndexBuffer8::Get( pIndexData ), BaseVertexIndex);
}
STDFUNC(MyDirect3DDevice8::GetIndices)(THIS_ IDirect3DIndexBuffer8** ppIndexData, UINT* pBaseVertexIndex) {
	TRX2(ppIndexData, pBaseVertexIndex);
	return ptr->GetIndices(ppIndexData, pBaseVertexIndex);
}
STDFUNC(MyDirect3DDevice8::CreatePixelShader)(THIS_ CONST DWORD* pFunction, DWORD* pHandle) {
	TRX2(pFunction, pHandle);
	return ptr->CreatePixelShader(pFunction, pHandle);
}
STDFUNC(MyDirect3DDevice8::SetPixelShader)(THIS_ DWORD Handle) {
	TRX1(Handle);
	return ptr->SetPixelShader(Handle);
}
STDFUNC(MyDirect3DDevice8::GetPixelShader)(THIS_ DWORD* pHandle) {
	TRX1(pHandle);
	return ptr->GetPixelShader(pHandle);
}
STDFUNC(MyDirect3DDevice8::DeletePixelShader)(THIS_ DWORD Handle) {
	TRX1(Handle);
	return ptr->DeletePixelShader(Handle);
}
STDFUNC(MyDirect3DDevice8::SetPixelShaderConstant)(THIS_ DWORD Register, CONST void* pConstantData, DWORD ConstantCount) {
	TRX3(Register, pConstantData, ConstantCount);
	return ptr->SetPixelShaderConstant(Register, pConstantData, ConstantCount);
}
STDFUNC(MyDirect3DDevice8::GetPixelShaderConstant)(THIS_ DWORD Register, void* pConstantData, DWORD ConstantCount) {
	TRX3(Register, pConstantData, ConstantCount);
	return ptr->GetPixelShaderConstant(Register, pConstantData,ConstantCount);
}
STDFUNC(MyDirect3DDevice8::GetPixelShaderFunction)(THIS_ DWORD Handle, void* pData, DWORD* pSizeOfData) {
	TRX3(Handle, pData, pSizeOfData);
	return ptr->GetPixelShaderFunction(Handle, pData, pSizeOfData);
}
STDFUNC(MyDirect3DDevice8::DrawRectPatch)(THIS_ UINT Handle, CONST float* pNumSegs, CONST D3DRECTPATCH_INFO* pRectPatchInfo) {
	TRX3(Handle, pNumSegs, pRectPatchInfo);
	return ptr->DrawRectPatch(Handle, pNumSegs, pRectPatchInfo);
}
STDFUNC(MyDirect3DDevice8::DrawTriPatch)(THIS_ UINT Handle, CONST float* pNumSegs, CONST D3DTRIPATCH_INFO* pTriPatchInfo) {
	TRX3(Handle, pNumSegs, pTriPatchInfo);
	return ptr->DrawTriPatch(Handle, pNumSegs, pTriPatchInfo);
}
STDFUNC(MyDirect3DDevice8::DeletePatch)(THIS_ UINT Handle) {
	TRX1(Handle);
	return ptr->DeletePatch(Handle);
}
