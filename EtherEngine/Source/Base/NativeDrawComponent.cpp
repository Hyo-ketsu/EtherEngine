#include <Base/NativeDrawComponent.h>


//----- DrawComponent実装
namespace EtherEngine {
    // 描画処理を行う
    void NativeDrawComponent::DrawFuntion(void) {
        //----- アクティブチェック
        if (this->IsUnvalidObject()) return;
        Update();
        //----- アクティブチェック
        if (this->IsUnvalidObject()) return;
        Draw();
        //----- アクティブチェック
        if (this->IsUnvalidObject()) return;
        LateUpdate();
    }
}
