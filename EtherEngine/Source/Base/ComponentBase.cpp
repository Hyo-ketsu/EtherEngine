#include <Base/ComponentBase.h>


//----- ComponentBase定義
namespace EtherEngine {
    // コンストラクタ
    NativeComponent::NativeComponent(NativeGameObject* gameObject)
        : NativeBaseObject(typeid(*this).name())
        , m_gameObject(gameObject) {
    }
}
