#ifndef I_SCENE_H
#define I_SCENE_H
#include <EngineLibrary/EngineLibraryDefine.h>
#include <EngineLibrary/BaseObject.h>

//----- Scene 宣言
namespace EtherEngine {
    // シーン
    // @ MEMO : ひとまずクラスという体にして現状Jsonを読み込むだけにします
    public ref class Scene : BaseObject {
    public:
        // コンストラクタ
        // @ Arg1 : Json読み込みディレクトリ
        Scene(PathString json);

    private:
    };
}


#endif // !I_SCENE_H
