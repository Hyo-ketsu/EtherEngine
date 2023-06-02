#include <Base/ComponentBase.h>


namespace EtherEngine {
    // コンストラクタ
    ComponentBase::ComponentBase(void) 
        : m_isStart(false) {
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
    // 描画処理を行う
    void ComponentBase::DrawFuntion(void) {
        Draw();
    }
}
