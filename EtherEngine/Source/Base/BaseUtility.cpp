#include <Base/BaseUtility.h>
#include <Base/EditorException.h>
#include <chrono>


//----- 生存確認用クラス 定義
namespace EtherEngine {
    // コンストラクタ
    EnableCheckClass::EnableCheckClass(void) {
        m_sharedPtr = std::make_shared<nullptr_t>();
    }
    // コピーコンストラクタ
    EnableCheckClass::EnableCheckClass(const EnableCheckClass& copy) {
        m_sharedPtr = copy.m_sharedPtr;
    }


    // 生存確認用のキーを取得する
    std::weak_ptr<nullptr_t> EnableCheckClass::GetEnableKey(void) {
        return std::weak_ptr<nullptr_t>(m_sharedPtr);
    }
}


//----- 便利関数 定義
namespace EtherEngine {
    namespace Utility {
        // 入力ファイルの中身を全て読み取る
        std::string RoadFileAll(const std::string& file) {
            //----- ファイルオープン
            std::ifstream readFile(file, std::ios::in | std::ios::binary);
            if (readFile.is_open() == false) throw EditorException((std::string("Exception! SceneData : ") + file + " Non file!").c_str());

            //----- 読み込み
            // @ Memo : EOFまで全て読み込みます
            std::string fileString;
            std::string line;
            while (std::getline(readFile, line)) {
                fileString += line;// += '\n';
            }

            //----- 返却
            return std::move(fileString);
        }


        // 文字列から特定の文字列を置換する
        std::string StringSubstitution(const std::string& target, const std::string& dest, const std::string& replacement) {
            //----- 変数宣言
            std::string ret = target;
            int pos = std::string::npos;   // 検索文字の位置

            //----- 検索ラムダ定義
            auto find = [&]() -> bool {
                pos = ret.find(dest);
                if (pos == std::string::npos) {
                    return false;
                }
                else {
                    return true;
                }
            };

            //----- 置換
            while (find()) {
                ret.replace(pos, dest.size(), replacement);
            }

            //----- 返却
            return ret;
        }
    }
}
