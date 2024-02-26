#include <EngineLibrary/GameObject.h>
#include <Base/BaseUtility.h>
#include <Base/NativeGameObjectStorage.h>
#include <EngineLibrary/BaseObjectStorage.h>
#include <EngineLibrary/GameObjectStorage.h>
#include <EngineLibrary/DrawComponent.h>


#pragma managed
//----- GameObject 定義
namespace EtherEngine {
    // コンストラクタ
    GameObject::GameObject(void)
        : m_components(gcnew System::Collections::Generic::List<Component^>(0)) 
        , m_deleteComponents(gcnew System::Collections::Generic::List<Component^>(0)) {
        m_handle = new std::remove_pointer_t<decltype(m_handle)>(NativeGameObjectStorage::Get()->CreateGameObject());
        GameObjectStorage::Get->AddGameObject(this);
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
    bool GameObject::IsSceneObject(Scene^ scene) {
        return NGameObject.GetData().GetScene() == scene->GetSceneID();
    }


    // 更新処理を行う
    void GameObject::Update(void) {
        for each (auto it in m_components) {
            if (it->IsUnvalidObject()) continue;

            it->Update();
        }

        DeleteComponents();
    }
    // 更新後処理を行う
    void GameObject::LateUpdate(void) {
        for each (auto it in m_components) {
            if (it->IsUnvalidObject()) continue;

            it->LateUpdate();
        }

        DeleteComponents();
    }
    // 物理更新処理を行う
    void GameObject::FixedUpdate(void) {
        for each (auto it in m_components) {
            if (it->IsUnvalidObject()) continue;

            it->Update();
        }

        DeleteComponents();
    }
    // 描画処理を行う
    void GameObject::Draw(UnmanageMaintainer<Eigen::Matrix4f> view, UnmanageMaintainer<Eigen::Matrix4f> projection) {
        for each (auto it in m_components) {
            if (it->IsUnvalidObject()) continue;

            auto drawComponent = dynamic_cast<DrawComponent^>(it);

            if (drawComponent != nullptr) {
                drawComponent->SetView(view.GetUnmanageMaintainer());
                drawComponent->SetProjection(projection.GetUnmanageMaintainer());

                drawComponent->Draw();
            }
        }

        DeleteComponents();
    }
    // 削除時処理を行う
    void GameObject::Delete(void) {

        for each (auto it in m_components) {
            if (it->IsUnvalidObject()) continue;

            it->Delete();
        }

        DeleteComponents();
    }
    // 衝突開始処理を行う
    void GameObject::CollisionStart(void) {
        for each (auto it in m_components) {
            if (it->IsUnvalidObject()) continue;

            it->CollisionStart();
        }

        DeleteComponents();
    }
    // 衝突終了処理を行う
    void GameObject::CollisionEnd(void) {
        for each (auto it in m_components) {
            if (it->IsUnvalidObject()) continue;

            it->CollisionEnd();
        }

        DeleteComponents();
    }
    // 衝突処理を行う
    void GameObject::CollisionHit(void) {
        for each (auto it in m_components) {
            if (it->IsUnvalidObject()) continue;

            it->CollisionHit();
        }

        DeleteComponents();
    }


    // コンポーネントを追加する
    generic <typename ComponentType>
    ComponentType GameObject::AddComponent(void) {
        //----- コンポーネントを追加する
        auto ret = safe_cast<ComponentType>(System::Activator::CreateInstance(ComponentType::typeid));
        ret->ParentGameObject = this;
        m_components->Add(ret);

        //----- 追加時処理実行
        ret->Create();

        //----- 返却
        return ret;
    }
    // コンポーネントを取得する
    generic <typename ComponentType>
    ComponentType GameObject::GetComponent(void) {
        //----- コンポーネント総なめ
        for each (auto it in m_components) {
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
        for each (auto it in m_components) {
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
        for each (auto it in m_components) {
            if (it->GetType() == ComponentType::typeid) {
                m_deleteComponents->Add(it);
                return true;
            }
        }

        return false;
    }


    // 削除済みのコンポーネントを削除する
    void GameObject::DeleteComponents(void) {
        for each (auto it in m_deleteComponents) {
            m_components->Remove(it);
        }

        m_deleteComponents->Clear();
    }
}
