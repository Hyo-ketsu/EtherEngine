#include <EtherEngine/FileDeleter.h>
#include <Base/BaseDefines.h>
#include <EtherEngine/ProjectMediation.h>


//----- FileDelete 宣言
namespace EtherEngine {
    // 入力ファイル・ディレクトリを削除する
    bool FileDelete(const PathClass& deleteFile, bool isRecursion) {
        //----- ファイル存在チェック
        if (deleteFile.IsExists() == false) return false;

        //----- 拡張子取得
        auto extension = deleteFile.GetExtension();

        //----- 各ファイルごと処理
        do {
            //----- ディレクトリ・非拡張子削除
            if (deleteFile.IsDirectory()) {
                return deleteFile.DeleteFiles(isRecursion);
            }

            //----- 通常ファイル処理
            if (extension == FileDefine::SCENE) {
            }
            if (extension == FileDefine::CPPCLISCRIPT) {
                ProjectMediation::Get()->DeleteSource(deleteFile);
            }

            //----- 削除処理
            return deleteFile.DeleteFiles();
        } while (false);
    }
}
