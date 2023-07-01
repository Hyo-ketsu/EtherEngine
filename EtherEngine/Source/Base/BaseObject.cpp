#include <Base/BaseObject.h>


//----- BaseObject ��`
namespace EtherEngine {
    // �R���X�g���N�^
    BaseObject::BaseObject(const std::string& name) 
        : m_name(name)
        , m_isActive(true) 
        , m_isDelete(false) {
    }

    // ���̃I�u�W�F�N�g���폜����
    void BaseObject::DeleteObject(void) {
        m_isActive = false;
        m_isDelete = true;
    }
}
