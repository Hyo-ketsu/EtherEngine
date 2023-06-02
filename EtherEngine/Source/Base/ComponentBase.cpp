#include <Base/ComponentBase.h>


namespace EtherEngine {
    // �R���X�g���N�^
    ComponentBase::ComponentBase(void) 
        : m_isStart(false) {
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
    // �`�揈�����s��
    void ComponentBase::DrawFuntion(void) {
        Draw();
    }
}
