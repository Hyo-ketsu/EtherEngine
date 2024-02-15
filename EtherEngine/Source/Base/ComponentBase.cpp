#include <Base/ComponentBase.h>


//----- ComponentBase��`
namespace EtherEngine {
    // �R���X�g���N�^
    ComponentBase::ComponentBase(NativeGameObject* gameObject, const std::string& name)
        : NativeBaseObject(name)
        , m_isStart(false) 
        , m_gameObject(gameObject) {
    }


    // �ǉ����������s��
    void ComponentBase::CreateFunction(void) {
        //----- �A�N�e�B�u�`�F�b�N�͍s���܂���

        //----- �ǉ����������s
        Create();
    }
    // �X�V�������s��
    void ComponentBase::UpdateFunction(void) {
        //----- �A�N�e�B�u�`�F�b�N
        if (IsUnvalidObject()) return;

        //----- �X�V�����������͏������������s��
        if (m_isStart) {
            //----- �X�V����
            Update();
        }
        else {
            //----- �X�V�����̍ŏ��̃t���[���B����������
            Start();
            m_isStart = true;
        }
    }


    // �폜���������s��
    void ComponentBase::DeleteFuntion(void) {
        //----- �A�N�e�B�u�`�F�b�N
        if (IsUnvalidObject()) return;

        //----- �폜������
        Delete();
    }


    // �ՓˊJ�n���������s��
    void ComponentBase::CollisionStartFunction(void) {
        //----- �A�N�e�B�u�`�F�b�N
        if (IsUnvalidObject()) return;

        //----- �ՓˑΏۂ��^�����Ă��邩
        if (m_hitData.empty()) return;

        //----- �������s
        CollisionStart();
    }
    // �ՓˏI�����������s��
    void ComponentBase::CollisionEndFunction(void) {
        //----- �A�N�e�B�u�`�F�b�N
        if (IsUnvalidObject()) return;

        //----- �ՓˑΏۂ��^�����Ă��邩
        if (m_hitData.empty()) return;

        //----- �������s
        CollisionEnd();
    }
    // �Փˎ��������s��
    void ComponentBase::CollisionHitFunction(void) {
        //----- �A�N�e�B�u�`�F�b�N
        if (IsUnvalidObject()) return;

        //----- �ՓˑΏۂ��^�����Ă��邩
        if (m_hitData.empty()) return;

        //----- �������s
        CollisionHit();
    }
}
