#ifndef I_COMPONENT_H
#define I_COMPONENT_H
// @ MEMO : 実際にユーザーが記述するためのもととなるクラス
#include <Base/NativeGameObject.h>
#include <EngineLibrary/AttributeDefine.h>
#include <EngineLibrary/ComponentInterface.h>
#include <EngineLibrary/EngineLibraryUtility.h>
#include <EngineLibrary/BaseObject.h>


//----- 前方宣言
namespace EtherEngine {
    ref class GameObject;
}


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
            void set(GameObject^ value);
        }


        // 追加時処理
        virtual void Create(void) {}
        // 開始処理
        virtual void Start(void) {}
        // 更新処理
        virtual void Update(void) {}
        // 更新後処理
        virtual void LateUpdate(void) {}
        // 削除時処理
        virtual void Delete(void) {}
        // 衝突開始処理
        virtual void CollisionStart(void) {}
        // 衝突終了処理
        virtual void CollisionEnd(void) {}
        // 衝突処理
        virtual void CollisionHit(void) {}
        
    private:
        [Attribute::OutputAttribute]
        GameObject^ m_gameObject;  // 親ゲームオブジェクトのID
    };
}


#endif // !I_COMPONENT_H
