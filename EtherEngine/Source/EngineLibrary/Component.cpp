#include <EngineLibrary/Component.h>


#pragma managed
//----- Component 定義
namespace EtherEngine {
    // コンストラクタ
    Component::Component(void) {
        m_gameObject = nullptr;
    }


    // ゲームオブジェクト
    EtherEngine::GameObject^ Component::ParentGameObject::get(void) {
        return m_gameObject;
    }
    void Component::ParentGameObject::set(EtherEngine::GameObject^ value) {
        m_gameObject = value;
    }
}
