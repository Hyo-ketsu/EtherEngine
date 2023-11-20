#include <EngineLibrary/AssemblyHolder.h>


//----- AssemblyHolder ��`
namespace EtherEngine {
    // �A�Z���u�����擾����
    System::Reflection::Assembly^ AssemblyHolder::GetAssembly(void) {
        if (static_cast<System::Reflection::Assembly^>(ms_assembly) == nullptr) {
            //----- �����ǂݍ���ł��Ȃ��B���݂̃A�Z���u�����擾
            return System::Reflection::Assembly::GetCallingAssembly();
        }
        else {
            //----- �A�Z���u���ԋp
            return ms_assembly;
        }
    }


    // �A�Z���u����ǂݍ���
    bool AssemblyHolder::LoadAssembly(const PathClass& assemblyPath) {
        //----- dll���t�@�C���`�F�b�N
        if (assemblyPath.IsExists() == false) return false;
        if (assemblyPath.HasExtension() && assemblyPath.GetExtension() != "dll") return false;

        //----- �ǂݍ���
        ms_assembly = System::Reflection::Assembly::LoadFrom(UnToManage(assemblyPath));
        return true;
    }
    // ���ݓǂݍ��݃A�Z���u�����폜����
    void AssemblyHolder::DeleteAssembly(void) {
        ms_assembly = nullptr;
    }


    // ���ݓǂݍ��݃A�Z���u�������݂��邩
    bool AssemblyHolder::IsLoadAssemblyEnable(void) {
        return static_cast<System::Reflection::Assembly^>(ms_assembly) == nullptr ? false : true;
    }


    msclr::gcroot<System::Reflection::Assembly^> AssemblyHolder::ms_assembly = nullptr;   // ���ݕێ����Ă���A�Z���u��
    bool AssemblyHolder::ms_isBuild = true;      // build���������Ă��邩
    bool AssemblyHolder::ms_isUpdate = false;    // �\�����[�V�������X�V����Ă��邩
}
