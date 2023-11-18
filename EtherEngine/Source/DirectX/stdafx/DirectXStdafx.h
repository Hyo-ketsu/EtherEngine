#include <Base/stdafx/BaseStdafx.h>


#include <d3d11.h>
#pragma comment(lib,"d3d11.lib")
#include <Windows.h>
#pragma comment(lib, "winmm.lib")

#include <Xinput.h>
#pragma comment(lib, "Xinput.lib")
#include <dxgi1_6.h>
#pragma comment(lib, "dxgi.lib")

#include <d3dcompiler.h>
#pragma comment(lib, "d3dcompiler.lib")


#include <processthreadsapi.h>

#ifdef _X86_
#ifdef _DEBUG
#pragma comment(lib, "DirectXTex/Win32/Debug/DirectXTex.lib")
#else
#pragma comment(lib, "DirectXTex/Win32/Release/DirectXTex.lib")
#endif
#else
#ifdef _DEBUG
#pragma comment(lib, "DirectXTex/x64/Debug/DirectXTex.lib")
#else
#pragma comment(lib, "DirectXTex/x64/Release/DirectXTex.lib")
#endif
#endif


#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#ifdef _DEBUG
#pragma comment(lib, "assimp/x64/Debug/assimp-vc142d.lib")
#else
#pragma comment(lib, "assimp/x64/Release/assimp-vc142.lib")
#endif
