#ifndef I_DIRECTXINCLUDE_H
#define I_DIRECTXINCLUDE_H
#include <Base/stdafx/BaseInclude.h>

#include <d3d11.h>
#pragma comment(lib,"d3d11.lib")
#include <Windows.h>
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "user32.lib")
#pragma comment(lib, "gdi32.lib")
#pragma comment(lib, "Ole32.lib")


#include <Xinput.h>
#pragma comment(lib, "Xinput.lib")
#include <dxgi1_6.h>
#pragma comment(lib, "dxgi.lib")

#include <d3dcompiler.h>
#pragma comment(lib, "d3dcompiler.lib")


#include <processthreadsapi.h>


#include <DirectXTex/DirectXTex.h>
#ifdef _DEBUG
#pragma comment(lib, "DirectXTex/x64/Debug/DirectXTex.lib")
#else
#pragma comment(lib, "DirectXTex/x64/Release/DirectXTex.lib")
#endif


#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#ifdef _DEBUG
#pragma comment(lib, "assimp/x64/Debug/assimp-vc142d.lib")
#else
#pragma comment(lib, "assimp/x64/Release/assimp-vc142.lib")
#endif



#endif // !I_DIRECTXINCLUDE_H
