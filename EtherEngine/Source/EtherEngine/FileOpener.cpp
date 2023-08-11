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
    }
}
