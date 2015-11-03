#include "main.h"

const bool traceGlobal = true;
const bool traceMyDirect3D8 = true;

class MyDirect3D8 : public IDirect3D8 {
public:
	MyDirect3D8(UINT SDKVersion) {
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

	bool WasInit() {
		return ptr != nullptr;
	}

	~MyDirect3D8() {
		TRACE(MyDirect3D8);
		if(hD3D)
			FreeLibrary(hD3D);
	}

	STDMETHOD(QueryInterface)(THIS_ REFIID riid, void** ppvObj) {
		TRACE5(MyDirect3D8, riid.Data1, riid.Data2, riid.Data3, riid.Data4, ppvObj);
		return ptr->QueryInterface(riid, ppvObj);
	}
	STDMETHOD_(ULONG, AddRef)(THIS) {
		TRACE(MyDirect3D8);
		return ptr->AddRef();
	}
	STDMETHOD_(ULONG, Release)(THIS) {
		TRACE(MyDirect3D8);
		auto counter = ptr->Release();
		if (counter == 0)
			delete this;
		return counter;
	}

	/*** IDirect3D8 methods ***/
	STDMETHOD(RegisterSoftwareDevice)(THIS_ void* pInitializeFunction) {
		TRACE1(MyDirect3D8, pInitializeFunction);
		return ptr->RegisterSoftwareDevice(pInitializeFunction);
	}
	STDMETHOD_(UINT, GetAdapterCount)(THIS) {
		TRACE(MyDirect3D8);
		return ptr->GetAdapterCount();
	}
	STDMETHOD(GetAdapterIdentifier)(THIS_ UINT Adapter, DWORD Flags, D3DADAPTER_IDENTIFIER8* pIdentifier) {
		TRACE3(MyDirect3D8, Adapter, Flags, pIdentifier);
		return ptr->GetAdapterIdentifier(Adapter, Flags, pIdentifier);
	}
	STDMETHOD_(UINT, GetAdapterModeCount)(THIS_ UINT Adapter) {
		TRACE1(MyDirect3D8, Adapter);
		return ptr->GetAdapterModeCount(Adapter);
	}
	STDMETHOD(EnumAdapterModes)(THIS_ UINT Adapter, UINT Mode, D3DDISPLAYMODE* pMode) {
		TRACE3(MyDirect3D8, Adapter, Mode, pMode);
		return ptr->EnumAdapterModes(Adapter, Mode, pMode);
	}
	STDMETHOD(GetAdapterDisplayMode)(THIS_ UINT Adapter, D3DDISPLAYMODE* pMode) {
		TRACE2(MyDirect3D8, Adapter, pMode);
		return ptr->GetAdapterDisplayMode(Adapter, pMode);
	}
	STDMETHOD(CheckDeviceType)(THIS_ UINT Adapter, D3DDEVTYPE CheckType, D3DFORMAT DisplayFormat, D3DFORMAT BackBufferFormat, BOOL Windowed) {
		TRACE5(MyDirect3D8, Adapter, CheckType, DisplayFormat, BackBufferFormat, Windowed);
		return ptr->CheckDeviceType(Adapter, CheckType, DisplayFormat, BackBufferFormat, Windowed);
	}
	STDMETHOD(CheckDeviceFormat)(THIS_ UINT Adapter, D3DDEVTYPE DeviceType, D3DFORMAT AdapterFormat, DWORD Usage, D3DRESOURCETYPE RType, D3DFORMAT CheckFormat) {
		TRACE6(MyDirect3D8, Adapter, DeviceType, AdapterFormat, Usage, RType, CheckFormat);
		return ptr->CheckDeviceFormat(Adapter, DeviceType, AdapterFormat, Usage, RType, CheckFormat);
	}
	STDMETHOD(CheckDeviceMultiSampleType)(THIS_ UINT Adapter, D3DDEVTYPE DeviceType, D3DFORMAT SurfaceFormat, BOOL Windowed, D3DMULTISAMPLE_TYPE MultiSampleType) {
		TRACE5(MyDirect3D8, Adapter, DeviceType, SurfaceFormat, Windowed, MultiSampleType);
		return ptr->CheckDeviceMultiSampleType(Adapter, DeviceType, SurfaceFormat, Windowed, MultiSampleType);
	}
	STDMETHOD(CheckDepthStencilMatch)(THIS_ UINT Adapter, D3DDEVTYPE DeviceType, D3DFORMAT AdapterFormat, D3DFORMAT RenderTargetFormat, D3DFORMAT DepthStencilFormat) {
		TRACE5(MyDirect3D8, Adapter, DeviceType, AdapterFormat, RenderTargetFormat, DepthStencilFormat);
		return ptr->CheckDepthStencilMatch(Adapter, DeviceType, AdapterFormat, RenderTargetFormat, DepthStencilFormat);
	}
	STDMETHOD(GetDeviceCaps)(THIS_ UINT Adapter, D3DDEVTYPE DeviceType, D3DCAPS8* pCaps) {
		TRACE3(MyDirect3D8, Adapter, DeviceType, pCaps);
		return ptr->GetDeviceCaps(Adapter, DeviceType, pCaps);
	}
	STDMETHOD_(HMONITOR, GetAdapterMonitor)(THIS_ UINT Adapter) {
		TRACE1(MyDirect3D8, Adapter);
		return ptr->GetAdapterMonitor(Adapter);
	}
	STDMETHOD(CreateDevice)(THIS_ UINT Adapter, D3DDEVTYPE DeviceType, HWND hFocusWindow, DWORD BehaviorFlags, D3DPRESENT_PARAMETERS* pPresentationParameters, IDirect3DDevice8** ppReturnedDeviceInterface) {
		TRACE6(MyDirect3D8, Adapter, DeviceType, hFocusWindow, BehaviorFlags, pPresentationParameters, ppReturnedDeviceInterface);

		// Set window to fullscreen and disable some of awful things
		// Note: for good reasons this must be not here, but instead I must first create hooks to this functions and function of create window
		// TODO: read this values from ini file and make changes only if need
		ShowCursor(TRUE);
		ClipCursor(nullptr);

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
		//pPresentationParameters->BackBufferHeight = 0;
		pPresentationParameters->BackBufferFormat = D3DFMT_X8R8G8B8;//D3DFMT_UNKNOWN; //D3DFMT_X8R8G8B8;
		pPresentationParameters->BackBufferCount = 1;
		pPresentationParameters->SwapEffect = D3DSWAPEFFECT_COPY;
		pPresentationParameters->Windowed = TRUE;

		HRESULT hr = ptr->CreateDevice(Adapter, DeviceType, hFocusWindow, BehaviorFlags, pPresentationParameters, ppReturnedDeviceInterface);

		if (SUCCEEDED(hr))
		{
			// Return our device
			//*ppReturnedDeviceInterface = new MyDirect3DDevice8(this, *ppReturnedDeviceInterface, pPresentationParameters->hDeviceWindow);
		}
		return hr;
	}

private:
	IDirect3D8 *ptr = nullptr;
	HMODULE hD3D = 0;
};

extern "C" {
	__declspec(dllexport) IDirect3D8 * WINAPI Direct3DCreate8(UINT SDKVersion) {
		TRACE1(Global, SDKVersion);
		auto d3d8 = new MyDirect3D8(SDKVersion);
		if (d3d8->WasInit()) {
			return d3d8;
		}
		delete d3d8;
		return nullptr;
	}

	__declspec(dllexport) BOOL WINAPI DllMain(
		HINSTANCE hinstDLL,  // handle to DLL module
		DWORD fdwReason,     // reason for calling function
		LPVOID lpReserved) {
			// Perform actions based on the reason for calling.
			switch (fdwReason)
			{
			case DLL_PROCESS_ATTACH:
				// Initialize once for each new process.
				// Return FALSE to fail DLL load.
				break;

			case DLL_THREAD_ATTACH:
				// Do thread-specific initialization.
				break;

			case DLL_THREAD_DETACH:
				// Do thread-specific cleanup.
				break;

			case DLL_PROCESS_DETACH:
				// Perform any necessary cleanup.
				break;
			}
			return TRUE;  // Successful DLL_PROCESS_ATTACH.
	}
}
//
//extern "C" __declspec(dllexport) IDirect3D8 * WINAPI Direct3DCreate8(UINT SDKVersion);
//extern "C" __declspec(dllexport) BOOL WINAPI DllMain(
//	HINSTANCE hinstDLL,  // handle to DLL module
//	DWORD fdwReason,     // reason for calling function
//	LPVOID lpReserved);
//
//extern "C" __declspec(dllexport) BOOL WINAPI DllMain(
//	HINSTANCE hinstDLL,  // handle to DLL module
//	DWORD fdwReason,     // reason for calling function
//	LPVOID lpReserved)  // reserved
//