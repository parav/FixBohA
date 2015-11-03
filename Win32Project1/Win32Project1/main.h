#pragma once
#define NOMINMAX
#include "MyD3D8.h"
#include <sstream>
#pragma comment(lib,"../../DXSDK/lib/dxguid.lib")

extern "C" typedef IDirect3D8* (WINAPI *Direct3DCreate8Ptr)(UINT);

extern const bool traceGlobal;
extern const bool traceMyDirect3D8;
extern const bool traceMyDirect3DDevice8;
extern const bool traceMyDirect3DSurface8;
extern const bool traceMyDirect3DVertexBuffer8;
extern const bool traceMyDirect3DIndexBuffer8;

extern bool wasTraced;

#ifdef _DEBUG
#define TRACEN(cls, N, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10 ) {\
	if(trace##cls){\
		std::ostringstream out;\
		/*if( this ) {\
					out << typeid(*this).name() << ": ";\
							}*/\
		out << /*#cls << ": " <<*/ __FUNCTION__ << "(";\
		if(N >= 1) out << p1;\
		if(N >= 2) out << ", " << p2;\
		if(N >= 3) out << ", " << p3;\
		if(N >= 4) out << ", " << p4;\
		if(N >= 5) out << ", " << p5;\
		if(N >= 6) out << ", " << p6;\
		if(N >= 7) out << ", " << p7;\
		if(N >= 8) out << ", " << p8;\
		if(N >= 9) out << ", " << p9;\
		if(N >= 10) out << ", " << p10;\
		out << ")" << std::endl;\
		OutputDebugStringA(out.str().c_str());\
		wasTraced = true;\
	}\
}
#else
#define TRACEN(cls, N, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10)
#endif
//																			  1 2  3  4  5  6  7  8  9  10
#define TRACE(cls)												TRACEN(cls,0,"","","","","","","","","","")
#define TRACE1(cls,  p1)										TRACEN(cls,1,p1,"","","","","","","","","")
#define TRACE2(cls,  p1, p2)									TRACEN(cls,2,p1,p2,"","","","","","","","")
#define TRACE3(cls,  p1, p2, p3)								TRACEN(cls,3,p1,p2,p3,"","","","","","","")
#define TRACE4(cls,  p1, p2, p3, p4)							TRACEN(cls,4,p1,p2,p3,p4,"","","","","","")
#define TRACE5(cls,  p1, p2, p3, p4, p5)						TRACEN(cls,5,p1,p2,p3,p4,p5,"","","","","")
#define TRACE6(cls,  p1, p2, p3, p4, p5, p6)					TRACEN(cls,6,p1,p2,p3,p4,p5,p6,"","","","")
#define TRACE7(cls,  p1, p2, p3, p4, p5, p6, p7)				TRACEN(cls,7,p1,p2,p3,p4,p5,p6,p7,"","","")
#define TRACE8(cls,  p1, p2, p3, p4, p5, p6, p7, p8)			TRACEN(cls,8,p1,p2,p3,p4,p5,p6,p7,p8,"","")
#define TRACE9(cls,  p1, p2, p3, p4, p5, p6, p7, p8, p9)		TRACEN(cls,9,p1,p2,p3,p4,p5,p6,p7,p8,p9,"")
#define TRACE10(cls, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10)	TRACEN(cls,10,p1,p2,p3,p4,p5,p6,p7,p8,p9,p10)

std::ostream &operator<<(std::ostream&, RECT*);
std::ostream &operator<<(std::ostream&, D3DPRESENT_PARAMETERS*);
std::ostream &operator<<(std::ostream&, REFIID riid);
std::ostream &operator<<(std::ostream&, D3DVIEWPORT8 *);

DWORD rgb16to32(WORD color);
WORD rgb32to16(DWORD color);

#define STDFUNC(func) HRESULT func
#define STDFUNC_(type, func) type func

#include "MyDirect3D8.h"
#include "MyDirect3DDevice8.h"
#include "MyDirect3DSurface8.h"
#include "MyDirect3DVertexBuffer8.h"
#include "MyDirect3DIndexBuffer8.h"

