#ifndef I_COMPONENT_H
#define I_COMPONENT_H
// @ MEMO : 実際にユーザーが記述するためのもととなるクラス
#include <Base/NativeGameObject.h>
#include <EngineLibrary/ComponentInterface.h>
#include <EngineLibrary/EngineLibraryUtility.h>
#include <EngineLibrary/BaseObject.h>
ref class GameObject;
#include <EngineLibrary/GameObject.h>


#pragma managed
//----- Component 宣言
namespace EtherEngine {
    public ref class Component : public BaseObject {
    public:
        // コンストラクタ
        Component(void);


        // ゲームオブジェクト
        property GameObject^ ParentGameObject {
            GameObject^ get(void);
        internal: 
            void set(GameObject^ value);
        }


        // 開始処理
        virtual void Start(void) {}
        // 更新処理
        virtual void Update(void) {}
        // 削除時処理
        virtual void Delete(void) {}
        // 衝突開始処理
        virtual void CollisionStart(void) {}
        // 衝突終了処理
        virtual void CollisionEnd(void) {}
        // 衝突処理
        virtual void CollisionHit(void) {}
        
    private:
        GameObject^ m_gameObject; // 自身を保持しているゲームオブジェクト
    };
}


#endif // !I_COMPONENT_H
