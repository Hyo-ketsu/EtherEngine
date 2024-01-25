#ifndef I_SCENE_H
#define I_SCENE_H
#include <EngineLibrary/EngineLibraryDefine.h>
#include <EngineLibrary/BaseObject.h>

//----- Scene 宣言
namespace EtherEngine {
    // シーン
    public ref class Scene : BaseObject {
    public:
        // コンストラクタ
        Scene(void);


        // シーン番号を取得する
        // @ Ret  : 取得したシーン番号
        SceneIDType GetSceneID(void);


        // シーンの情報を取得する
        // @ Arg1 : シーンの中身の情報のJson
        virtual System::String^ GetScene(void) = 0;
    };
}


#endif // !I_SCENE_H
