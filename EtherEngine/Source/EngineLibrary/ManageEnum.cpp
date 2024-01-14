#include <EngineLibrary/ManageEnum.h>


//----- ManageEnum ��`
namespace EtherEngine {
    // �R���X�g���N�^
    ManageEnum::ManageEnum(System::Enum^ setEnum) {
        if (setEnum == nullptr) return; 

        m_enumType = setEnum->GetType();
        m_enumValue = System::Convert::ToInt64(setEnum);
    }
}
