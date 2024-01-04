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
        , m_id(id) {
    }


    // �C�x���g�̔��΂��s��
    void BaseObject::UpdateEventIgnition(System::EventArgs^ e) {
        UpdateEvent(this, e);
    }
}
