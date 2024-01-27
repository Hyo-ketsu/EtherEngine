#ifndef I_ASSEMBLYHOLDER_H
#define I_ASSEMBLYHOLDER_H
#include <EngineLibrary/EngineLibraryDefine.h>
#include <EngineLibrary/ManageSingleton.h>


#pragma managed
//----- AssemblyHolder ��`
namespace EtherEngine {
    // �Q�[���̃A�Z���u����ێ������N���X
    public ref class AssemblyHolder {
        ETHER_ENGINE_MANAGE_SINGLETON(AssemblyHolder);
    public:
        // �f�X�g���N�^
        ~AssemblyHolder(void);
        // �t�@�C�i���C�U
        !AssemblyHolder(void);


        // �A�Z���u�����擾����
        // @ Ret  : �擾�����A�Z���u���A�܂��͌��݂̃A�Z���u��
        System::Reflection::Assembly^ GetAssembly(void);


        property System::String^ LoadAssemblyPath {
            System::String^ get(void) { return m_loadAssemblyPath; }
            void set(System::String^ value) { m_loadAssemblyPath = value; }
        }


        // �A�Z���u����ǂݍ���
        // @ Ret  : �A�Z���u�����ǂݍ��߂���
        bool LoadAssembly(void);
        // ���ݓǂݍ��݃A�Z���u�����폜����
        void DeleteAssembly(void);


        // ���ݓǂݍ��݃A�Z���u�������݂��邩
        // @ Ret  : �A�Z���u�����擾���Ă��邩
        bool IsLoadAssemblyEnable(void);

    private:
        System::String^ m_loadAssemblyPath;   // assembly��ǂݍ��ރp�X
        System::Reflection::Assembly^ m_assembly;   // ���ݕێ����Ă���A�Z���u��
        System::Runtime::Loader::AssemblyLoadContext^ m_assemblyLoadContext;   // ���ݕێ����Ă���A�Z���u��
    };
}


#endif // !I_ASSEMBLYHOLDER_H
