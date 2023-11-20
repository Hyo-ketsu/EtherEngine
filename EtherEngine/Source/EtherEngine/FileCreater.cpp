#include <EtherEngine/FileCreater.h>
#include <Base/EtherEngineUtility.h>
#include <EtherEngine/ProjectMediation.h>


namespace EtherEngine {
    // @ ファイルを生成、同時に(行うのであれば)処理を行う
    PathClass FileCreate(const std::string& fileName, const PathClass& extension, const PathClass& createDirectory,
        const Utility::DuplicationNameObjectName& nameRule, const std::string& fileString, bool isCreateDirectory) {
        //----- ファイル生成
        PathClass createFile = GetFileName(createDirectory / fileName += extension, nameRule);
        if (isCreateDirectory) {
            //----- ディレクトリ作成
            createFile.Create_Directorie();
        }
        else {
            //----- 通常ファイル作成
            createFile.Create_File(fileString);
        }

        //----- 各ファイルごと処理
        do {
            //----- ディレクトリ処理
            if (isCreateDirectory) {
                break;
            }

            //----- 生成ファイル(拡張子)ごとに処理
            if (extension.Get() == FileDefine::Extended::SCENE) {
                break;
            }
            else if (extension.Get() == FileDefine::Extended::SCRIPT) {
                ProjectMediation::Get()->AddSource(createFile);
                break;
            }
        } while (false);

        //----- 返却
        return createFile;
    }
}
