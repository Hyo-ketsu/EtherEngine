#include <Base/ComponentBase.h>


//----- ComponentBase��`
namespace EtherEngine {
    // �R���X�g���N�^
    NativeComponent::NativeComponent(NativeGameObject* gameObject)
        : NativeBaseObject(typeid(*this).name())
        , m_gameObject(gameObject) {
    }
}
