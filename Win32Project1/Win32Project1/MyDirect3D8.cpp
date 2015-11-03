#include "main.h"


MyDirect3D8::MyDirect3D8(UINT SDKVersion) : ptr(nullptr), hD3D(0) {
	TRACE1(MyDirect3D8, SDKVersion);

	hD3D = LoadLibraryA("d3d8.dll");
	if (!hD3D)
		return;
	auto __Direct3DCreate8 = reinterpret_cast<Direct3DCreate8Ptr>(GetProcAddress(hD3D, "Direct3DCreate8"));
	if (!__Direct3DCreate8) {
		return;
	}
	ptr = __Direct3DCreate8(SDKVersion);
}

bool MyDirect3D8::WasInit() {
	return ptr != nullptr;
}

HRESULT MyDirect3D8::__CreateDevice(UINT Adapter, D3DDEVTYPE DeviceType, HWND hFocusWindow, DWORD BehaviorFlags, D3DPRESENT_PARAMETERS* pPresentationParameters, IDirect3DDevice8** ppReturnedDeviceInterface) {
	TRACE6(MyDirect3D8, Adapter, DeviceType, hFocusWindow, BehaviorFlags, pPresentationParameters, ppReturnedDeviceInterface);
	return ptr->CreateDevice(Adapter, DeviceType, hFocusWindow, BehaviorFlags, pPresentationParameters, ppReturnedDeviceInterface);
}


MyDirect3D8::~MyDirect3D8() {
	TRACE(MyDirect3D8);
	if (hD3D)
		FreeLibrary(hD3D);
}

STDFUNC(MyDirect3D8::QueryInterface)(THIS_ REFIID riid, void** ppvObj) {
	TRACE2(MyDirect3D8, riid, ppvObj);
	return ptr->QueryInterface(riid, ppvObj);
}

STDFUNC_(ULONG, MyDirect3D8::AddRef)(THIS) {
	TRACE(MyDirect3D8);
	return ptr->AddRef();
}
STDFUNC_(ULONG, MyDirect3D8::Release)(THIS) {
	TRACE(MyDirect3D8);
	auto counter = ptr->Release();
	if (counter == 0)
		delete this;
	return counter;
}

