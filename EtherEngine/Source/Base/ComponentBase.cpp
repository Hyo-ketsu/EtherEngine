#include <Base/ComponentBase.h>
#include <Base/GameObject.h>


//----- ComponentBase定義
namespace EtherEngine {
    // コンストラクタ
    ComponentBase::ComponentBase(void* gameObject)
        : m_isStart(false) 
        , m_gameObject(static_cast<GameObject*>(gameObject)) {
        
    }
    // デストラクタ
    ComponentBase::~ComponentBase(void) {
    }


    // 所属ゲームオブジェクトの取得
    void ComponentBase::GetGameObject(void** gameObject) const {
        *gameObject = m_gameObject;
    }


    // 更新処理を行う
    void ComponentBase::UpdateFuntion(void) {
        if (m_isStart) {
            Update();
        }
        else {
            Start();
            m_isStart = true;
        }
    }
}
