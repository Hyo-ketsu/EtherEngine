#include <EtherEngine/EditorApplication.h>


namespace EtherEngine {
    // �ǉ�������(��)
    void EditorApplication::InitLast(void) {
        m_imGui = std::make_unique<IMGUI>(m_dxRender.GetAtomicData().GetDevice(), m_dxRender.GetAtomicData().GetContext());
    }
}