/*** IDirect3D8 methods ***/
STDFUNC(MyDirect3D8::RegisterSoftwareDevice)(THIS_ void* pInitializeFunction) {
	TRACE1(MyDirect3D8, pInitializeFunction);
	return ptr->RegisterSoftwareDevice(pInitializeFunction);
}
STDFUNC_(UINT, MyDirect3D8::GetAdapterCount)(THIS) {
	TRACE(MyDirect3D8);
	return ptr->GetAdapterCount();
}
STDFUNC(MyDirect3D8::GetAdapterIdentifier)(THIS_ UINT Adapter, DWORD Flags, D3DADAPTER_IDENTIFIER8* pIdentifier) {
	TRACE3(MyDirect3D8, Adapter, Flags, pIdentifier);
	return ptr->GetAdapterIdentifier(Adapter, Flags, pIdentifier);
}
STDFUNC_(UINT, MyDirect3D8::GetAdapterModeCount)(THIS_ UINT Adapter) {
	TRACE1(MyDirect3D8, Adapter);
	return ptr->GetAdapterModeCount(Adapter);
}
STDFUNC(MyDirect3D8::EnumAdapterModes)(THIS_ UINT Adapter, UINT Mode, D3DDISPLAYMODE* pMode) {
	TRACE3(MyDirect3D8, Adapter, Mode, pMode);
	return ptr->EnumAdapterModes(Adapter, Mode, pMode);
}
STDFUNC(MyDirect3D8::GetAdapterDisplayMode)(THIS_ UINT Adapter, D3DDISPLAYMODE* pMode) {
	TRACE2(MyDirect3D8, Adapter, pMode);
	return ptr->GetAdapterDisplayMode(Adapter, pMode);
}
STDFUNC(MyDirect3D8::CheckDeviceType)(THIS_ UINT Adapter, D3DDEVTYPE CheckType, D3DFORMAT DisplayFormat, D3DFORMAT BackBufferFormat, BOOL Windowed) {
	TRACE5(MyDirect3D8, Adapter, CheckType, DisplayFormat, BackBufferFormat, Windowed);
	return ptr->CheckDeviceType(Adapter, CheckType, DisplayFormat, BackBufferFormat, Windowed);
}
STDFUNC(MyDirect3D8::CheckDeviceFormat)(THIS_ UINT Adapter, D3DDEVTYPE DeviceType, D3DFORMAT AdapterFormat, DWORD Usage, D3DRESOURCETYPE RType, D3DFORMAT CheckFormat) {
	TRACE6(MyDirect3D8, Adapter, DeviceType, AdapterFormat, Usage, RType, CheckFormat);
	return ptr->CheckDeviceFormat(Adapter, DeviceType, AdapterFormat, Usage, RType, CheckFormat);
}
STDFUNC(MyDirect3D8::CheckDeviceMultiSampleType)(THIS_ UINT Adapter, D3DDEVTYPE DeviceType, D3DFORMAT SurfaceFormat, BOOL Windowed, D3DMULTISAMPLE_TYPE MultiSampleType) {
	TRACE5(MyDirect3D8, Adapter, DeviceType, SurfaceFormat, Windowed, MultiSampleType);
	return ptr->CheckDeviceMultiSampleType(Adapter, DeviceType, SurfaceFormat, Windowed, MultiSampleType);
}
STDFUNC(MyDirect3D8::CheckDepthStencilMatch)(THIS_ UINT Adapter, D3DDEVTYPE DeviceType, D3DFORMAT AdapterFormat, D3DFORMAT RenderTargetFormat, D3DFORMAT DepthStencilFormat) {
	TRACE5(MyDirect3D8, Adapter, DeviceType, AdapterFormat, RenderTargetFormat, DepthStencilFormat);
	return ptr->CheckDepthStencilMatch(Adapter, DeviceType, AdapterFormat, RenderTargetFormat, DepthStencilFormat);
}
STDFUNC(MyDirect3D8::GetDeviceCaps)(THIS_ UINT Adapter, D3DDEVTYPE DeviceType, D3DCAPS8* pCaps) {
	TRACE3(MyDirect3D8, Adapter, DeviceType, pCaps);
	return ptr->GetDeviceCaps(Adapter, DeviceType, pCaps);
}
STDFUNC_(HMONITOR, MyDirect3D8::GetAdapterMonitor)(THIS_ UINT Adapter) {
	TRACE1(MyDirect3D8, Adapter);
	return ptr->GetAdapterMonitor(Adapter);
}
STDFUNC(MyDirect3D8::CreateDevice)(THIS_ UINT Adapter, D3DDEVTYPE DeviceType, HWND hFocusWindow, DWORD BehaviorFlags, D3DPRESENT_PARAMETERS* pPresentationParameters, IDirect3DDevice8** ppReturnedDeviceInterface) {
	TRACE6(MyDirect3D8, Adapter, DeviceType, hFocusWindow, BehaviorFlags, pPresentationParameters, ppReturnedDeviceInterface);

	ShowCursor(TRUE);
	//ClipCursor(nullptr);
	const DWORD windowStyle = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_BORDER | WS_MINIMIZEBOX;
	SetWindowLong(hFocusWindow, GWL_STYLE, windowStyle);
	RECT rc = { 0, 0, static_cast<LONG>(pPresentationParameters->BackBufferWidth), static_cast<LONG>(pPresentationParameters->BackBufferHeight) };
	AdjustWindowRect(&rc, windowStyle, FALSE);
	MoveWindow(hFocusWindow, 0, 0, rc.right - rc.left, rc.bottom - rc.top, TRUE);
	ShowWindow(hFocusWindow, SW_SHOWNORMAL);
	UpdateWindow(hFocusWindow);

	DeviceType = D3DDEVTYPE_HAL; // REF, HAL
	BehaviorFlags = D3DCREATE_HARDWARE_VERTEXPROCESSING;
	//pPresentationParameters->BackBufferWidth = 0;
	//pPresentatinoParameters->BackBufferHeight = 0;
	pPresentationParameters->BackBufferFormat = D3DFMT_X8R8G8B8;
	pPresentationParameters->BackBufferCount = 1;
	pPresentationParameters->SwapEffect = D3DSWAPEFFECT_COPY;
	
	pPresentationParameters->Windowed = TRUE;

	auto pDevice = new MyDirect3DDevice8(this, Adapter, DeviceType, hFocusWindow, BehaviorFlags, pPresentationParameters);
	if (pDevice->WasInit()) {
		*ppReturnedDeviceInterface = pDevice;
		return S_OK;
	}
	else {
		*ppReturnedDeviceInterface = nullptr;
		delete pDevice;
		return E_FAIL;
	}
}
