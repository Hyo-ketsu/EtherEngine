#ifndef I_CPPCLISTDAFX_H
#define I_CPPCLISTDAFX_H
#include <DirectX/stdafx/DirectXStdafx.h>


#ifdef _ENGINELIBRARY
#define ENGINELIBRARY_API __declspec(dllexport)
#else
#define ENGINELIBRARY_API __declspec(dllimport)
#endif


#include <msclr/gcroot.h>
#include <vcclr.h>


#endif 
