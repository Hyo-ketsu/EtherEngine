#include <EngineLibrary/GameObject.h>
#include <Base/BaseUtility.h>
#include <Base/NativeGameObjectStorage.h>
#include <EngineLibrary/BaseObjectStorage.h>
#include <EngineLibrary/GameObjectStorage.h>


#pragma managed
//----- GameObject 定義
namespace EtherEngine {
    // コンストラクタ
    GameObject::GameObject(void) {
        m_handle = new std::remove_pointer_t<decltype(m_handle)>(NativeGameObjectStorage::Get()->CreateGameObject());
    }
    // デストラクタ
    GameObject::~GameObject(void) {
        this->!GameObject();
    }
    // ファイナライザ
    GameObject::!GameObject(void) {
        BaseObjectStorage::Get->DeleteBaseObject(this);
        DELETE_NULL(m_handle);
    }


    // 自身を削除する
    void GameObject::Destroy(void) {   
        GameObjectStorage::Get->DeleteGameObject(this);
    }


    // 入力したシーンのオブジェクトか判定する
    bool GameObject::IsSceneObject(Scene scene) {
        return NGameObject.GetData().GetScene() == scene.GetSceneID();
    }


    // コンポーネントを追加する
    generic <typename ComponentType>
    ComponentType GameObject::AddComponent(void) {
        //----- コンポーネントを追加する
        auto ret = safe_cast<ComponentType>(System::Activator::CreateInstance(ComponentType::typeid));
        ret->ParentGameObject = this;
        m_componentList->Add(ret);
        return ret;
    }
    // コンポーネントを取得する
    generic <typename ComponentType>
    ComponentType GameObject::GetComponent(void) {
        //----- コンポーネント総なめ
        for each (auto it in m_componentList) {
            if (it->GetType() == ComponentType::typeid) {
                return safe_cast<ComponentType>(it);
            }
        }

        //----- ない。
        return ComponentType();
    }
    // コンポーネントを取得する
    generic <typename ComponentType>
    System::Collections::Generic::List<ComponentType>^ GameObject::GetComponents(void) {
        //----- 返却変数宣言
        System::Collections::Generic::List<ComponentType>^ ret = gcnew System::Collections::Generic::List<ComponentType>(0);

        //----- コンポーネント総なめ
        for each (auto it in m_componentList) {
            if (it->GetType() == ComponentType::typeid) {
                ret->Add(safe_cast<ComponentType>(it));
            }
        }

        //----- 返却
        return ret;
    }
    // コンポーネントを削除する
    generic <typename ComponentType>
    bool GameObject::DeleteComponent(void) {
        //----- コンポーネント総なめ
        for (int i = 0; i < m_componentList->Count; i++) {
            if (m_componentList[i]->GetType() == ComponentType::typeid) {
                m_componentList->RemoveAt(i);
            }
        }

        return false;
    }
}
