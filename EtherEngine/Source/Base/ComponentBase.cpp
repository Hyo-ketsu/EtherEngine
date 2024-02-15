#include <Base/ComponentBase.h>


//----- ComponentBase定義
namespace EtherEngine {
    // コンストラクタ
    ComponentBase::ComponentBase(NativeGameObject* gameObject, const std::string& name)
        : NativeBaseObject(name)
        , m_isStart(false) 
        , m_gameObject(gameObject) {
    }


    // 追加時処理を行う
    void ComponentBase::CreateFunction(void) {
        //----- アクティブチェックは行いません

        //----- 追加時処理実行
        Create();
    }
    // 更新処理を行う
    void ComponentBase::UpdateFunction(void) {
        //----- アクティブチェック
        if (IsUnvalidObject()) return;

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
        if (IsUnvalidObject()) return;

        //----- 削除時処理
        Delete();
    }


    // 衝突開始時処理を行う
    void ComponentBase::CollisionStartFunction(void) {
        //----- アクティブチェック
        if (IsUnvalidObject()) return;

        //----- 衝突対象が与えられているか
        if (m_hitData.empty()) return;

        //----- 処理実行
        CollisionStart();
    }
    // 衝突終了時処理を行う
    void ComponentBase::CollisionEndFunction(void) {
        //----- アクティブチェック
        if (IsUnvalidObject()) return;

        //----- 衝突対象が与えられているか
        if (m_hitData.empty()) return;

        //----- 処理実行
        CollisionEnd();
    }
    // 衝突時処理を行う
    void ComponentBase::CollisionHitFunction(void) {
        //----- アクティブチェック
        if (IsUnvalidObject()) return;

        //----- 衝突対象が与えられているか
        if (m_hitData.empty()) return;

        //----- 処理実行
        CollisionHit();
    }
}
