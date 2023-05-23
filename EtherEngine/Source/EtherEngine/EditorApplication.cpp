#include <EtherEngine/EditorApplication.h>


namespace EtherEngine {
    // ’Ç‰Á‰Šú‰»(Œã)
    void EditorApplication::InitLast(void) {
        m_imGui = std::make_unique<IMGUI>(m_dxRender.GetAtomicData().GetDevice(), m_dxRender.GetAtomicData().GetContext());
    }
}
