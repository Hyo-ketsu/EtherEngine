#ifndef I_GAMEOBJECT_H
#define I_GAMEOBJECT_H
#include <Base/NativeGameObject.h>
#include <Base/Handle.h>
#include <EngineLibrary/BaseObject.h>
namespace EtherEngine {
    ref class Component;
}
#include <EngineLibrary/Component.h>
#include <EngineLibrary/AttributeDefine.h>
#include <EngineLibrary/Scene.h>


// @ MEMO : 余力があればGetComponentあたりを高速化する


#pragma managed
//----- GameObject 宣言
namespace EtherEngine {
    // ゲームオブジェクト
    public ref class GameObject : public BaseObject {
    public:
        // コンストラクタ
        GameObject(void);
        // デストラクタ
        ~GameObject(void);
        // ファイナライザ
        !GameObject(void);


        // 自身を削除する
        void Destroy(void);


        // ネイティブゲームオブジェクト
        property Handle<NativeGameObject> NGameObject {
            Handle<NativeGameObject> get(void) { return m_handle->GetHandle(); }
        }


        // 入力したシーンのオブジェクトか判定する
        bool IsSceneObject(Scene^ scene);


        // コンポーネントを追加する
        // @ Temp : 追加するコンポーネント
        // @ Ret  : 取得したコンポーネント
        generic <typename ComponentType> where ComponentType : Component, gcnew()
        ComponentType AddComponent(void);
        // コンポーネントを取得する
        // @ Temp : 取得するコンポーネント
        // @ Ret  : 取得したコンポーネント
        generic <typename ComponentType> where ComponentType : Component, gcnew()
        ComponentType GetComponent(void);
        // コンポーネントを取得する
        // @ Temp : 取得するコンポーネント
        // @ Ret  : 取得したコンポーネント
        generic <typename ComponentType> where ComponentType : Component, gcnew()
        System::Collections::Generic::List<ComponentType>^ GetComponents(void);
        // コンポーネントを削除する
        // @ Temp : 削除コンポーネント
        // @ Ret  : 削除が行われたか
        generic <typename ComponentType> where ComponentType : Component, gcnew()
        bool DeleteComponent(void);

    private:
        [Attribute::OutputAttribute] System::Collections::Generic::List<Component^>^ m_componentList;
        Handle<NativeGameObject>* m_handle;
        SceneIDType m_thisObjectScene;
    };
}


#endif // !I_GAMEOBJECT_H
