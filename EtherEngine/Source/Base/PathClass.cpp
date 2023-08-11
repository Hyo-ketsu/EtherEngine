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


    // 拡張子含めたファイル名取得
    std::string PathClass::GetFile(void) const {
        return path(m_path).filename().string();
    }
    // ディレクトリ名を取得
    PathClass PathClass::GetDirectory(void) const {
        return PathClass(path(m_path).remove_filename().string());
    }
    // 拡張子名を取得
    std::string PathClass::GetExtension(void) const {
        return path(m_path).extension().string();
    }


    // 拡張子を持っているか
    bool PathClass::HasExtension(void) const {
        return path(m_path).has_extension();
    }


    // 現在収納されているディレクトリを全て生成する
    bool PathClass::CreateDirectories(void) const {
        return create_directories(path(m_path));
    }


    // パス要素追加
    const PathClass PathClass::operator/=(const std::string& path) const {
        return PathClass((std::filesystem::path(m_path) /= path).string());
    }
    // パス文字列追加
    const PathClass PathClass::operator+=(const std::string& string) const {
        return PathClass((std::filesystem::path(m_path) += string).string());
    }


    // ファイルが存在しているか
    bool PathClass::IsExists(void) const {
        return exists(path(m_path));
    }
    // 通常ファイルか
    bool PathClass::IsFile(void) const {
        return is_regular_file(path(m_path));
    }
    // ディレクトリか　
    bool PathClass::IsDirectory(void) const {
        return is_directory(path(m_path));
    }


    // 配下ディレクトリをすべて取得する
    std::vector<PathClass> PathClass::GetLowerDirectory(void) const {
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
