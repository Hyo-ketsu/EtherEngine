#ifndef I_ASSEMBLYHOLDER_H
#define I_ASSEMBLYHOLDER_H
#include <CPPCLI/ManageSingleton.h>
#include <CPPCLI/CPPCLIUtility.h>


//----- AssemblyHolder ��`
namespace EtherEngine {
    // �Q�[���̃A�Z���u����ێ������N���X
    class AssemblyHolder {
    public:
        // �A�Z���u�����擾����
        // @ Ret  : �擾�����A�Z���u���A�܂��͌��݂̃A�Z���u��
        static System::Reflection::Assembly^ GetAssembly(void);


        // �A�Z���u����ǂݍ���
        // @ Ret  : �A�Z���u�����ǂݍ��߂���
        // @ Arg1 : �ǂݍ��ރA�Z���u����
        static bool LoadAssembly(const PathClass& assemblyPath);
        // ���ݓǂݍ��݃A�Z���u�����폜����
        static void DeleteAssembly(void);


        // ���ݓǂݍ��݃A�Z���u�������݂��邩
        // @ Ret  : �A�Z���u�����擾���Ă��邩
        static bool IsLoadAssemblyEnable(void);

    private:
        /// @brief �R���X�g���N�^
        AssemblyHolder(void) {}


        static msclr::gcroot<System::Reflection::Assembly^> ms_assembly;   // ���ݕێ����Ă���A�Z���u��
        static bool ms_isBuild;     // build���������Ă��邩
        static bool ms_isUpdate;    // �\�����[�V�������X�V����Ă��邩
    };
}


#endif // !I_ASSEMBLYHOLDER_H
