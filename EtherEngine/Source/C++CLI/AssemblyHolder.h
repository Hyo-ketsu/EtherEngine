#ifndef I_ASSEMBLYHOLDER_H
#define I_ASSEMBLYHOLDER_H
#include <C++CLI/ManageSingleton.h>
#include <C++CLI/C++CLIUtility.h>


//----- AssemblyHolder ��`
namespace EtherEngine {
    // �Q�[���̃A�Z���u����ێ������N���X
    static public ref class AssemblyHolder {
    public:
        // �A�Z���u�����擾����
        // @ Ret  : �擾�����A�Z���u���A�܂��͌��݂̃A�Z���u��
        static System::Reflection::Assembly^ GetAssembly(void) {
            if (ms_assembly == nullptr) {
                //----- �����ǂݍ���ł��Ȃ��B���݂̃A�Z���u�����擾
                return System::Reflection::Assembly::GetCallingAssembly();
            }
            else {
                //----- �A�Z���u���ԋp
                return ms_assembly;
            }
        }
        // ���ݓǂݍ��݃A�Z���u�������݂��邩
        // @ Ret  : �A�Z���u�����擾���Ă��邩
        static bool IsLoadAssemblyEnable(void) {
            return ms_assembly == nullptr ? false : true;
        }


        // �A�Z���u����ǂݍ���
        // @ Ret  : �A�Z���u�����ǂݍ��߂���
        // @ Arg1 : �ǂݍ��ރA�Z���u����
        static bool LoadAssembly(const PathClass& assemblyPath) {
            //----- dll���t�@�C���`�F�b�N
            if (assemblyPath.IsExists() == false) return false;
            if (assemblyPath.HasExtension() && assemblyPath.GetExtension() != "dll") return false;

            //----- �ǂݍ���
            ms_assembly = System::Reflection::Assembly::LoadFrom(UnToManage(assemblyPath));
        }
        // ���ݓǂݍ��݃A�Z���u�����폜����
        static void DeleteAssembly(void) {
            ms_assembly = nullptr;
        }

    private:
        static System::Reflection::Assembly^ ms_assembly = nullptr;   // ���ݕێ����Ă���A�Z���u��
    };
}


#endif // !I_ASSEMBLYHOLDER_H
