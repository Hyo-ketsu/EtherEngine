#include <EngineLibrary/GameObject.h>
#include <Base/BaseUtility.h>
#include <Base/GameObjectStorage.h>


//----- GameObject ��`
namespace EtherEngine {
    // �R���X�g���N�^
    GameObject::GameObject(void) {
        m_handle = new std::remove_pointer_t<decltype(m_handle)>(GameObjectStorage::Get()->CreateGameObject());
    }
    // �f�X�g���N�^
    GameObject::~GameObject(void) {
        this->!GameObject();
    }
    // �t�@�C�i���C�U
    GameObject::!GameObject(void) {
        DELETE_NULL(m_handle);
    }
}
