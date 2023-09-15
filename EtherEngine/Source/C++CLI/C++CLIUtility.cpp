#include <C++CLI/C++CLIUtility.h>
#include <C++CLI/AssemblyHolder.h>
// @ MEMO : w_cahr����char�ɂ��Ă���̂ŃG���[�N��������
     

//----- ������ϊ��֐�
namespace EtherEngine {
    // .NET�������C++������ɕϊ�����
    std::string ManageToUn(System::String^ manage) {
        //----- �錾�E�擾
        std::string ret;
        auto wchars = manage->ToCharArray();

        //----- �m��
        ret.reserve(wchars->Length);

        //----- �ϊ�
        for (int i = 0; i < wchars->Length; i++) {
            ret.push_back(static_cast<char>(wchars[i]));
        }

        return ret;
    }
    // C++�������.NET������ɕϊ�����
    System::String^ UnToManage(const std::string& un) {
        //----- �錾
        System::String^ ret;

        //----- �ϊ�
        ret = gcnew System::String(un.c_str());

        //----- �ԋp
        return ret;
    }
}


//----- ���S�C�����擾�֐� �錾
namespace EtherEngine {
    // ���S�C�������擾����
    std::string GetFullName(const std::string& className, const uint index, const bool isSystem) {
        //----- �ϐ��錾
        auto manageClassName = UnToManage(className);
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
                    return ManageToUn(type->FullName);
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
