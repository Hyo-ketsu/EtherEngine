#include <EngineLibrary/Component.h>
#include <EngineLibrary/GameObject.h>


#pragma managed
//----- Component ��`
namespace EtherEngine {
    // �R���X�g���N�^
    Component::Component(void) {
        m_gameObject = nullptr;
    }


    // �Q�[���I�u�W�F�N�g
    GameObject^ Component::ParentGameObject::get(void) {
        //----- �e�I�u�W�F�N�g���擾
        return m_gameObject;
    }
    void Component::ParentGameObject::set(GameObject^ value) {
        m_gameObject = value;
    }
}
