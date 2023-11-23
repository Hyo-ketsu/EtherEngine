#include <EngineLibrary/EngineLibraryUtility.h>
#include <EngineLibrary/AssemblyHolder.h>
// @ MEMO : w_cahr����char�ɂ��Ă���̂ŃG���[�N��������
     

//----- ������ϊ��֐�
namespace EtherEngine {
}


//----- ���S�C�����擾�֐� �錾
namespace EtherEngine {
    // ���S�C�������擾����
    std::string GetFullName(const std::string& className, const uint index, const bool isSystem) {
        //----- �ϐ��錾
        System::String^ manageClassName = gcnew System::String(className.c_str());
        uint currentIndex = 0;

        //----- �A�Z���u���̃��[�h
        auto assembly = AssemblyHolder::GetAssembly();

        //----- �^�̎擾
        auto types = assembly->GetTypes();

        //----- �S�^����̌���
        for each (auto type in types) {
            //----- System���O��Ԃ̏ȗ�
            if (isSystem == true) {
                if (type->Namespace == "System") {
                    continue;
                }
            }

            //----- �����^����
            if (type->Name == manageClassName) {
                if (index == currentIndex) {
                    //----- �C���f�b�N�X�������B�ԋp
                    return ManageToUnmanage::String(type->FullName);
                }
                else {
                    //----- �C���f�b�N�X������Ȃ��B�C���f�b�N�X��i�߂�
                    currentIndex++;
                    continue;
                }
            }

            //----- ���S�C��������v���邩
            if (type->FullName == manageClassName) {
                return className;
            }
        }

        //----- �i���炭�j�N���X�������݂��Ȃ��B��O���o
        throw std::exception("Error! No Class Name!");
    }
    // ���S�C�������擾����
    System::String^ GetFullName(System::String^ className, const uint index, const bool isSystem) {
        //----- �ϐ��錾
        uint currentIndex = 0;

        //----- �A�Z���u���̃��[�h
        auto assembly = AssemblyHolder::GetAssembly();

        //----- �^�̎擾
        auto types = assembly->GetTypes();

        //----- �S�^����̌���
        for each (auto type in types) {
            //----- System���O��Ԃ̏ȗ�
            if (isSystem == true) {
                if (type->Namespace == "System") {
                    continue;
                }
            }

            //----- �����^����
            if (type->Name == className) {
                if (index == currentIndex) {
                    //----- �C���f�b�N�X�������B�ԋp
                    return type->FullName;
                }
                else {
                    //----- �C���f�b�N�X������Ȃ��B�C���f�b�N�X��i�߂�
                    currentIndex++;
                    continue;
                }
            }

            //----- ���S�C��������v���邩
            if (type->FullName == className) {
                return className;
            }
        }

        //----- �i���炭�j�N���X�������݂��Ȃ��B��O���o
        throw std::exception("Error! No Class Name!");
    }
}
