#include <Base/EtherEngineUtility.h>


namespace EtherEngine {
    namespace Utilty {
        // 重複したオブジェクトに名前を付ける
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
        // 重複したオブジェクトに名前を付ける
        void DuplicationName(std::string* name, const uint number, const DuplicationNameObjectName& type) {
            *name = DuplicationName(*name, number, type);
        }
        // 重複したオブジェクト名か判定する
        bool IsDuplicationName(const std::string& name, const std::string& base, const uint number, const DuplicationNameObjectName& type) {
            //----- 検索
            auto newName = DuplicationName(std::string(""), number, type);
            auto namePos = name.find(newName);

            //----- 確認
            if (namePos == std::string::npos) {
                return false;
            }
            else {
                return true;
            }
        }
    }
}
