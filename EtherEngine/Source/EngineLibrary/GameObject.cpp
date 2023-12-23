#include <EngineLibrary/GameObject.h>
#include <Base/BaseUtility.h>
#include <Base/GameObjectStorage.h>


//----- GameObject 定義
namespace EtherEngine {
    // コンストラクタ
    GameObject::GameObject(void) {
        m_handle = new std::remove_pointer_t<decltype(m_handle)>(GameObjectStorage::Get()->CreateGameObject());
    }
    // デストラクタ
    GameObject::~GameObject(void) {
        this->!GameObject();
    }
    // ファイナライザ
    GameObject::!GameObject(void) {
        DELETE_NULL(m_handle);
    }
}
