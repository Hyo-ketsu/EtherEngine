#include <Base/PathClass.h>
#include <filesystem>


//----- PathClass 定義
namespace EtherEngine {
    using namespace std::filesystem;

    // コンストラクタ
    PathClass::PathClass(const std::string& path) 
        : m_path(path) {
    }
    // コンストラクタ
    PathClass::PathClass(const char* path) 
        : m_path(path) {
    }


    // カレントディレクトリゲッター
    std::string PathClass::GetCurDirectory(void) {
        return current_path().string();
    }


    // 拡張子を持っているか
    bool PathClass::HasExtension(void) const {
        return path(m_path).has_extension();
    }


    // 配下ディレクトリをすべて取得する
    std::vector<PathClass> PathClass::GetDirectory(void) const {
        //----- 宣言
        std::vector<PathClass> ret;

        //----- 全ての下位ファイル取得
        for (auto& it : directory_iterator(path(m_path))) {
            ret.push_back(path(it).string());
        }

        //----- 返却
        return ret;
    }
}
