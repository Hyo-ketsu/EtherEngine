#include <EngineLibrary/AssemblyHolder.h>
#include <EngineLibrary/EngineLibraryUtility.h>

using namespace System::Reflection;
using namespace System::Runtime::Loader;


//----- AssemblyHolder ��`
namespace EtherEngine {
    // �R���X�g���N�^
    AssemblyHolder::AssemblyHolder(void) 
        : m_loadAssemblyPath(nullptr) 
        , m_assembly(nullptr)
        , m_assemblyLoadContext(gcnew AssemblyLoadContext("EngineContext", true)) {
    }
    // �f�X�g���N�^
    AssemblyHolder::~AssemblyHolder(void) {
        this->!AssemblyHolder();
    }
    // �t�@�C�i���C�U
    AssemblyHolder::!AssemblyHolder(void) {
        DeleteAssembly();
        m_assemblyLoadContext = nullptr;
    }


    // �A�Z���u�����擾����
    System::Reflection::Assembly^ AssemblyHolder::GetAssembly(void) {
        if (m_assembly == nullptr) {
            //----- assembly��ǂݍ���
            LoadAssembly();
        }
        else {
            //----- �A�Z���u���ԋp
            return m_assembly;
        }
    }


    // �A�Z���u����ǂݍ���
    bool AssemblyHolder::LoadAssembly(void) {
        //----- dll���t�@�C���`�F�b�N
        if (System::IO::Path::Exists(m_loadAssemblyPath) == false) return false;
        if (System::IO::Path::HasExtension(m_loadAssemblyPath) && System::IO::Path::GetExtension(m_loadAssemblyPath) != ".dll") return false;
                
        //----- �ǂݍ���
        m_assembly = m_assemblyLoadContext->LoadFromAssemblyPath(m_loadAssemblyPath);

        return true;
    }
    // ���ݓǂݍ��݃A�Z���u�����폜����
    void AssemblyHolder::DeleteAssembly(void) {
        m_assembly = nullptr;
        m_assemblyLoadContext->Unload();
        System::GC::Collect();
        System::GC::WaitForPendingFinalizers();
    }


    // ���ݓǂݍ��݃A�Z���u�������݂��邩
    bool AssemblyHolder::IsLoadAssemblyEnable(void) {
        return m_assembly == nullptr ? false : true;
    }
}
