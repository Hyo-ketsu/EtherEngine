#include <EngineLibrary/Component.h>


#pragma managed
//----- Component ��`
namespace EtherEngine {
    // �R���X�g���N�^
    Component::Component(void) {
        m_gameObject = nullptr;
    }


    // �Q�[���I�u�W�F�N�g
    EtherEngine::GameObject^ Component::ParentGameObject::get(void) {
        return m_gameObject;
    }
    void Component::ParentGameObject::set(EtherEngine::GameObject^ value) {
        m_gameObject = value;
    }
}
