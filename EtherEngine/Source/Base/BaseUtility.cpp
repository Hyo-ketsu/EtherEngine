#include <Base/BaseUtility.h>
#include <Base/EditorException.h>
#include <chrono>


//----- �����m�F�p�N���X ��`
namespace EtherEngine {
    // �R���X�g���N�^
    EnableCheckClass::EnableCheckClass(void) {
        m_sharedPtr = std::make_shared<nullptr_t>();
    }
    // �R�s�[�R���X�g���N�^
    EnableCheckClass::EnableCheckClass(const EnableCheckClass& copy) {
        m_sharedPtr = copy.m_sharedPtr;
    }


    // �����m�F�p�̃L�[���擾����
    std::weak_ptr<nullptr_t> EnableCheckClass::GetEnableKey(void) {
        return std::weak_ptr<nullptr_t>(m_sharedPtr);
    }
}


//----- �֗��֐� ��`
namespace EtherEngine {
    namespace Utility {
        // ���̓t�@�C���̒��g��S�ēǂݎ��
        std::string RoadFileAll(const std::string& file) {
            //----- �t�@�C���I�[�v��
            std::ifstream readFile(file, std::ios::in | std::ios::binary);
            if (readFile.is_open() == false) throw EditorException((std::string("Exception! SceneData : ") + file + " Non file!").c_str());

            //----- �ǂݍ���
            // @ Memo : EOF�܂őS�ēǂݍ��݂܂�
            std::string fileString;
            std::string line;
            while (std::getline(readFile, line)) {
                fileString += line;// += '\n';
            }

            //----- �ԋp
            return std::move(fileString);
        }


        // �����񂩂����̕������u������
        std::string StringSubstitution(const std::string& target, const std::string& dest, const std::string& replacement) {
            //----- �ϐ��錾
            std::string ret = target;
            int pos = std::string::npos;   // ���������̈ʒu

            //----- ���������_��`
            auto find = [&]() -> bool {
                pos = ret.find(dest);
                if (pos == std::string::npos) {
                    return false;
                }
                else {
                    return true;
                }
            };

            //----- �u��
            while (find()) {
                ret.replace(pos, dest.size(), replacement);
            }

            //----- �ԋp
            return ret;
        }
    }
}
