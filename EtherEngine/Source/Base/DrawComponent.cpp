#include <Base/DrawComponent.h>


//----- DrawComponent����
namespace EtherEngine {
    // �`�揈�����s��
    void DrawComponent::DrawFuntion(void) {
        //----- �A�N�e�B�u�`�F�b�N
        if (GetActive() == false) return;
        if (GetDelete()) return;

        Draw();
    }
}
