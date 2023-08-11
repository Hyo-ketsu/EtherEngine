#include <Base/EtherEngineUtility.h>


//----- Jsonインターフェース 定義
namespace EtherEngine {
    // 入力する
    void IInOuter::Input(const std::string& input) {
        Input(Json::parse(input));
    }
}


//----- 便利関数 定義
namespace EtherEngine {
    // 入力ファイルの中身を全て読み取る
    std::string RoadFileAll(const std::string& file) {
        //----- ファイルオープン
        std::ifstream scene(file);
        if (scene.is_open() == false) throw std::exception((std::string("Exception! SceneData : ") + file + " Non file!").c_str());

        //----- 読み込み
        // @ Memo : EOFまで全て読み込みます
        std::string fileString;
        std::string line;
        while (std::getline(scene, line)) {
            fileString += line;
        }

        //----- 返却
        return std::move(fileString);
    }
}


namespace EtherEngine {
    namespace Utilty {
        // 重複したオブジェクトに名前を付ける
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
