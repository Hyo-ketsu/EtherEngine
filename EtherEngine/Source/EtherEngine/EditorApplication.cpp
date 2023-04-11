#include <EtherEngine/EditorApplication.h>


namespace EtherEngine {
    // 追加初期化(後)
    void EditorApplication::InitLast(void) {
        m_imGui = std::make_unique<IMGUI>(m_dxRender.GetDevice(), m_dxRender.GetContext());
    }
}
