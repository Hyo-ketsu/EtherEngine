#include <EngineLibrary/AssemblyHolder.h>
#include <EngineLibrary/EngineLibraryUtility.h>


//----- AssemblyHolder ��`
namespace EtherEngine {
    // �A�Z���u�����擾����
    System::Reflection::Assembly^ AssemblyHolder::GetAssembly(void) {
        if (ms_assembly == nullptr) {
            //----- �����ǂݍ���ł��Ȃ��B���݂̃A�Z���u�����擾
            return System::Reflection::Assembly::GetCallingAssembly();
        }
        else {
            //----- �A�Z���u���ԋp
            return ms_assembly;
        }
    }


    // �A�Z���u����ǂݍ���
    bool AssemblyHolder::LoadAssembly(PathString^ assemblyPath) {
        //----- dll���t�@�C���`�F�b�N
        if (System::IO::Path::Exists(assemblyPath->ToString()) == false) return false;
        if (System::IO::Path::HasExtension(assemblyPath->ToString()) && System::IO::Path::GetExtension(assemblyPath->ToString()) != ".dll") return false;

        //----- �ǂݍ���
        ms_assembly = System::Reflection::Assembly::LoadFrom(assemblyPath->ToString());
        return true;
    }
    // ���ݓǂݍ��݃A�Z���u�����폜����
    void AssemblyHolder::DeleteAssembly(void) {
        ms_assembly = nullptr;
    }


    // ���ݓǂݍ��݃A�Z���u�������݂��邩
    bool AssemblyHolder::IsLoadAssemblyEnable(void) {
        return ms_assembly == nullptr ? false : true;
    }
}
