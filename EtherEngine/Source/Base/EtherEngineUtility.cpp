#include <Base/EtherEngineUtility.h>
#include <filesystem>


//----- Jsonインターフェース 定義
namespace EtherEngine {
    // 入力する
    void IInOuter::InputString(const std::string& input) {
        Input(Json::parse(input));
    }
}


//----- 便利関数 定義
namespace EtherEngine {
    // 入力ファイルの中身を全て読み取る
    std::string RoadFileAll(const std::string& file) {
        //----- ファイルオープン
        std::ifstream readFile(file, std::ios::in | std::ios::binary);
        if (readFile.is_open() == false) throw std::exception((std::string("Exception! SceneData : ") + file + " Non file!").c_str());

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


//----- 便利クラス 定義
namespace EtherEngine {
    // フラグを取得する
    bool Trigger::GetFrag(void) {
        bool ret = m_isFrag;
        m_isFrag = false;
        return ret;
    }
    // フラグを取得する
    Trigger::operator bool (void) {
        return GetFrag();
    }


    // フラグを設定する
    void Trigger::SetFrag(const bool& isFrag) {
        m_isFrag |= isFrag;
    }
    // フラグを設定する
    void Trigger::operator=(const bool& isFrag) {
        SetFrag(isFrag);
    }
}


namespace EtherEngine {
    namespace Utility {
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
        // ファイル名走査関数
        std::string GetFileName(const PathClass& path, const Utility::DuplicationNameObjectName& nameRule) {
            //----- 変数宣言
            int countNumber = 1;
            std::vector<PathClass> directoryFile;
            auto createPath = PathClass(path.GetFile());

            //----- 同じ拡張子のファイル取得
            for (auto&& it : path.GetDirectory().GetLowerDirectory()) {
                if (it.GetExtension() == path.GetExtension()) {
                    directoryFile.push_back(it.GetFile());
                }
            }

            //----- 同じ名前のファイル走査
            while (true) {
                //----- 変数宣言
                bool isEnable = false; // 同じファイル名が存在するか

                //----- 走査
                for (auto&& it : directoryFile) {
                    if (createPath.Get() == it.Get()) {
                        //----- 同名が存在する。
                        isEnable = true;
                        break;
                    }
                }

                //----- 同名が存在したか
                if (isEnable) {
                    //----- 存在した。名前を生成し再判定
                    auto extension = path.GetExtension();
                    createPath = path.GetFileName();
                    Utility::DuplicationName(&createPath.Access(), countNumber, nameRule);
                    createPath = createPath += extension;
                    countNumber++;
                }
                else {
                    //----- 存在しない。返却
                    PathClass ret = path.GetDirectory();
                    ret /= createPath;
                    return ret.Get();
                }
            }
        }
    }
}
