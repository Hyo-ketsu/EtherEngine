#ifndef I_GAMEOBJECT_H
#define I_GAMEOBJECT_H
#include <Base/Transform.h>
#include <Base/Handle.h>
#include <Base/Scene.h>


namespace EtherEngine {
    // シーン上のゲームを構成するオブジェクトを表現する
    class GameObejct {
    public:
        
    public:
        // コンストラクタ
        // @ Arg1 : 座標
        // @ Arg2 : 現在Scene
        GameObejct(const Transform& transform, const Handle<Scene> scene);


    private:
        Transform m_transform;  // 座標
    };
}
// シーン上の
#endif
