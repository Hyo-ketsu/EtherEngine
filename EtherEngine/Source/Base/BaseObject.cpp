#include <Base/BaseObject.h>


//----- BaseObject ��`
namespace EtherEngine {
    // �R���X�g���N�^
    BaseObject::BaseObject(const std::string& name) 
        : m_isActive(true) 
        , m_isDelete(false) {
    }


    // ���̃I�u�W�F�N�g���폜����
    void BaseObject::DeleteObject(void) {
        m_isActive = false;
        m_isDelete = true;
    }
    // ���̃I�u�W�F�N�g���A�N�e�B�u�����肷��
    bool BaseObject::IsUnvalidObject(void) const {
        return m_isActive == false && m_isDelete;
    }
}
