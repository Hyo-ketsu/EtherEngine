#include <Base/EtherEngineUtility.h>
#include <Base/EditorException.h>
#include <filesystem>


//----- Json�C���^�[�t�F�[�X ��`
namespace EtherEngine {
    // ���͂���
    void IInOuter::InputString(const std::string& input) {
        Input(Json::parse(input));
    }
}




//----- �֗��N���X ��`
namespace EtherEngine {
    // �t���O���擾����
    bool Trigger::GetFrag(void) {
        bool ret = m_isFrag;
        m_isFrag = false;
        return ret;
    }
    // �t���O���擾����
    Trigger::operator bool (void) {
        return GetFrag();
    }


    // �t���O��ݒ肷��
    void Trigger::SetFrag(const bool& isFrag) {
        m_isFrag |= isFrag;
    }
    // �t���O��ݒ肷��
    void Trigger::operator=(const bool& isFrag) {
        SetFrag(isFrag);
    }
}


namespace EtherEngine {
    namespace Utility {
        // �d�������I�u�W�F�N�g�ɖ��O��t����
        std::string DuplicationName(const std::string& name, const uint number, const DuplicationNameObjectName& type) {
            switch (type) {
            case DuplicationNameObjectName::ParenthesesNumber:
                return name + "(" + std::to_string(number) + ")";
                break;
            case DuplicationNameObjectName::Number:
                return name + " " + std::to_string(number);
                break;
            case DuplicationNameObjectName::UnderscoreNumber:
                return name + "_" + std::to_string(number);
                break;
            default:
                return name;
            }
        }
        // �d�������I�u�W�F�N�g�ɖ��O��t����
        void DuplicationName(std::string* name, const uint number, const DuplicationNameObjectName& type) {
            *name = DuplicationName(*name, number, type);
        }
        // �d�������I�u�W�F�N�g�������肷��
        bool IsDuplicationName(const std::string& name, const std::string& base, const uint number, const DuplicationNameObjectName& type) {
            //----- ����
            auto newName = DuplicationName(std::string(""), number, type);
            auto namePos = name.find(newName);

            //----- �m�F
            if (namePos == std::string::npos) {
                return false;
            }
            else {
                return true;
            }
        }
        // �t�@�C���������֐�
        std::string GetFileName(const PathClass& path, const Utility::DuplicationNameObjectName& nameRule) {
            //----- �ϐ��錾
            int countNumber = 1;
            std::vector<PathClass> directoryFile;
            auto createPath = PathClass(path.GetFile());

            //----- �����g���q�̃t�@�C���擾
            for (auto&& it : path.GetDirectory().GetLowerDirectory()) {
                if (it.GetExtension() == path.GetExtension()) {
                    directoryFile.push_back(it.GetFile());
                }
            }

            //----- �������O�̃t�@�C������
            while (true) {
                //----- �ϐ��錾
                bool isEnable = false; // �����t�@�C���������݂��邩

                //----- ����
                for (auto&& it : directoryFile) {
                    if (createPath.Get() == it.Get()) {
                        //----- ���������݂���B
                        isEnable = true;
                        break;
                    }
                }

                //----- ���������݂�����
                if (isEnable) {
                    //----- ���݂����B���O�𐶐����Ĕ���
                    auto extension = path.GetExtension();
                    createPath = path.GetFileName();
                    Utility::DuplicationName(&createPath.Access(), countNumber, nameRule);
                    createPath = createPath += extension;
                    countNumber++;
                }
                else {
                    //----- ���݂��Ȃ��B�ԋp
                    PathClass ret = path.GetDirectory();
                    ret /= createPath;
                    return ret.Get();
                }
            }
        }
    }
}
