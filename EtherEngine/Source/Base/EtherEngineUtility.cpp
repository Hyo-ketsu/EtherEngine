#include <Base/EtherEngineUtility.h>
#include <filesystem>


//----- Json�C���^�[�t�F�[�X ��`
namespace EtherEngine {
    // ���͂���
    void IInOuter::Input(const std::string& input) {
        Input(Json::parse(input));
    }
}


//----- �֗��֐� ��`
namespace EtherEngine {
    // ���̓t�@�C���̒��g��S�ēǂݎ��
    std::string RoadFileAll(const std::string& file) {
        //----- �t�@�C���I�[�v��
        std::ifstream readFile(file, std::ios::in | std::ios::binary);
        if (readFile.is_open() == false) throw std::exception((std::string("Exception! SceneData : ") + file + " Non file!").c_str());

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


namespace EtherEngine {
    namespace Utilty {
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
    }
}
