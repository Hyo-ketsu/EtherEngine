#include <Base/EtherEngineUtility.h>


namespace EtherEngine {
    namespace Utilty {
        // �d�������I�u�W�F�N�g�ɖ��O��t����
        std::string DuplicationName(const std::string& name, const uint number, const DuplicationNameObjectName& type) {
            switch (type) {
            case DuplicationNameObjectName::PARENTHESES_NUMBER:
                return name + "(" + std::to_string(number) + ")";
                break;
            case DuplicationNameObjectName::NUMBER:
                return name + " " + std::to_string(number);
                break;
            case DuplicationNameObjectName::UNDERSCORE_NUMBER:
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
