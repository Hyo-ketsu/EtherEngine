#include <EngineLibrary/AssemblyHolder.h>
#include <EngineLibrary/EngineLibraryUtility.h>

using namespace System::Reflection;
using namespace System::Runtime::Loader;


//----- AssemblyHolder ��`
namespace EtherEngine {
    // �R���X�g���N�^
    AssemblyHolder::AssemblyHolder(void) 
        : ms_loadAssemblyPath(nullptr) 
        , ms_assembly(nullptr)
        , ms_assemblyLoadContext(gcnew AssemblyLoadContext("EngineContext", true)) {
    }
    // �f�X�g���N�^
    AssemblyHolder::~AssemblyHolder(void) {
        this->!AssemblyHolder();
    }
    // �t�@�C�i���C�U
    AssemblyHolder::!AssemblyHolder(void) {
        DeleteAssembly();
        ms_assemblyLoadContext = nullptr;
    }


    // �A�Z���u�����擾����
    System::Reflection::Assembly^ AssemblyHolder::GetAssembly(void) {
        if (ms_assembly == nullptr) {
            //----- assembly��ǂݍ���
            LoadAssembly();
        }
        else {
            //----- �A�Z���u���ԋp
            return ms_assembly;
        }
    }


    // �A�Z���u����ǂݍ���h
    bool AssemblyHolder::LoadAssembly(void) {
        //----- dll���t�@�C���`�F�b�N
        if (System::IO::Path::Exists(ms_loadAssemblyPath) == false) return false;
        if (System::IO::Path::HasExtension(ms_loadAssemblyPath) && System::IO::Path::GetExtension(ms_loadAssemblyPath) != ".dll") return false;
                

        //----- �ǂݍ���
        ms_assembly = ms_assemblyLoadContext->LoadFromAssemblyPath(ms_loadAssemblyPath);

        return true;
    }
    // ���ݓǂݍ��݃A�Z���u�����폜����
    void AssemblyHolder::DeleteAssembly(void) {
        ms_assembly = nullptr;
        ms_assemblyLoadContext->Unload();
        System::GC::Collect();
        System::GC::WaitForPendingFinalizers();
    }


    // ���ݓǂݍ��݃A�Z���u�������݂��邩
    bool AssemblyHolder::IsLoadAssemblyEnable(void) {
        return ms_assembly == nullptr ? false : true;
    }
}
