#include <EtherEngine/FileOpener.h>
#include <Base/SceneLoader.h>
#include <Base/BaseDefines.h>


//----- FileOpen ��`
namespace EtherEngine {
    // �t�@�C�����J��
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