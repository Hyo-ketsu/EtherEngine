#include <Base/NativeDrawComponent.h>


//----- DrawComponent����
namespace EtherEngine {
    // �`�揈�����s��
    void NativeDrawComponent::DrawFuntion(void) {
        //----- �A�N�e�B�u�`�F�b�N
        if (this->IsUnvalidObject()) return;
        Update();
        //----- �A�N�e�B�u�`�F�b�N
        if (this->IsUnvalidObject()) return;
        Draw();
        //----- �A�N�e�B�u�`�F�b�N
        if (this->IsUnvalidObject()) return;
        LateUpdate();
    }
}
