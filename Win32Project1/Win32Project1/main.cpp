#include "main.h"

const bool trace = true;
const bool traceGlobal				= trace;
const bool traceMyDirect3D8			= trace;
const bool traceMyDirect3DDevice8	= trace;
const bool traceMyDirect3DSurface8	= trace;
const bool traceMyDirect3DVertexBuffer8 = trace;
const bool traceMyDirect3DIndexBuffer8 = trace;


bool wasTraced = false;

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


std::ostream &operator<<(std::ostream& out, RECT* pRC) {
	if (!pRC)
		return out << 0;
	return out << "rc{" << pRC->left << ", " << pRC->top << ", " << pRC->right << ", " << pRC->bottom << "}";
}
std::ostream &operator<<(std::ostream& out, D3DPRESENT_PARAMETERS* pPP) {
	if (!pPP)
		return out << 0;
	return out << "pp{ w: " << pPP->BackBufferWidth << ", h: " << pPP->BackBufferHeight << ", ...}";
}

std::ostream &operator<<(std::ostream& out, REFIID riid) {
	return out << "g{" << riid.Data1 << "-" << riid.Data2 << "-" << riid.Data3 << "-" << riid.Data4 << "}";
}

std::ostream &operator<<(std::ostream& out, D3DVIEWPORT8 *vp) {
	if (!vp)
		return out << "nullptr";
	return out << "vp{" << vp->X << "-" << vp->Width << ", " << vp->Y << "-" << vp->Height << ", " << vp->MinZ << "-" << vp->MaxZ << "}";
}


DWORD rgb16to32(WORD color) {
	//   5  6  5
	UCHAR r, g, b;
	r = ((color >> 11) << 3) & 0xFF;
	g = ((color >> 5) << 2) & 0xFF;
	b = (color << 3) & 0xFF;
	return ((r << 16) | (g << 8) | (b));
}

WORD rgb32to16(DWORD color) {
	UCHAR r, g, b;
	r = (color >> 16) & 0xFF;
	g = (color >> 8) & 0xFF;
	b = (color)& 0xFF;
	return (((r >> 3) << 11) | ((g >> 2) << 5) | ((b >> 3)));
}
