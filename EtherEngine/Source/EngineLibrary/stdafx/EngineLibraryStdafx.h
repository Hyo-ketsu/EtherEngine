#ifndef I_CPPCLISTDAFX_H
#define I_CPPCLISTDAFX_H
#include <EngineLibrary/stdafx/EngineLibraryInclude.h>


#ifdef _ENGINELIBRARY
#define ENGINELIBRARY_API __declspec(dllexport)
#else
#define ENGINELIBRARY_API __declspec(dllimport)
#endif


#endif 
