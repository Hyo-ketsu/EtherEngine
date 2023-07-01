#include <Base/ComponentBase.h>
#include <Base/GameObject.h>


//----- ComponentBase定義
namespace EtherEngine {
    // コンストラクタ
    ComponentBase::ComponentBase(void* gameObject, const std::string& name)
        : BaseObject(name)
        , m_isStart(false) 
        , m_gameObject(static_cast<GameObject*>(gameObject)) {
    }


    // 所属ゲームオブジェクトの取得
    void ComponentBase::GetParentObject(void** gameObject) const {
        *gameObject = m_gameObject;
    }


    // 更新処理を行う
    void ComponentBase::UpdateFuntion(void) {
        //----- アクティブチェック
        if (GetActive() == false) return;
        if (GetDelete()) return;

        //----- 更新処理もしくは初期化処理を行う
        if (m_isStart) {
            //----- 更新処理
            Update();
        }
        else {
            //----- 更新処理の最初のフレーム。初期化処理
            Start();
            m_isStart = true;
        }
    }

    // 削除時処理を行う
    void ComponentBase::DeleteFuntion(void) {
        //----- アクティブチェック
        if (GetActive() == false) return;
        if (GetDelete()) return;

        //----- 削除時処理
        Delete();
    }
}
