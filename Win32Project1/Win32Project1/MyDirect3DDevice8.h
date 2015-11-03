#pragma once

#include "MyD3D8.h"

class MyDirect3D8;
class MyDirect3DDevice8 : public IDirect3DDevice8 {
public:
	MyDirect3DDevice8( MyDirect3D8 *d3d8, UINT Adapter, D3DDEVTYPE DeviceType, HWND hFocusWindow, DWORD BehaviorFlags, D3DPRESENT_PARAMETERS* pPresentationParameters );
	virtual ~MyDirect3DDevice8();
	bool WasInit();
	void SaveCurrentBackBuffer();
	HRESULT __CreateVertexBuffer(THIS_ UINT Length, DWORD Usage, DWORD FVF, D3DPOOL Pool, IDirect3DVertexBuffer8** ppVertexBuffer);
	HRESULT __CreateIndexBuffer(THIS_ UINT Length, DWORD Usage, D3DFORMAT Format, D3DPOOL Pool, IDirect3DIndexBuffer8** ppIndexBuffer);

	/*** IUnknown methods ***/
/* 000 */	STDMETHOD(QueryInterface)(THIS_ REFIID riid, void** ppvObj);
/* 004 */	STDMETHOD_(ULONG, AddRef)(THIS);
/* 008 */	STDMETHOD_(ULONG, Release)(THIS);

