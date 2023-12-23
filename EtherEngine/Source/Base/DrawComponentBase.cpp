#include <Base/DrawComponentBase.h>


//----- DrawComponent実装
namespace EtherEngine {
    // 描画処理を行う
    void DrawComponent::DrawFuntion(void) {
        //----- アクティブチェック
        if (GetActive() == false) return;
        if (GetDelete()) return;

        Draw();
    }
}
