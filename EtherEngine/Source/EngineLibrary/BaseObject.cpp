#include <EngineLibrary/BaseObject.h>
#include <EngineLibrary/BaseObjectStorage.h>


#pragma managed
//----- BaseObject ��`
namespace EtherEngine {
    // �R���X�g���N�^
    BaseObject::BaseObject(void) 
        : BaseObject(gcnew IDClass()) {
        BaseObjectStorage::Get->AddBaseObject(this);
    }
    // �R���X�g���N�^
    BaseObject::BaseObject(IDClass^ id) 
        : m_isActive(true) 
        , m_isDelete(false)
        , m_id(id) {
    }


    // ���̃I�u�W�F�N�g���폜����
    void BaseObject::DeleteObject(void) {
        m_isDelete = true;
    }
    // ���̃I�u�W�F�N�g���g���Ȃ������肷��
    bool BaseObject::IsUnvalidObject(void) {
        return m_isActive && (m_isDelete == false);
    }
}
