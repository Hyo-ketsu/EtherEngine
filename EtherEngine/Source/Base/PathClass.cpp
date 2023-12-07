#include <Base/PathClass.h>
#include <Base/BaseUtility.h>
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
    PathClass PathClass::GetCurDirectory(void) {
        return PathClass(current_path().string());
    }


    // 拡張子含めたファイル名取得
    std::string PathClass::GetFile(void) const {
        return path(m_path).filename().string();
    }
    // 拡張子含めないファイル名取得
    std::string PathClass::GetFileName(void) const {
        return path(m_path).stem().string();
    }
    // ディレクトリ名を取得
    PathClass PathClass::GetDirectory(void) const {
        return PathClass(path(m_path).remove_filename().string());
    }
    // 拡張子名を取得
    std::string PathClass::GetExtension(void) const {
        return path(m_path).extension().string();
    }


    // 現在収納されているディレクトリを全て生成する
    bool PathClass::Create_Directorie(void) const {
        return create_directories(path(m_path));
    }
    // 現在収納されているディレクトリを生成する
    bool PathClass::Create_Directory(void) const {
        return create_directory(path(m_path));
    }
    // 現在格納されているパスでファイルを生成する
    bool PathClass::Create_File(const std::string& fileString) const {
        //----- 変数宣言
        path path = m_path;

        //----- ファイルが存在しているかチェック
        if (exists(path)) return false;

        //----- ファイルオープン
        std::ofstream ofs(path);
        if (ofs.is_open() == false) return false;

        //----- 文字列格納
        ofs << fileString;

        //----- 返却
        return true; 
    }
    // 現在のファイル・ディレクトリを削除します
    bool PathClass::Delete_File(const bool isAllRemove) const {
        if (isAllRemove) {
            return remove_all(path(m_path)) > 0;
        }
        else {
            return remove(path(m_path));
        }
    }
    // 現在のファイルをコピーする
    bool PathClass::Copy_File(const PathClass& copyPath) const {
        //----- コピーが可能か判定
        if (copyPath.IsExists() == false) return false;
        if (this->IsFile() == false) return false;

        //----- 同名ファイルを対象パスに作成
        auto myFileString = Utility::RoadFileAll(m_path);
        (copyPath / this->GetFile()).Create_File(myFileString);

        return true;
    }


    // パス要素追加
    PathClass& PathClass::operator/=(const std::string& path) {
        m_path = (std::filesystem::path(m_path) /= path).string();
        return *this;
    }
    // パス要素追加
    PathClass PathClass::operator/(const std::string& path) const {
        return PathClass((std::filesystem::path(m_path) /= path).string());
    }
    // パス文字列追加
    PathClass& PathClass::operator+=(const std::string& string)  {
        m_path = (std::filesystem::path(m_path) += string).string();
        return *this;
    }
    // パス文字列追加
    PathClass PathClass::operator+(const std::string& string) const {
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
    // 拡張子を持っているか
    bool PathClass::HasExtension(void) const {
        return path(m_path).has_extension();
    }


    // 配下ディレクトリをすべて取得する
    std::vector<PathClass> PathClass::GetLowerDirectory(void) const {
        //----- 宣言
        std::vector<PathClass> ret;

        //----- ディレクトリでなければそのまま返却
        if (this->IsDirectory() == false) return ret;

        //----- 全ての下位ファイル取得
        for (auto& it : directory_iterator(path(m_path))) {
            ret.push_back(path(it).string());
        }

        //----- 返却
        return ret;
    }
}
