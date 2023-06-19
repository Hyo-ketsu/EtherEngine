#include <Base/ComponentBase.h>
#include <Base/GameObject.h>


//----- ComponentBase��`
namespace EtherEngine {
    // �R���X�g���N�^
    ComponentBase::ComponentBase(void* gameObject)
        : m_isStart(false) 
        , m_gameObject(static_cast<GameObject*>(gameObject)) {
        
    }
    // �f�X�g���N�^
    ComponentBase::~ComponentBase(void) {
    }


    // �����Q�[���I�u�W�F�N�g�̎擾
    void ComponentBase::GetGameObject(void** gameObject) const {
        *gameObject = m_gameObject;
    }


    // �X�V�������s��
    void ComponentBase::UpdateFuntion(void) {
        if (m_isStart) {
            Update();
        }
        else {
            Start();
            m_isStart = true;
        }
    }
}
