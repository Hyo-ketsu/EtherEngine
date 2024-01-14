#include <EngineLibrary/ManageEnum.h>


//----- ManageEnum 定義
namespace EtherEngine {
    // コンストラクタ
    ManageEnum::ManageEnum(System::Enum^ setEnum) {
        if (setEnum == nullptr) return; 

        m_enumType = setEnum->GetType();
        m_enumValue = System::Convert::ToInt64(setEnum);
    }
}
