#include <EngineLibrary/BaseObject.h>


#pragma managed
//----- BaseObject ��`
namespace EtherEngine {
    // �R���X�g���N�^
    BaseObject::BaseObject(void) 
        : BaseObject(gcnew IDClass()) {
    }
    // �R���X�g���N�^
    BaseObject::BaseObject(IDClass^ id) 
        : m_isActive(true) 
        , m_id(id) {
    }
}
