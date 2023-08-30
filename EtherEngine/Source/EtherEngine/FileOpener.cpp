#include <EtherEngine/FileOpener.h>
#include <Base/SceneLoader.h>
#include <Base/BaseDefines.h>


//----- FileOpen 定義
namespace EtherEngine {
    // ファイルを開く
    void FileOpen(const PathClass& file) {
        do {
            //----- scene
            if (FileDefine::SCENE == file.GetExtension()) {
                SceneLoader::Get()->MoveScene(file);
                break;
            }
        } while (false);

        //----- 指定されたファイル以外
        // @ MEMO : system使ってるので後で修正
        system((std::string("start ") + file.Get()).c_str());
    }
}
