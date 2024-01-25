#include <EngineLibrary/Component.h>
#include <EngineLibrary/GameObject.h>


#pragma managed
//----- Component 定義
namespace EtherEngine {
    // コンストラクタ
    Component::Component(void) {
        m_gameObject = nullptr;
    }


    // ゲームオブジェクト
    GameObject^ Component::ParentGameObject::get(void) {
        //----- 親オブジェクトを取得
        return m_gameObject;
    }
    void Component::ParentGameObject::set(GameObject^ value) {
        m_gameObject = value;
    }
}