			/*** IDirect3DDevice8 methods ***/
/* 00C */	STDMETHOD(TestCooperativeLevel)(THIS);
/* 010 */	STDMETHOD_(UINT, GetAvailableTextureMem)(THIS);
/* 014 */	STDMETHOD(ResourceManagerDiscardBytes)(THIS_ DWORD Bytes);
/* 018 */	STDMETHOD(GetDirect3D)(THIS_ IDirect3D8** ppD3D8);
/* 01C */	STDMETHOD(GetDeviceCaps)(THIS_ D3DCAPS8* pCaps);
/* 020 */	STDMETHOD(GetDisplayMode)(THIS_ D3DDISPLAYMODE* pMode);
/* 024 */	STDMETHOD(GetCreationParameters)(THIS_ D3DDEVICE_CREATION_PARAMETERS *pParameters);
/* 028 */	STDMETHOD(SetCursorProperties)(THIS_ UINT XHotSpot, UINT YHotSpot, IDirect3DSurface8* pCursorBitmap);
/* 02C */	STDMETHOD_(void, SetCursorPosition)(THIS_ UINT XScreenSpace, UINT YScreenSpace, DWORD Flags);
/* 030 */	STDMETHOD_(BOOL, ShowCursor)(THIS_ BOOL bShow);
/* 034 */	STDMETHOD(CreateAdditionalSwapChain)(THIS_ D3DPRESENT_PARAMETERS* pPresentationParameters, IDirect3DSwapChain8** pSwapChain);
/* 038 */	STDMETHOD(Reset)(THIS_ D3DPRESENT_PARAMETERS* pPresentationParameters);
/* 03C */	STDMETHOD(Present)(THIS_ CONST RECT* pSourceRect, CONST RECT* pDestRect, HWND hDestWindowOverride, CONST RGNDATA* pDirtyRegion);
/* 040 */	STDMETHOD(GetBackBuffer)(THIS_ UINT BackBuffer, D3DBACKBUFFER_TYPE Type, IDirect3DSurface8** ppBackBuffer);
/* 044 */	STDMETHOD(GetRasterStatus)(THIS_ D3DRASTER_STATUS* pRasterStatus);
/* 048 */	STDMETHOD_(void, SetGammaRamp)(THIS_ DWORD Flags, CONST D3DGAMMARAMP* pRamp);
/* 04C */	STDMETHOD_(void, GetGammaRamp)(THIS_ D3DGAMMARAMP* pRamp);
/* 050 */	STDMETHOD(CreateTexture)(THIS_ UINT Width, UINT Height, UINT Levels, DWORD Usage, D3DFORMAT Format, D3DPOOL Pool, IDirect3DTexture8** ppTexture);
/* 054 */	STDMETHOD(CreateVolumeTexture)(THIS_ UINT Width, UINT Height, UINT Depth, UINT Levels, DWORD Usage, D3DFORMAT Format, D3DPOOL Pool, IDirect3DVolumeTexture8** ppVolumeTexture);
/* 058 */	STDMETHOD(CreateCubeTexture)(THIS_ UINT EdgeLength, UINT Levels, DWORD Usage, D3DFORMAT Format, D3DPOOL Pool, IDirect3DCubeTexture8** ppCubeTexture);
/* 05C */	STDMETHOD(CreateVertexBuffer)(THIS_ UINT Length, DWORD Usage, DWORD FVF, D3DPOOL Pool, IDirect3DVertexBuffer8** ppVertexBuffer);
/* 060 */	STDMETHOD(CreateIndexBuffer)(THIS_ UINT Length, DWORD Usage, D3DFORMAT Format, D3DPOOL Pool, IDirect3DIndexBuffer8** ppIndexBuffer);
/* 064 */	STDMETHOD(CreateRenderTarget)(THIS_ UINT Width, UINT Height, D3DFORMAT Format, D3DMULTISAMPLE_TYPE MultiSample, BOOL Lockable, IDirect3DSurface8** ppSurface);
/* 068 */	STDMETHOD(CreateDepthStencilSurface)(THIS_ UINT Width, UINT Height, D3DFORMAT Format, D3DMULTISAMPLE_TYPE MultiSample, IDirect3DSurface8** ppSurface);
/* 06C */	STDMETHOD(CreateImageSurface)(THIS_ UINT Width, UINT Height, D3DFORMAT Format, IDirect3DSurface8** ppSurface);
/* 070 */	STDMETHOD(CopyRects)(THIS_ IDirect3DSurface8* pSourceSurface, CONST RECT* pSourceRectsArray, UINT cRects, IDirect3DSurface8* pDestinationSurface, CONST POINT* pDestPointsArray);
/* 074 */	STDMETHOD(UpdateTexture)(THIS_ IDirect3DBaseTexture8* pSourceTexture, IDirect3DBaseTexture8* pDestinationTexture);
/* 078 */	STDMETHOD(GetFrontBuffer)(THIS_ IDirect3DSurface8* pDestSurface);
/* 07C */	STDMETHOD(SetRenderTarget)(THIS_ IDirect3DSurface8* pRenderTarget, IDirect3DSurface8* pNewZStencil);
/* 080 */	STDMETHOD(GetRenderTarget)(THIS_ IDirect3DSurface8** ppRenderTarget);
/* 084 */	STDMETHOD(GetDepthStencilSurface)(THIS_ IDirect3DSurface8** ppZStencilSurface);
/* 088 */	STDMETHOD(BeginScene)(THIS);
/* 08C */	STDMETHOD(EndScene)(THIS);
/* 090 */	STDMETHOD(Clear)(THIS_ DWORD Count, CONST D3DRECT* pRects, DWORD Flags, D3DCOLOR Color, float Z, DWORD Stencil);
/* 094 */	STDMETHOD(SetTransform)(THIS_ D3DTRANSFORMSTATETYPE State, CONST D3DMATRIX* pMatrix);		// 94
/* 098 */	STDMETHOD(GetTransform)(THIS_ D3DTRANSFORMSTATETYPE State, D3DMATRIX* pMatrix);				// 98 = 38
/* 09C */	STDMETHOD(MultiplyTransform)(THIS_ D3DTRANSFORMSTATETYPE, CONST D3DMATRIX*);				// 9C
/* 0A0 */	STDMETHOD(SetViewport)(THIS_ CONST D3DVIEWPORT8* pViewport);								// A0
/* 0A4 */	STDMETHOD(GetViewport)(THIS_ D3DVIEWPORT8* pViewport);										// A4
/* 0A8 */	STDMETHOD(SetMaterial)(THIS_ CONST D3DMATERIAL8* pMaterial);								// A8
/* 0AC */	STDMETHOD(GetMaterial)(THIS_ D3DMATERIAL8* pMaterial);										// AC
/* 0B0 */	STDMETHOD(SetLight)(THIS_ DWORD Index, CONST D3DLIGHT8*);									// B0
/* 0B4 */	STDMETHOD(GetLight)(THIS_ DWORD Index, D3DLIGHT8*);											// B4
/* 0B8 */	STDMETHOD(LightEnable)(THIS_ DWORD Index, BOOL Enable);										// B8
/* 0BC */	STDMETHOD(GetLightEnable)(THIS_ DWORD Index, BOOL* pEnable);								// BC
/* 0C0 */	STDMETHOD(SetClipPlane)(THIS_ DWORD Index, CONST float* pPlane);							// C0
/* 0C4 */	STDMETHOD(GetClipPlane)(THIS_ DWORD Index, float* pPlane);									// C4
/* 0C8 */	STDMETHOD(SetRenderState)(THIS_ D3DRENDERSTATETYPE State, DWORD Value);						// C8
/* 0CC */	STDMETHOD(GetRenderState)(THIS_ D3DRENDERSTATETYPE State, DWORD* pValue);					// CC
/* 0D0 */	STDMETHOD(BeginStateBlock)(THIS);															// D0
/* 0D4 */	STDMETHOD(EndStateBlock)(THIS_ DWORD* pToken);												// D4
/* 0D8 */	STDMETHOD(ApplyStateBlock)(THIS_ DWORD Token);												// D8
/* 0DC */	STDMETHOD(CaptureStateBlock)(THIS_ DWORD Token);											// DC
/* 0E0 */	STDMETHOD(DeleteStateBlock)(THIS_ DWORD Token);												// D0
/* 0E4 */	STDMETHOD(CreateStateBlock)(THIS_ D3DSTATEBLOCKTYPE Type, DWORD* pToken);					// D4
/* 0E8 */	STDMETHOD(SetClipStatus)(THIS_ CONST D3DCLIPSTATUS8* pClipStatus);							// D8
/* 0EC */	STDMETHOD(GetClipStatus)(THIS_ D3DCLIPSTATUS8* pClipStatus);								// DC
/* 0F0 */	STDMETHOD(GetTexture)(THIS_ DWORD Stage, IDirect3DBaseTexture8** ppTexture);				// E0
/* 0F4 */	STDMETHOD(SetTexture)(THIS_ DWORD Stage, IDirect3DBaseTexture8* pTexture);					// E4
/* 0F8 */	STDMETHOD(GetTextureStageState)(THIS_ DWORD Stage, D3DTEXTURESTAGESTATETYPE Type, DWORD* pValue);	// E8
/* 0FC */	STDMETHOD(SetTextureStageState)(THIS_ DWORD Stage, D3DTEXTURESTAGESTATETYPE Type, DWORD Value);		// EC
/* 100 */	STDMETHOD(ValidateDevice)(THIS_ DWORD* pNumPasses);													// F0
/* 104 */	STDMETHOD(GetInfo)(THIS_ DWORD DevInfoID, void* pDevInfoStruct, DWORD DevInfoStructSize);			// F4
/* 108 */	STDMETHOD(SetPaletteEntries)(THIS_ UINT PaletteNumber, CONST PALETTEENTRY* pEntries);				// F8
/* 10C */	STDMETHOD(GetPaletteEntries)(THIS_ UINT PaletteNumber, PALETTEENTRY* pEntries);						// FC
/* 110 */	STDMETHOD(SetCurrentTexturePalette)(THIS_ UINT PaletteNumber);										// 100
/* 114 */	STDMETHOD(GetCurrentTexturePalette)(THIS_ UINT *PaletteNumber);										// 104
/* 118 */	STDMETHOD(DrawPrimitive)(THIS_ D3DPRIMITIVETYPE PrimitiveType, UINT StartVertex, UINT PrimitiveCount);						// 108
/* 11C */	STDMETHOD(DrawIndexedPrimitive)(THIS_ D3DPRIMITIVETYPE, UINT minIndex, UINT NumVertices, UINT startIndex, UINT primCount);	// 10A
/* 120 */	STDMETHOD(DrawPrimitiveUP)(THIS_ D3DPRIMITIVETYPE PrimitiveType, UINT PrimitiveCount, CONST void* pVertexStreamZeroData, UINT VertexStreamZeroStride);	// 10C
/* 124 */	STDMETHOD(DrawIndexedPrimitiveUP)(THIS_ D3DPRIMITIVETYPE PrimitiveType, UINT MinVertexIndex, UINT NumVertexIndices, UINT PrimitiveCount, CONST void* pIndexData, D3DFORMAT IndexDataFormat, CONST void* pVertexStreamZeroData, UINT VertexStreamZeroStride); // 110
/* 128 */	STDMETHOD(ProcessVertices)(THIS_ UINT SrcStartIndex, UINT DestIndex, UINT VertexCount, IDirect3DVertexBuffer8* pDestBuffer, DWORD Flags);	// 114
/* 12C */	STDMETHOD(CreateVertexShader)(THIS_ CONST DWORD* pDeclaration, CONST DWORD* pFunction, DWORD* pHandle, DWORD Usage);	// 118
/* 130 */	STDMETHOD(SetVertexShader)(THIS_ DWORD Handle);											// 130h ?
/* 134 */	STDMETHOD(GetVertexShader)(THIS_ DWORD* pHandle);										// 134
/* 138 */	STDMETHOD(DeleteVertexShader)(THIS_ DWORD Handle);										// 138
/* 13C */	STDMETHOD(SetVertexShaderConstant)(THIS_ DWORD Register, CONST void* pConstantData, DWORD ConstantCount);	//13C
/* 140 */	STDMETHOD(GetVertexShaderConstant)(THIS_ DWORD Register, void* pConstantData, DWORD ConstantCount);			//140
/* 144 */	STDMETHOD(GetVertexShaderDeclaration)(THIS_ DWORD Handle, void* pData, DWORD* pSizeOfData);					//144
/* 148 */	STDMETHOD(GetVertexShaderFunction)(THIS_ DWORD Handle, void* pData, DWORD* pSizeOfData);					//148
/* 14C */	STDMETHOD(SetStreamSource)(THIS_ UINT StreamNumber, IDirect3DVertexBuffer8* pStreamData, UINT Stride);		//14C
/* 150 */	STDMETHOD(GetStreamSource)(THIS_ UINT StreamNumber, IDirect3DVertexBuffer8** ppStreamData, UINT* pStride);	//150
/* 154 */	STDMETHOD(SetIndices)(THIS_ IDirect3DIndexBuffer8* pIndexData, UINT BaseVertexIndex);						//154
/* 158 */	STDMETHOD(GetIndices)(THIS_ IDirect3DIndexBuffer8** ppIndexData, UINT* pBaseVertexIndex);
/* 15C */	STDMETHOD(CreatePixelShader)(THIS_ CONST DWORD* pFunction, DWORD* pHandle);
/* 160 */	STDMETHOD(SetPixelShader)(THIS_ DWORD Handle);
/* 164 */	STDMETHOD(GetPixelShader)(THIS_ DWORD* pHandle);
/* 168 */	STDMETHOD(DeletePixelShader)(THIS_ DWORD Handle);
/* 16C */	STDMETHOD(SetPixelShaderConstant)(THIS_ DWORD Register, CONST void* pConstantData, DWORD ConstantCount);
/* 170 */	STDMETHOD(GetPixelShaderConstant)(THIS_ DWORD Register, void* pConstantData, DWORD ConstantCount);
/* 174 */	STDMETHOD(GetPixelShaderFunction)(THIS_ DWORD Handle, void* pData, DWORD* pSizeOfData);
/* 178 */	STDMETHOD(DrawRectPatch)(THIS_ UINT Handle, CONST float* pNumSegs, CONST D3DRECTPATCH_INFO* pRectPatchInfo);
/* 17C */	STDMETHOD(DrawTriPatch)(THIS_ UINT Handle, CONST float* pNumSegs, CONST D3DTRIPATCH_INFO* pTriPatchInfo);
/* 180 */	STDMETHOD(DeletePatch)(THIS_ UINT Handle);

private:
	IDirect3DDevice8 *ptr;		// pointer to original
	MyDirect3D8 *pD3D;			// created device

	UINT frame;					// current frame number
	UINT command;				// current command in frame
	HWND hWnd;
};
